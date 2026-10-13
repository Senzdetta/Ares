// https://github.com/Senzdetta/Ares

language "Shell" {
    ext = [".sh", ".bash", ".fish", ".zsh", ".bashrc", ".zshrc"]
    com = ["#{}"]
}

language "Python" {
    ext = [".py", ".pyi", ".pyx"]
    com = ["#{}"]
}

language "Perl" {
    ext = [".pl", ".pm", ".t"]
    com = ["#{}"]
}

language "Ruby" {
    ext = [".rb", ".rbw", ".rake", ".gemspec"]
    com = ["#{}"]
}

language "Lua" {
    ext = [".lua"]
    com = ["--{}", "--[[{}]]"]
}

language "Luau" {
    ext = [".luau"]
    com = ["--{}", "--[[{}]]"]
}

language "Javascript" {
    ext = [".js", ".jsx"]
    com = ["//{}", "/*{}*/"]
}

language "Typescript" {
    ext = [".ts", ".tsx"]
    com = ["//{}", "/*{}*/"]
}

language "Julia" {
    ext = [".jl"]
    com = ["#{}", "#={}=#"]
}

language "Go" {
    ext = [".go", ".mod", ".sum"]
    com = ["//{}", "/*{}*/"]
}

language "C" {
    ext = [".c", ".h"]
    com = ["//{}", "/*{}*/"]
}

language "C++" {
    ext = [".cpp", ".hpp", ".cc", ".cxx", ".hh", ".hxx"]
    com = ["//{}", "/*{}*/"]
}

language "Dart" {
    ext = [".dart"]
    com = ["//{}", "/*{}*/"]
}

language "D" {
    ext = [".d"]
    com = ["//{}", "/*{}*/"]
}

language "Rust" {
    ext = [".rs"]
    com = ["//{}", "/*{}*/"]
}

language "Zig" {
    ext = [".zig"]
    com = ["//{}"]
}

language "Nim" {
    ext = [".nim"]
    com = ["#{}"]
}

language "Crystal" {
    ext = [".cr"]
    com = ["#{}"]
}

language "Java" {
    ext = [".java"]
    com = ["//{}", "/*{}*/"]
}

language "Kotlin" {
    ext = [".kt", ".kts"]
    com = ["//{}", "/*{}*/"]
}

language "C#" {
    ext = [".cs", ".csx"]
    com = ["//{}", "/*{}*/"]
}

language "Ares Framework Rcfile" {
    ext = [".aresrc"]
    com = ["#{}"]
}

language "Ares Framework Goscript" {
    ext = [".gs"]
    com = ["//{}", "/*{}*/"]
}

language "Ares Framework LLSI Init" {
    ext = [".init"]
    com = ["//{}"]
}

language "Ares Framework LLSI Module" {
    ext = [".llsi"]
    com = ["#{}"]
}

language "Ares Framework Shell Module" {
    ext = [".shx"]
    com = ["#{}"]
}

language "Ares Framework Acon Syntax Definition" {
    ext = [".syntax"]
    com = ["//{}"]
}

language "Ares Framework Acon" {
    ext = [".acon"]
    com = ["//{}"]
}

language "Ares Framework Cobf Charmap" {
    ext = [".cobf"]
    com = ["//{}"]
}

language "HTML" {
    ext = [".html", ".htm"]
    com = ["<!--{}-->"]
}

language "CSS" {
    ext = [".css"]
    com = ["/*{}*/"]
}

language "SCSS" {
    ext = [".scss"]
    com = ["//{}", "/*{}*/"]
}

language "Sass" {
    ext = [".sass"]
    com = ["//{}", "/*{}*/"]
}

language "Vue" {
    ext = [".vue"]
    com = ["<!--{}-->"]
}

language "Svelte" {
    ext = [".svelte"]
    com = ["<!--{}-->"]
}

language "YAML" {
    ext = [".yaml", ".yml"]
    com = ["#{}"]
}

language "TOML" {
    ext = [".toml"]
    com = ["#{}"]
}

language "JSON" {
    ext = [".jsonc", ".json"]
    com = []
}

language "INI" {
    ext = [".ini"]
    com = ["#{}", ";{}"]
}

language "CFG" {
    ext = [".cfg"]
    com = ["#{}", ";{}"]
}

language "Conf" {
    ext = [".conf"]
    com = ["#{}"]
}

language "Swift" {
    ext = [".swift"]
    com = ["//{}", "/*{}*/"]
}

language "PHP" {
    ext = [".php"]
    com = ["//{}", "#{}", "/*{}*/"]
}

