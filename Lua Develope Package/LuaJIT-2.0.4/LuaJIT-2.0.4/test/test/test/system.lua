require("test")
require("main")
print("load global function!!!!")
test.show()

function rsf()
	main.require_ex("test")
	test.show()
end
