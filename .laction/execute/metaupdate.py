import shutil
import tempfile
import sys
import re
import json
import time
import subprocess
from pathlib import Path

script_dir = Path(__file__).resolve().parent
project_root = script_dir.parent.parent

STATE_DIR = (Path(
    tempfile.gettempdir(),
) / "laction" / "metaupdate.py" / "state").resolve()

FORCE = (script_dir / "metaupdate" / "forceup").exists()

def ask(question, default_yes):
    if FORCE:
        return True
    ans = input(question).strip().lower()
    return default_yes if not ans else ans in ("y", "yes")

def inside(base, p):
    base, p = Path(base).resolve(), Path(p).resolve()
    return p != base and base in p.parents

def safe_in(base, rel):
    if Path(rel).is_absolute():
        raise ValueError(
            f"\x1b[0mAbsolute path is not allowed:",
            f"\x1b[0;32m{rel}\x1b[0m",
        )

    p = (base / rel).resolve()
    if not inside(base, p):
        raise ValueError(
            f"\x1b[0mPath outside \x1b[0;34m{base.name}\x1b[0m:",
            f"\x1b[0;32m{rel}\x1b[0m",
        )

    return p

def dest_in_root(rel):
    p = (project_root / rel.lstrip("/\\")).resolve()
    if not inside(project_root, p):
        raise ValueError(
            f"\x1b[0mPath outside project root:",
            f"\x1b[0;32m{rel}\x1b[0m",
        )
    return p

def parse_meta(raw):
    return json.loads(
        re.sub(
            r",\s*([\]}])",
            r"\1",
            raw,
        ),
    )

def find_packages():
    return sorted(
        p for p in project_root.rglob("metapackage.json")
        if inside(
            project_root, p,
        ) and ".backup" not in p.parts
    )

def copy_into(src_dir, dst_dir):
    for c in src_dir.iterdir():
        tgt = dst_dir / c.name
        if c.is_dir():
            shutil.copytree(
                c, tgt,
                copy_function=shutil.copy,
                ignore_dangling_symlinks=True,
            )
        else:
            shutil.copy(c, tgt)

