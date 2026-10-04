-- https://github.com/Zeronetsec/Ares

local ffi = require("ffi")

pcall(ffi.cdef, [[
    typedef uint32_t uid_t;
    typedef uint32_t gid_t;
    
    struct passwd {
        char *pw_name;
        char *pw_passwd;
        uid_t pw_uid;
        gid_t pw_gid;
        char *pw_gecos;
        char *pw_dir;
        char *pw_shell;
    };

    uid_t geteuid(void);
    struct passwd *getpwuid(uid_t uid);
]])

local yumipr = {}

function yumipr.getuser()
    local success, username = pcall(function()
        local euid = ffi.C.geteuid()
        local pw = ffi.C.getpwuid(euid)
        if pw ~= nil and pw.pw_name ~= nil then
            return ffi.string(pw.pw_name)
        end
    end)

    if success and username and username ~= "" then
        return username
    end

    local env_user = os.getenv("USER") or os.getenv("LOGNAME")
    if env_user and env_user ~= "" then
        return env_user
    end

    return "unknown"
end

return yumipr

-- Copyright (c) 2026 Zeronetsec