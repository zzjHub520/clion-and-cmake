list(APPEND CMAKE_MESSAGE_CONTEXT src)

add_executable(main main.cpp)
add_executable(Amain ALIAS main)

if (TARGET Amain)
    message("---------------")
endif ()