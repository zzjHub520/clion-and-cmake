//
// Created by 1 on 2022/10/11.
//

#include <hello/hello.hpp>

#include "internal.hpp"

namespace hello {
    void Hello::greet() const {
        details::print_impl(m_name);
    }
}