def update(meta_path):
    meta_path = meta_path.resolve()
    dest = meta_path.parent
    name = dest.name

    if not inside(project_root, dest):
        raise ValueError(
            f"\x1b[0mMetapackage is outside project root.",
        )

    if inside(project_root, STATE_DIR):
        raise ValueError(
            f"\x1b[0mTemp folder",
            f"\x1b[1;90m(\x1b[0;32m{STATE_DIR}\x1b[1;90m)",
            f"\x1b[0mis inside project root.",
        )

    raw = meta_path.read_text(encoding="utf-8")
    meta = parse_meta(raw)
    pkg = meta["package"]

    if not re.fullmatch(
        r"[\w.-]+(/[\w.-]+)+",
        pkg,
    ):
        raise ValueError(
            f"\x1b[0mWrong package name format:",
            f"\x1b[0;32m{pkg}\x1b[0m",
        )

    STATE_DIR.mkdir(parents=True, exist_ok=True)
    work = Path(
        tempfile.mkdtemp(
            prefix=f"{name}_",
            dir=STATE_DIR,
        ),
    )
    repo = work / "repo"
    rrepo = repo.resolve()

    try:
        print(
            f"\x1b[0;34m[*] \x1b[0mCloning:",
            f"\x1b[0;32m{pkg}\x1b[0m...",
        )

        subprocess.run(
            [
                "git", "clone", "--depth", "1",
                f"https://{pkg}.git",
                str(repo),
            ],
            check=True,
        )

        moves = []
        for rule in meta.get("move", []):
            s, d = [x.strip() for x in rule.split("->")]

            into_dir = d.endswith("/")
            src = safe_in(repo, s)
            dst = dest_in_root(d)

            if into_dir:
                dst = dst / src.name

            if not src.exists():
                raise ValueError(
                    f"\x1b[0mFile or folder not found:",
                    f"\x1b[0;32m{s}\x1b[0m",
                )

            if dst == dest or inside(dest, dst):
                raise ValueError(
                    f"\x1b[0mMove to this destination is not allowed:",
                    f"\x1b[0;32m{d}\x1b[0m",
                )

            if inside(dst, dest):
                raise ValueError(
                    f"\x1b[0mDestination covers package folder:",
                    f"\x1b[0;32m{d}\x1b[0m",
                )

            if dst.exists() and src.is_dir() != dst.is_dir():
                raise ValueError(
                    f"\x1b[0mType mismatch (file vs folder):",
                    f"\x1b[0;32m{s}",
                    f"\x1b[1;90m->",
                    f"\x1b[0;32m{d}\x1b[0m",
                )

            moves.append((src, dst))

        removes = [
            safe_in(
                repo, r,
            ) for r in meta.get("remove", [])
        ]

        print(
            f"\x1b[1;34m[*] \x1b[0mFound package:",
            f"\x1b[0;32m{name}",
            f"\x1b[1;90m(\x1b[0;32m{pkg}\x1b[1;90m)\x1b[0m",
        )

        print(
            f"    \x1b[1;34m›",
            f"\x1b[0mRemove:",
        )

        for r in removes:
            print(
                f"        \x1b[1;31m-",
                f"\x1b[0;32m{r.relative_to(rrepo)}\x1b[0m",
            )

        print(
            f"    \x1b[1;34m›",
            f"\x1b[0mMove:",
        )

        for s, d in moves:
            print(
                f"        \x1b[1;31m-",
                f"\x1b[0;32m{s.relative_to(rrepo)}",
                f"\x1b[1;90m->",
                f"\x1b[0;32m{d.relative_to(project_root)}\x1b[0m",
            )

        dask = (
            f"\x1b[0mUpdate package? (y/n): ",
        )

        if not ask(dask, True):
            print(
                f"\x1b[0;33m[!] \x1b[0mPackage",
                f"\x1b[0;34m{name}\x1b[0m: skipped.",
            )
            return

        for s, d in moves:
            if d.exists():
                q = (
                    f"\x1b[0mPackage \x1b[0;32m{name}",
                    f"\x1b[0mwants to overwrite:",
                    f"\n",
                    f"\x1b[0;32m{s.relative_to(rrepo)}",
                    f"\x1b[1;90m->",
                    f"\x1b[0;32m{d.relative_to(project_root)}\x1b[0m",
                    f"\n",
                    f"\x1b[0mAllow overwrite? (y/n): ",
                )

                if not ask(q, False):
                    print(
                        f"\x1b[0;33m[!] \x1b[0;34m{name}\x1b[0m:",
                        f"overwrite canceled, nothing changed.",
                    )
                    return

        bak = STATE_DIR / "backup" / name / time.strftime("%Y%m%d-%H%M%S")
        bak.mkdir(parents=True)

        for s, d in moves:
            if d.exists():
                b = bak / "moved" / d.relative_to(project_root)
                b.parent.mkdir(
                    parents=True,
                    exist_ok=True,
                )

                if d.is_dir():
                    shutil.copytree(
                        d, b,
                        copy_function=shutil.copy,
                    )
                    shutil.rmtree(d)
                else:
                    shutil.copy(d, b)
                    d.unlink()

            d.parent.mkdir(
                parents=True,
                exist_ok=True,
            )

            shutil.move(
                str(s), str(d),
                copy_function=shutil.copy,
            )

        for r in removes:
            if r.is_dir():
                shutil.rmtree(r)
            else:
                r.unlink(missing_ok=True)

        old = bak / "old"
        old.mkdir()

        for c in dest.iterdir():
            if c.name != "metapackage.json":
                shutil.move(
                    str(c), str(old / c.name),
                )

        copy_into(repo, dest)
        meta_path.write_text(raw, encoding="utf-8")

        print(
            f"\x1b[0;32m[+] \x1b[0mUpdated:",
            f"\x1b[0;32m{dest.relative_to(project_root)}",
            f"\x1b[1;90m(\x1b[0;37mbackup:",
            f"\x1b[0;32m{bak}\x1b[1;90m)\x1b[0m",
        )
    finally:
        shutil.rmtree(
            work, ignore_errors=True,
        )

packages = find_packages()
if not packages:
    print(
        f"\x1b[0;33m[!] \x1b[0mMetapackage file not found in:",
        f"\x1b[0;32m{project_root}\x1b[0m",
    )

if FORCE:
    print(
        f"\x1b[0;33m[!] \x1b[0mForce mode active:",
        f"skipping confirmation.",
    )

for mp in packages:
    try:
        update(mp)
    except Exception as e:
        print(
            f"\x1b[1;31m[!]",
            f"\x1b[0m{mp.relative_to(project_root)}:",
            f"{e}",
        )