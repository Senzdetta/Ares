{{ shebang::luajit }}
-- https://github.com/Zeronetsec/Ares

local lib_dir = os.getenv("__lib__") or "."
package.path = lib_dir .. "/?.lua;" ..
    lib_dir .. "/?/init.lua;" ..
    lib_dir .. "/yumipr/lua/?.lua;" ..
    package.path

local color = require("std.lua.color")
local gitbranch = require("yumipr.lua.gitbranch")
local gettime = require("yumipr.lua.gettime")
local geteuid = require("yumipr.lua.geteuid")
local setprompt = require("yumipr.lua.setprompt")
local readline = require("yumipr.lua.readline")
local posixvar = require("yumipr.lua.posixvar")
local getcwd = require("yumipr.lua.getcwd")

local branch_icons = {
    ["main"] = "",
    ["master"] = "",
    ["dev"] = "",
}

local branch_name = gitbranch.gitbranch()
local branch_display = ""
if branch_name then
    local icon = branch_icons[branch_name] or "branch:"
    branch_display = icon
end

local time_icons = {
    [0] = "☾",
    [1] = "⋄",
    [3] = "𓄃",
    [5] = "⚔",
    [7] = "✈︎",
    [12] = "𓃵",
    [15] = "☯︎",
    [20] = "𖤐",
    [23] = "𓄀",
}

local ctime = tonumber(gettime.gettime("%H")) or 0
local time_display = time_icons[ctime] or "𖤍"

local prsyms = {
    [0] = "#",
    [2000] = "≫",
}

local prcurrent = geteuid.geteuid() or 1000
local euid_display = prsyms[prcurrent] or "$"

local pvar = posixvar.posixvar
local function get_env(key)
    return pvar[key] or os.getenv(key)
end

local abs_cwd = pvar.PWD or os.getenv("PWD")
    or getcwd.getcwd({
        collapse_home = false,
        trim = 0,
    })
    or ""

local prompt_dirtrim = tonumber(
        get_env("PROMPT_DIRTRIM")
    )
    or 2

local cwd_trimmed = getcwd.getcwd({
    collapse_home = true,
    trim = prompt_dirtrim,
})

local env_home = get_env("HOME")
    or get_env("home")

local env_prefix = get_env("PREFIX")
    or get_env("prefix")

local env_root = get_env("__aresroot__")
    or (env_prefix .. "/opt/ares")

local env_config = get_env("__config__")
    or (env_prefix .. "/opt/ares/config")

local env_bin = get_env("__bin__")
    or (env_prefix .. "/bin")

local dircons = {}
local function add_path(path, col)
    if not path or path == "" then return end
    dircons[path] = col
    if path:sub(1, 31) == "/data/data/com.termux/files/usr" then
        local short_path = "/usr" .. path:sub(32)
        dircons[short_path] = col
    end
end

add_path("/", color.RR)
add_path("/root", color.RR)
add_path(env_root, color.RR)

add_path("/etc", color.GG)
add_path(env_prefix .. "/etc", color.GG)
add_path(env_config, color.GG)

add_path("/bin", color.CC)
add_path("/sbin", color.CC)
add_path("/xbin", color.CC)
add_path("/system/bin", color.CC)
add_path("/system/xbin", color.CC)
add_path(env_prefix .. "/bin", color.CC)
add_path(env_prefix .. "/sbin", color.CC)
add_path(env_bin, color.CC)

add_path("/usr", color.BB)
add_path(env_prefix, color.BB)

add_path("~", color.YY)
add_path(env_home, color.YY)

local dir_color = nil
local max_len = -1

for path_prefix, col in pairs(dircons) do
    if abs_cwd == path_prefix or abs_cwd:sub(
        1, #path_prefix + 1
    ) == (path_prefix .. "/") then
        if #path_prefix > max_len then
            max_len = #path_prefix
            dir_color = col
        end
    end
end

dir_color = dir_color or color.YY

local host = "Framework"
local user = "Ares"

local err_code = tonumber(
    pvar.exit_code
        or os.getenv("exit_code")
        or pvar.err
        or 0
) or 0

local line_no = tostring(
    pvar.LINENO
        or os.getenv("LINENO")
        or pvar.lineno
        or 1
)

local out = {}

if err_code > 0 then
    out = {
        readline.readline("\x1b[?25h") .. "\n",
        readline.readline("\x1b[38;5;244m") .. "┌──(",
        readline.readline(color.R)  .. user,
        readline.readline("\x1b[38;5;244m") .. "(",
        readline.readline(color.B)  .. time_display,
        readline.readline("\x1b[38;5;244m") .. ")",
        readline.readline(color.R)  .. host,
        readline.readline("\x1b[38;5;244m") .. ")-(",
        readline.readline(dir_color) .. cwd_trimmed,
        readline.readline("\x1b[38;5;244m") .. ") -> (",
        readline.readline(color.GG) .. line_no,
        readline.readline("\x1b[38;5;244m") .. ":",
        readline.readline(color.GG) .. tostring(err_code),
        readline.readline("\x1b[38;5;244m") .. ")",
        readline.readline(color.N) .. "\n",
        readline.readline("\x1b[38;5;244m") .. "└──",
        readline.readline(color.R)  .. euid_display,
        readline.readline(color.N) .. " ",
    }
elseif branch_name ~= nil and branch_name ~= "" then
    out = {
        readline.readline("\x1b[?25h") .. "\n",
        readline.readline("\x1b[38;5;244m") .. "┌──(",
        readline.readline(color.R)  .. user,
        readline.readline("\x1b[38;5;244m") .. "(",
        readline.readline(color.YY) .. time_display,
        readline.readline("\x1b[38;5;244m") .. ")",
        readline.readline(color.R)  .. host,
        readline.readline("\x1b[38;5;244m") .. ")-(",
        readline.readline(dir_color) .. cwd_trimmed,
        readline.readline("\x1b[38;5;244m") .. ") -> (",
        readline.readline(color.YY) .. branch_display .. " ",
        readline.readline(color.GG) .. branch_name,
        readline.readline("\x1b[38;5;244m") .. ")",
        readline.readline(color.N) .. "\n",
        readline.readline("\x1b[38;5;244m") .. "└──",
        readline.readline(color.GG) .. euid_display,
        readline.readline(color.N) .. " ",
    }
else
    out = {
        readline.readline("\x1b[?25h") .. "\n",
        readline.readline("\x1b[38;5;244m") .. "┌──(",
        readline.readline(color.R)  .. user,
        readline.readline("\x1b[38;5;244m") .. "(" .. time_display .. ")",
        readline.readline(color.R)  .. host,
        readline.readline("\x1b[38;5;244m") .. ")-(",
        readline.readline(dir_color) .. cwd_trimmed,
        readline.readline("\x1b[38;5;244m") .. ")",
        readline.readline(color.N) .. "\n",
        readline.readline("\x1b[38;5;244m") .. "└──",
        readline.readline(color.WW) .. euid_display,
        readline.readline(color.N) .. " ",
    }
end

setprompt.setprompt(table.concat(out, ""))

-- Copyright (c) 2026 Zeronetsec