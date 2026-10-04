-- https://github.com/Senzdetta/Ares

local yumipr = {}

function yumipr.setprompt(prompt)
    if prompt == nil then
        error("yumipr.setprompt: prompt content cannot be nil!")
    end

    io.write(tostring(prompt))
    io.stdout:flush()
end

return yumipr

-- Copyright (c) 2026 Senzdetta