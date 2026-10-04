-- https://github.com/Senzdetta/Ares

local ffi = require("ffi")

pcall(ffi.cdef, [[
    char *getcwd(char *buf, size_t size);
]])

local yumipr = {}

function yumipr.getcwd(options)
    options = options or {}
    local cwd = nil

    local env_pwd = os.getenv("PWD")
    if env_pwd and env_pwd ~= "" then
        cwd = env_pwd
    else
        local success, res = pcall(function()
            local buf = ffi.new("char[1024]")
            local ptr = ffi.C.getcwd(buf, 1024)
            if ptr ~= nil then
                return ffi.string(ptr)
            end
        end)
        cwd = (success and res and res ~= "") and res or "."
    end

    local is_home_relative = false
    if options.collapse_home ~= false then
        local home = os.getenv("HOME")
        if home and home ~= "" then
            local escaped_home = home:gsub(
                "([%^%$%(%)%%%.%[%]%*%+%-%?])",
                "%%%1"
            )

            if cwd:find("^" .. escaped_home) then
                cwd = cwd:gsub("^" .. escaped_home, "~")
                is_home_relative = true
            end
        end
    end

    local trim_limit = options.trim or tonumber(
        os.getenv("PROMPT_DIRTRIM")
    )

    if trim_limit and trim_limit > 0 then
        if cwd ~= "~" and cwd ~= "/" then
            local parts = {}
            for part in cwd:gmatch("[^/]+") do
                if part ~= "~" then
                    table.insert(parts, part)
                end
            end

            if #parts > trim_limit then
                local trimmed_parts = {}
                for i = #parts - trim_limit + 1, #parts do
                    table.insert(trimmed_parts, parts[i])
                end

                if is_home_relative or cwd:sub(1, 1) == "~" then
                    cwd = "~/.../" .. table.concat(
                        trimmed_parts, "/"
                    )
                else
                    cwd = "/.../" .. table.concat(
                        trimmed_parts, "/"
                    )
                end
            end
        end
    end
    return cwd
end

return yumipr

-- Copyright (c) 2026 Senzdetta