//
// Created by zzj on 2022/10/16.
//
#include <iostream>

#ifndef GIT_VERSION
#define GIT_VERSION unknown
#endif

using namespace std;

const char git_rev[] = GIT_VERSION;

int main(int argc, const char *argv[]) {
    std::cout << "Hello C++ " << __cplusplus << std::endl;
    cout << "git version: " << git_rev << endl;
    return 0;
}
