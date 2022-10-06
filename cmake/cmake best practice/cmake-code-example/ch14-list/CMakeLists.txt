cmake_minimum_required(VERSION 3.23)
project(ch14_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(ch14_list main.cpp)

message("---------------- temp test start ----------------------")
## 输出message, 加双引号和和不加双引号是有区别的
#set(my_list a b c d e)
#message("${my_list}") # a;b;c;d;e
#message(${my_list})   # abcde

############## reader ####################
#set(my_list a b c d e)
## 读取列表长度
## list(LENGTH <list> <output variable>)
#list(LENGTH my_list len)
#message("len=${len}")
#
## 读取元素
##list(GET <list> <element index> [<element index> ...] <output variable>)
#list(GET my_list 0 1 elem)
#message("elem=${elem}")
#
## 粘连列表
## list(JOIN <list> <glue> <output variable>)
#list(JOIN my_list - out_var)
#message("out_var=${out_var}")
#
## 子列表
## list(SUBLIST <list> <begin> <length> <output variable>)
#list(SUBLIST my_list 1 3 out_var)
#message("out_var=${out_var}")

############## search ###########################
#set(my_list a b c d e)
## list(FIND <list> <value> <output variable>)
#list(FIND my_list d out_var) # 找不到返回-1，找到返回下标
#message("out_var=${out_var}")

############## modification ###########################
# 追加元素
set(my_list a b c d e)
# list(APPEND <list> [<element> ...])
list(APPEND my_list 1 2;3 4)
message("my_list=${my_list}")

# 正则表达式
set(my_list a b c d e)
# list(FILTER <list> <INCLUDE|EXCLUDE> REGEX <regular_expression>)
list(FILTER my_list INCLUDE REGEX [0-9])
message("my_list=${my_list}")

# 插入元素
set(my_list a b c d e)
# list(INSERT <list> <element_index> <element> [<element> ...])
list(INSERT my_list 0 @ * & )
message("my_list=${my_list}")

# 弹出元素
set(my_list a b c d e)
# list(POP_BACK <list> [<out-var>...])
list(POP_BACK my_list ele1 ele2)
message("${ele1} ${ele2}")
# list(POP_FRONT <list> [<out-var>...])
list(POP_FRONT my_list ele1 ele2)
message("${ele1} ${ele2}")

# 头部追加
set(my_list a b c d e)
# list(PREPEND <list> [<element> ...])
list(PREPEND my_list ele1 ele2)
message("${my_list}")

# 移除元素
set(my_list a b c d e)
# list(REMOVE_ITEM <list> <value> [<value> ...])
list(REMOVE_ITEM my_list a b)
message("${my_list}")
# list(REMOVE_AT <list> <index> [<index> ...])
list(REMOVE_AT my_list 0 1)
message("${my_list}")
# list(REMOVE_DUPLICATES <list>)
# 删除重复元素
set(mylist a a b b c c d d)
list(REMOVE_DUPLICATES mylist)
message("${mylist}")

# 转换
#list(TRANSFORM <list> <ACTION> [<SELECTOR>] [OUTPUT_VARIABLE <output variable>])
set(MY_LIST 1 2 3 4 5 6 7 8 9)
list(TRANSFORM MY_LIST PREPEND  he-)
list(TRANSFORM MY_LIST APPEND  0)
message("${MY_LIST}")

set(my_list a Bb c dD e Ff)
list(TRANSFORM my_list TOLOWER )
message("${my_list}")

list(TRANSFORM my_list APPEND "x" FOR 2 5 1 OUTPUT_VARIABLE A_out)
message("${A_out}")
message("${my_list}")

# 排序
set(my_list a B c D e fF)
message("${my_list}")
list(REVERSE my_list)
message("${my_list}")
list(SORT my_list COMPARE STRING)
message("${my_list}")


message("---------------- temp test end ------------------------")




