package.path  = ";.\\?.lua";
require("localServerChat")
--require("system.ChatSystem.crossServerChat")
print(package.path)
print("road charSystem success!!")

--crossServerChat.crossServerChat()
localServerChat.localServerChat()