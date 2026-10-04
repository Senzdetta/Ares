-- https://github.com/Zeronetsec/Ares

local yumipr = {}

function yumipr.unwrap(ipt)
    if ipt == nil then
        error("yumipr.unwrap: input cannot be nil!")
    end

    local str = tostring(ipt)
    local content = str:match("^\001(.-)\002$")

    return content or str
end

return yumipr

-- Copyright (c) 2026 Zeronetsec