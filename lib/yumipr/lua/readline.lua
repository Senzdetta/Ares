-- https://github.com/Zeronetsec/Ares

local yumipr = {}

function yumipr.readline(ipt)
    if ipt == nil then
        error("yumipr.readline: input cannot be nil!")
    end
    return "\001" .. tostring(ipt) .. "\002"
end

return yumipr

-- Copyright (c) 2026 Zeronetsec