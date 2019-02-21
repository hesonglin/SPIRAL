--package.path = package.path .. ";./?.lua;./Data/luaScript/?.lua;./Data/luaScript/system/ChatSystem/?.lua"
print(package.path)
local m = require("localServerChat")
--print(tostring(m))
--require("system.ChatSystem.crossServerChat")

print("road charSystem success!!")

--crossServerChat.crossServerChat()
--localServerChat.localServerChat()