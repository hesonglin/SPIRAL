package.path  = package.path .. ";.\\?.lua";

require("localServerChat")
require("main")
--require("test")
--require("system.ChatSystem.crossServerChat")
print(package.path)
print("road charSystem success!!")

--crossServerChat.crossServerChat()
--localServerChat.localServerChat()
--function test()
--	local test = require("localServerChat")
	--local m = require("test")
--	test.localServerChat()
	--m.show()
--end
--test()
localServerChat.localServerChat()
--test.show()
function rsf()
	print("chatSystem rsf")
	main.require_ex("localServerChat")
	localServerChat.localServerChat()
	
end