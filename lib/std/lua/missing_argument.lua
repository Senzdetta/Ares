-- https://github.com/Senzdetta/Ares

local color = require("color")
local m = {}

function m.missing_argument(tool_name)
    io.write(
        string.format(
            "%s[!] %sMissing argument!\n",
            color.R, color.N
        )
    )

    io.write(
        string.format(
            "%s[!] %sTry: %saresdoc %s%s%s\n",
            color.R, color.N, color.GG, color.CC, tool_name, color.N
        )
    )
end

return m

-- Copyright (c) 2026 Senzdetta