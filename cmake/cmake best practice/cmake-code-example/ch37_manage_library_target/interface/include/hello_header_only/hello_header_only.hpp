//
// Created by 1 on 2022/10/11.
//

#ifndef CMAKE_CODE_EXAMPLE_HELLO_HEADER_ONLY_HPP
#define CMAKE_CODE_EXAMPLE_HELLO_HEADER_ONLY_HPP

#include <iostream>
#include <string>

namespace hello_header_only{
    void print_hello(const std::string& name){
        std::cout << "Hello " << name << " from a header only libray\n";
    }
}

#endif //CMAKE_CODE_EXAMPLE_HELLO_HEADER_ONLY_HPP
