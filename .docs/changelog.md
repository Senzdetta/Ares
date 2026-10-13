# CHANGELOG

### 2026-10-01
```text
1. Rewrote the bootloader if-else logic as a Go binary for better performance.
   init/bootloader.sh now just evals the binary.

2. Ported small utilities to native Go for faster startup:
   - rmext
   - remake
   - fchmod
   - setcursor
```

### 2026-10-02
```text
1. Clean up the bootloader code and add color.

2. Adding code validation to the bootloader to validate init/bootloader.sh before generating code.

3. Moving bin/common/* and bin/core/* (some items) to bin/iofs/, bin/term/, etc., based on the tools' functions.
   Also updating the documentation (data/aresdoc/bin) to reflect the actual bin directory structure.

4. Autosuggestion flexibility.
   Delegates symbol coloring and cutting to the user configuration, allowing for theme flexibility in shgest.so.
   New keys in config/shgest.conf:
   - history_color
   - alias_color
   - function_color
   - builtin_color
   - tool_color
   - variable_color
   - path_color
   - cutter_symbol
   - cutter_color
   - other_color

5. rewriting the shgest.conf documentation (data/aresdoc/config/shgest.conf.acon).

6. Optimized shgest.so (utils/cso/shgest/search_path.h) to handle tildes (~) and variables ($) while still providing suggestions for the next word.

7. Modified utils/go/bootloader to use flags:
   - --shell for console/shell.sh
   - --bootloader for init/bootloader.sh

8. Removed validation code for init/bootloader.sh as it was unnecessary.

9. Changed the bootloader invocation from 'eval "$(...)"' to 'source <()' for better performance (though it doesn't really make much of a difference, lol).
```

### 2026-10-03
```text
1. metadata/*.json is embedded directly into the utils/go/json_parser binary

2. the essence of the ares framework:
   - ares.sh -> ares.c
   - utils/banner.sh -> utils/banner.h (embedded banner, data/banner.txt removed)
   - module/shell.sh -> module/shell.h
   - module/exec.sh -> module/exec.h
   - etc...
   rewritten in c language.

3. Converted dynav.so to be configuration-based (using config/startup.config).
   Variable read-only status is now determined by the 'lock_variable = <true|false>' key.
   Also updated utils/go/bootloader to read this key as well.

4. Modified the boot architecture.
   console/shell.sh and init/bootloader.sh are now generated on-the-fly during boot.
   the corresponding files on disk are empty both before and after booting.
   Removed 'errexit' so that the boot process continues even if an error occurs.
```

### 2026-10-04
```text
1. Re-initialized the Go component and updated the dependency from lib/go to lib/std/go.

2. Moved utils/go/cnf_handler to bin/core/cnf and updated init/engine/cnf/cnf_handler.shx accordingly.
```

### 2026-10-06
```text
1. change --version output.
```

### 2026-10-08
```text
1. Added logic so that the --uwu output is fixed as '(・ω・)' instead of being random.

2. removed utils/go/nyanners, as --uwu logic is now native to C (module/uwu.h).
```

### 2026-10-09
```text
1. Replaced config/dynap_exclude.scfg with config/dynap_exclude.lst, utilizing a list syntax that supports variable expansion for a more human-readable format.
   Naturally, utils/cso/dynap/* has been updated to accommodate this change.

2. Added utils/crawlpath/* and utils/crawlpath.h.
   commands executed via flags like --chstartup (which rely on $PATH) will now retain the correct context.

3. Updated documentation for data/aresdoc/config/dynap_exclude.lst (formerly .scfg).

4. Added a new binary: bin/system/printpath (C).

5. Adjusted the initialization order of $HOME, $PATH, and dynamic variables in utils/bootloader/bs_init.go.
   Previous order: dynap -> rhome -> dynav
   Since dynap now supports variable expansion, the correct order is:
   Current order: rhome -> dynav -> dynap.

6. Changing the comment syntax in config/dynap_exclude.lst to match config/dynav_ignore.lst (using '#'), and making adjustments in utils/crawlpath/ldconfig.h and utils/cso/dynap/load_exclusions.h.

7. A new binary, bin/iofs/tojunk (C) has been added to replace bin/iofs/remake.
   bin/iofs/remake has been removed for now but will be reintroduced once the package manager is ready, marked with the @deprecated tag.
```

### 2026-10-10
```text
1. Adding new tools/commands:
   - bin/string/rmchar (C)
   - bin/string/strjoin (C)
   - bin/string/strsplit (C)
   - bin/string/writestr (C)
   - bin/string/writefstr (C)
   - bin/string/strtrans (C)
```

### 2026-10-11
```text
1. Added logic to handle cases where the alias and the actual filename are identical for openfile.
   openfile now prompts the user to choose which file to open in such instances.
   openfile now also supports custom themes via the 'openfile.theme = to/theme' setting in the configuration file.

2. Changed the rule file for bin/iofs/rmext (rmext) from .scfg to .lst.
   Previously: "exclude" from "path/to"
   Now: path/to/exclude

3. Removed the fixed data type logic in chstartup when reading and modifying the configuration.
   Since the Ares configuration is now extremely flexible, this feature no longer makes sense and actually complicates things.

4. Fixing compilation errors in all .so files (yes, all of them) for Debian Sid.
   Maybe someday there will be a version of Ares that is slow but doesn't give the developer a migraine.

5. addition of lib/std/lua/*.

6. Changes to the args parameter and the addition of stdin (piping) support in:
   - rmchar
   - strjoin
   - strsplit
   - strtrans

7. adding new tool/cmd:
   - bin/text/rmline (C)
```

### 2026-10-12
```text
1. Removal of functions in utils/go/bootloader/ and replacing them with:
   - ss_* -> generate_bootloader.go
   - bs_* -> generate_shell.go
   ...along with several changes to Fprintf and function names.

2. I’ve split the Ares core—along with the config, CSO, and bootloader—into separate subsystems.
   Ares now has a subsystem architecture, including ares-subsystem-crossp for cross-platform support.
   Ironically, while I had been struggling with performance issues and GNU Bash headers that kept breaking across versions, it turned out the cross-platform version—which I assumed would be much slower—didn't actually show a noticeable difference.
   Both have very similar startup times.
   So... I’m now prioritizing ares-subsystem-crossp over ares-subsystem-glibc, only maintaining the glibc version when I feel like it.
```

### 2026-10-13
```text
1. Adding new tool:
   - bin/text/sloc (Go)
   - bin/discovery/avaengine (C)
```