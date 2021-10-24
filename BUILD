cc_library(
	name = "static_vector",
	includes = ["include"],
	strip_include_prefix = "include",
	hdrs = glob(["include/*.hpp"]),
	visibility = [
		"//visibility:public",
	],
)

cc_test(
	name = "static_vector_ut",
	srcs = glob(["test/*.cpp", "test/*.hpp"]),
	deps =  [":static_vector"],
)

cc_binary(
	name = "sample",
	srcs = ["sample/sample.cpp"],
	deps = [":static_vector"],
)
