-- https://github.com/Zeronetsec/Ares

local yumipr = {}

local function read_fline(path)
    local f = io.open(path, "r")
    if not f then return nil end

    local line = f:read("*l")
    f:close()

    return line and line:match("^%s*(.-)%s*$")
end

function yumipr.gethost()
    local host = read_fline("/etc/hostname") 
        or read_fline("/proc/sys/kernel/hostname")

    if host and host ~= "" then
        return host
    end

    local env_host = os.getenv("HOSTNAME") or os.getenv("HOST")
    if env_host and env_host ~= "" then
        return env_host
    end

    return "localhost"
end

return yumipr

-- Copyright (c) 2026 Zeronetsec