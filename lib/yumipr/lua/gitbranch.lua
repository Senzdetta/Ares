-- https://github.com/Zeronetsec/Ares

local yumipr = {}

function yumipr.gitbranch()
    local f = io.open(".git/HEAD", "r")
    if not f then return nil end

    local content = f:read("*l")
    f:close()

    if not content then return nil end

    local branch = content:match("^ref:%s*refs/heads/(.+)$")
    if branch then
        return branch
    end

    if #content >= 7 then
        return content:sub(1, 7)
    end

    return content
end

return yumipr

-- Copyright (c) 2026 Zeronetsec