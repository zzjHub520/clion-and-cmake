cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
list(APPEND CMAKE_MESSAGE_CONTEXT src)
message("TOP=${TOP}")
set(src_var "this is sub variable" PARENT_SCOPE)
message("src_var=${src_var}")

option(is_top OFF "is top dir")
message("is_top=${is_top}")