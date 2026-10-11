-- https://github.com/Senzdetta/Ares

local color = require("color")
local m = {}

function m.invalid_option(invarg, command)
    io.write(
        string.format(
            "%s[!] %sInvalid option: %s%s%s\n",
            color.R, color.N, color.GG, invarg, color.N
        )
    )

    io.write(
        string.format(
            "%s[!] %sTry: %saresdoc %s%s%s\n",
            color.R, color.N, color.GG, color.CC, command, color.N
        )
    )
end

return m

-- Copyright (c) 2026 Senzdetta