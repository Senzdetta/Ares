-- https://github.com/Zeronetsec/Ares

local yumipr = {}
yumipr.posixvar = {}

local env_map = {
    lineno = "LINENO",
    err = "?",
    pid = "$",
    user = "USER",
    pwd = "PWD",
    shell = "SHELL",
    prefix = "PREFIX",
    home = "HOME",
    hostname = "HOSTNAME",
    shlvl = "SHLVL",
    euid = "EUID",
    ppid = "PPID",
    uid = "UID",
    term = "TERM",
    prdtrim = "PROMPT_DIRTRIM",
    colorterm = "COLORTERM"
}

setmetatable(yumipr.posixvar, {
    __index = function(t, key)
        local env_name = env_map[key] or key
        local val = os.getenv(env_name)

        if key == "prefix" and (val == nil or val == "") then
            return "/usr"
        end

        return val
    end
})

return yumipr

-- Copyright (c) 2026 Zeronetsec