language "Elixir" {
    ext = [".ex", ".exs"]
    com = ["#{}"]
}

language "Erlang" {
    ext = [".erl", ".hrl"]
    com = ["%%{}"]
}

language "Haskell" {
    ext = [".hs"]
    com = ["--{}", "{-{}-}"]
}

language "Scala" {
    ext = [".scala", ".sc"]
    com = ["//{}", "/*{}*/"]
}

language "R" {
    ext = [".r", ".R"]
    com = ["#{}"]
}

language "SQL" {
    ext = [".sql"]
    com = ["--{}", "/*{}*/"]
}

language "Git Ignore" {
    ext = [".gitignore"]
    com = ["#{}"]
}

language "Git Attributes" {
    ext = [".gitattributes"]
    com = ["#{}"]
}

language "Markdown" {
    ext = [".md"]
    com = ["<!--{}-->"]
}

language "Text" {
    ext = [".txt"]
    com = []
}

language "LST" {
    ext = [".lst"]
    com = ["#{}"]
}

language "HCL" {
    ext = [".hcl"]
    com = ["#{}", "//{}"]
}

language "Micro Editor Config" {
    ext = [".micro"]
    com = ["#{}"]
}

language "Hash" {
    ext = [".hash"]
    com = []
}

language "RCfile" {
    ext = [".rc"]
    com = ["#{}"]
}

language "Powershell" {
    ext = [".ps1", ".psm1", ".psd1"]
    com = ["#{}", "<#{}#>"]
}

language "Batch" {
    ext = [".bat", ".cmd"]
    com = ["REM {}"]
}

language "Vim Script" {
    ext = [".vim"]
    com = ["\"{}"]
}

language "Clojure" {
    ext = [".clj", ".cljs", ".cljc", ".edn"]
    com = [";;{}"]
}

language "OCaml" {
    ext = [".ml", ".mli"]
    com = ["(*{}*)"]
}

language "F#" {
    ext = [".fs", ".fsi", ".fsx"]
    com = ["//{}", "(*{}*)"]
}

language "Assembly" {
    ext = [".asm", ".s"]
    com = [";{}", "//{}"]
}

language "Reason" {
    ext = [".re", ".rei"]
    com = ["//{}", "/*{}*/"]
}

language "Less" {
    ext = [".less"]
    com = ["//{}", "/*{}*/"]
}

language "Stylus" {
    ext = [".styl"]
    com = ["//{}", "/*{}*/"]
}

language "Astro" {
    ext = [".astro"]
    com = ["<!--{}-->", "//{}"]
}

language "MDX" {
    ext = [".mdx"]
    com = ["{/*{}*/}"]
}

language "Handlebars" {
    ext = [".hbs", ".handlebars"]
    com = ["{{!{}}}"]
}

language "Pug" {
    ext = [".pug"]
    com = ["//{}", "//-{}"]
}

language "Jade" {
    ext = [".jade"]
    com = ["//{}", "//-{}"]
}

language "Nunjucks" {
    ext = [".njk"]
    com = ["{#{}#}"]
}

language "Jinja" {
    ext = [".jinja", ".jinja2"]
    com = ["{#{}#}"]
}

language "Twig" {
    ext = [".twig"]
    com = ["{#{}#}"]
}

language "Dockerfile" {
    ext = [".dockerfile"]
    com = ["#{}"]
}

language "Docker Ignore" {
    ext = [".dockerignore"]
    com = ["#{}"]
}

language "ENV" {
    ext = [".env", ".env.local", ".env.example"]
    com = ["#{}"]
}

language "Makefile" {
    ext = [".mk"]
    com = ["#{}"]
}

language "Nginx" {
    ext = [".nginx", ".nginxconf"]
    com = ["#{}"]
}

language "GraphQL" {
    ext = [".graphql", ".gpl"]
    com = ["#{}"]
}

language "Protobuf" {
    ext = [".proto"]
    com = ["//{}", "/*{}*/"]
}

language "Pascal" {
    ext = [".pas", ".pp", ".inc"]
    com = ["//{}", "(*{}*)", "({{})"]
}

language "Odin" {
    ext = [".odin"]
    com = ["//{}", "/*{}*/"]
}

language "V" {
    ext = [".v"]
    com = ["//{}", "/*{}*/"]
}

language "Vala" {
    ext = [".vala", ".vapi"]
    com = ["//{}", "/*{}*/"]
}

language "Fortran" {
    ext = [".f90", ".f95", ".f03", ".f08", ".f", ".for"]
    com = ["!{}"]
}

