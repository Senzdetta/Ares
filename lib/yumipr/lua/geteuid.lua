-- https://github.com/Senzdetta/Ares

local ffi = require("ffi")

pcall(ffi.cdef, [[
    typedef uint32_t uid_t;
    uid_t geteuid(void);
]])

local yumipr = {}

function yumipr.geteuid()
    local success, euid = pcall(function()
        return tonumber(ffi.C.geteuid())
    end)

    if success and euid then 
        return euid 
    end

    local env_euid = os.getenv("EUID") or os.getenv("UID")
    if env_euid then 
        return tonumber(env_euid) 
    end

    return nil
end

return yumipr

-- Copyright (c) 2026 Senzdetta