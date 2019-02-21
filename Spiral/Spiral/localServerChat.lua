module("localServerChat",package.seeall)
--注意lua5.3和lua5.1的区别
--https://my.oschina.net/u/186074/blog/785298
--localServerChat = {}
function localServerChat()
	print("hello i am localServerChat")
	local version = LSystem.getVersion()
	print("this version is " .. version)
	local res = LSystem.setVersionId(20190217)
	print("setVersion res " .. res)
	local version = LSystem.getVersion()
	print("this version is " .. version)
	--print("热更完毕 " .. hello)
end
--return localServerChat