language "Solidity" {
    ext = [".sol"]
    com = ["//{}", "/*{}*/"]
}

language "Ada" {
    ext = [".adb", ".ads"]
    com = ["--{}"]
}

language "Scheme" {
    ext = [".scm", ".ss"]
    com = [";{}"]
}

language "Lisp" {
    ext = [".lisp", ".cl", ".lsp"]
    com = [";;{}", "#|{}|#"]
}

language "GDScript" {
    ext = [".gd"]
    com = ["#{}"]
}

language "ActionScript" {
    ext = [".as"]
    com = ["//{}", "/*{}*/"]
}

language "C3" {
    ext = [".c3"]
    com = ["//{}", "/*{}*/"]
}

language "Verilog" {
    ext = [".v", ".vh", ".sv", ".svh"]
    com = ["//{}", "/*{}*/"]
}

language "VHDL" {
    ext = [".vhd", ".vhdl"]
    com = ["--{}"]
}

language "COBOL" {
    ext = [".cob", ".cbl", ".cpy"]
    com = ["*>{}"]
}

language "Haxe" {
    ext = [".hx"]
    com = ["//{}", "/*{}*/"]
}

language "Raku" {
    ext = [".raku", ".rakumod", ".rakutest", ".p6", ".pm6"]
    com = ["#{}", "#=`{}`"]
}

language "Cirru" {
    ext = [".cirru"]
    com = ["--{}"]
}

language "Forth" {
    ext = [".fth", ".4th", ".forth"]
    com = ["\\ {}", "( {} )"]
}

language "MATLAB" {
    ext = [".m"]
    com = ["%%{}"]
}

language "Apex" {
    ext = [".cls", ".trigger"]
    com = ["//{}", "/*{}*/"]
}

language "Tcl" {
    ext = [".tcl"]
    com = ["#{}"]
}

language "SystemVerilog" {
    ext = [".sv", ".svh"]
    com = ["//{}", "/*{}*/"]
}

language "Smalltalk" {
    ext = [".st"]
    com = ["\"{}\""]
}

language "AutoHotkey" {
    ext = [".ahk"]
    com = [";{}", "/*{}*/"]
}

language "GLSL" {
    ext = [".glsl", ".vert", ".frag", ".geom", ".comp"]
    com = ["//{}", "/*{}*/"]
}

language "HLSL" {
    ext = [".hlsl", ".fx", ".fxh"]
    com = ["//{}", "/*{}*/"]
}

language "XML" {
    ext = [".xml", ".xsl", ".xslt", ".xsd"]
    com = ["<!--{}-->"]
}

language "SVG" {
    ext = [".svg"]
    com = ["<!--{}-->"]
}

language "LaTeX" {
    ext = [".tex", ".sty", ".cls"]
    com = ["%%{}"]
}

language "AsciiDoc" {
    ext = [".adoc", ".asciidoc"]
    com = ["//{}"]
}

language "reStructuredText" {
    ext = [".rst"]
    com = [".. {}"]
}

language "Nix" {
    ext = [".nix"]
    com = ["#{}"]
}

language "Starlark" {
    ext = [".bzl", ".star"]
    com = ["#{}"]
}

language "Jsonnet" {
    ext = [".jsonnet", ".libsonnet"]
    com = ["//{}", "/*{}*/", "#{}"]
}

language "CUE" {
    ext = [".cue"]
    com = ["//{}"]
}

language "Thrift" {
    ext = [".thrift"]
    com = ["//{}", "/*{}*/"]
}

language "Elm" {
    ext = [".elm"]
    com = ["--{}"]
}

language "PureScript" {
    ext = [".purs"]
    com = ["--{}", "{-{}-}"]
}

language "Gleam" {
    ext = [".gleam"]
    com = ["//{}"]
}

language "MoonBit" {
    ext = [".mbt"]
    com = ["//{}"]
}

language "Lean" {
    ext = [".lean"]
    com = ["--{}"]
}

language "Red" {
    ext = [".red"]
    com = [";{}"]
}

language "Objective-C" {
    ext = [".m"]
    com = ["//{}", "/*{}*/"]
}

language "Objective-C++" {
    ext = [".mm"]
    com = ["//{}", "/*{}*/"]
}

language "Cypher" {
    ext = [".cyp", ".cypher"]
    com = ["//{}"]
}

language "Prisma" {
    ext = [".prisma"]
    com = ["//{}"]
}

// Copyright (c) 2026 Senzdetta