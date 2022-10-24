cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(ch55_execute_process)

#[==[
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
]==]

# 以下变量可以不赋值，改用cmake的配置的时候，来指定  cmake -S . -B build -DVAR=1 -DVAR2=2 -DVAR3=3
set(VAR "var1")
set(VAR2 "var2")
set(VAR3 " ")
set(VAR4 "")

#configure_file(version.h.in version.h)
#configure_file(version.h.in version.h NO_SOURCE_PERMISSIONS)
# OWNER
# GROUP
# OTHER
#configure_file(version.h.in version.h FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ)
configure_file(version.h.in version.h @ONLY)
