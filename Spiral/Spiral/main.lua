
module("main", package.seeall)
function require_ex(_mname)
	print(string.format("require_ex = %s",_mname))
	if package.loaded[_mname] then
		print(string.format("require_ex module[%s] reload",_mname))
	end
	package.loaded[_mname] = nil
	require(_mname)
end


--require_ex("test")