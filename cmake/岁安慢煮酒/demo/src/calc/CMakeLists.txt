add_library(addition STATIC addition.cpp)

install(TARGETS addition DESTINATION lib)
install(FILES addition.h DESTINATION include)


add_library(subtract SHARED subtract.cpp)

install(TARGETS subtract DESTINATION bin)
install(FILES subtract.h DESTINATION include)
