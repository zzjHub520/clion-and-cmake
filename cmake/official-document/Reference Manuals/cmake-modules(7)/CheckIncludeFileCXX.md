# CheckIncludeFileCXX

Provides a macro to check if a header file can be included in `CXX`.

- **CHECK_INCLUDE_FILE_CXX**

  ```cmake
  CHECK_INCLUDE_FILE_CXX(<include> <variable> [<flags>])
  ```

  Check if the given `<include>` file may be included in a `CXX` source file and store the result in an internal cache entry named `<variable>`. The optional third argument may be used to add compilation flags to the check (or use `CMAKE_REQUIRED_FLAGS` below).

The following variables may be set before calling this macro to modify the way the check is run:

- `CMAKE_REQUIRED_FLAGS`

  string of compile command line flags.

- `CMAKE_REQUIRED_DEFINITIONS`

  a [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of macros to define (-DFOO=bar).

- `CMAKE_REQUIRED_INCLUDES`

  a [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of header search paths to pass to the compiler.

- `CMAKE_REQUIRED_LINK_OPTIONS`

  *New in version 3.14:* a [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of options to add to the link command.

- `CMAKE_REQUIRED_LIBRARIES`

  a [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of libraries to add to the link command. See policy [`CMP0075`](https://cmake.org/cmake/help/latest/policy/CMP0075.html#policy:CMP0075).

- `CMAKE_REQUIRED_QUIET`

  *New in version 3.1:* execute quietly without messages.

See modules [`CheckIncludeFile`](https://cmake.org/cmake/help/latest/module/CheckIncludeFile.html#module:CheckIncludeFile) and [`CheckIncludeFiles`](https://cmake.org/cmake/help/latest/module/CheckIncludeFiles.html#module:CheckIncludeFiles) to check for one or more `C` headers.