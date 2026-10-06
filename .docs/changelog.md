# CHANGELOG

### 2026-10-01
```text
1. Rewrote the bootloader if-else logic as a Go binary for better performance.
   init/bootloader.sh now just `eval`s the binary.

2. Ported small utilities to native Go for faster startup:
     - rmext
     - remake
     - fchmod
     - setcursor
```

### 2026-10-02
```text
1. Clean up the bootloader code and add color.

2. Adding code validation to the bootloader to validate `init/bootloader.sh` before generating code.

3. Moving `bin/common/*` and `bin/core/*` (some items) to `bin/iofs/`, `bin/term/`, etc., based on the tools' functions.
   Also updating the documentation (`data/aresdoc/bin`) to reflect the actual `bin` directory structure.

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

9. Changed the bootloader invocation from `eval "$(...)"` to `source <()` for better performance (though it doesn't really make much of a difference, lol).
```

### 2026-10-03
```text
1. metadata/*.json is embedded directly into the utils/go/json_parser binary

2. the essence of the ares framework: 
     - ares.sh -> ares.c 
     - utils/banner.sh -> utils/banner.h (embedded banner, data/banner.txt removed) 
     - module/shell.sh -> module/shell.c 
     - etc... 
   rewritten in c language.

3. Converted dynav.so to be configuration-based (using config/startup.config).
   Variable read-only status is now determined by the 'lock_variable = <true|false>' key.
   Also updated utils/go/bootloader to read this key as well.

4. Modified the boot architecture.
   `console/shell.sh` and `init/bootloader.sh` are now generated on-the-fly during boot.
   the corresponding files on disk are empty both before and after booting.
   Removed 'errexit' so that the boot process continues even if an error occurs.
```

### 2026-10-04
```text
1. Re-initialized the Go component and updated the dependency from `lib/go` to `lib/std/go`.

2. Moved `utils/go/cnf_handler` to `bin/core/cnf` and updated `init/engine/cnf/cnf_handler.shx` accordingly.
```

### 2026-10-06
```
1. change --version output.
```