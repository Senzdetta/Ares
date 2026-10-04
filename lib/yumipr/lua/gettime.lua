-- https://github.com/Senzdetta/Ares

local yumipr = {}

function yumipr.gettime(fmt)
    if fmt == nil or fmt == "" then
        fmt = "%H:%M:%S"
    end

    if type(fmt) ~= "string" then
        error("yumipr.gettime: format must be a string!")
    end

    return os.date(fmt)
end

return yumipr

-- Copyright (c) 2026 Senzdetta