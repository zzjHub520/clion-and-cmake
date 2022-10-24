//
// Created by 1 on 2022/10/11.
//

#ifndef CMAKE_CODE_EXAMPLE_HELLO_HPP
#define CMAKE_CODE_EXAMPLE_HELLO_HPP

#include <string>

namespace hello {
    class Hello {
    public:
        Hello(const std::string &name) : m_name(name) {}

        void greet() const;

    private:
        const std::string m_name;
    };
}

#endif //CMAKE_CODE_EXAMPLE_HELLO_HPP
