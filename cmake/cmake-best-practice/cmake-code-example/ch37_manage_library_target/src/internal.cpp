//
// Created by 1 on 2022/10/11.
//

#include "internal.hpp"
#include <iostream>

namespace hello::details {
    void print_impl(const std::string &name) {
        std::cout << "Hello " << name << " from a static libray\n";
    }
}