# CheckIncludeFiles

Provides a macro to check if a list of one or more header files can be included together.

- **CHECK_INCLUDE_FILES**

  ```cmake
  CHECK_INCLUDE_FILES("<includes>" <variable> [LANGUAGE <language>])
  ```

  Check if the given `<includes>` list may be included together in a source file and store the result in an internal cache entry named `<variable>`. Specify the `<includes>` argument as a [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of header file names.

  If `LANGUAGE` is set, the specified compiler will be used to perform the check. Acceptable values are `C` and `CXX`. If not set, the C compiler will be used if enabled. If the C compiler is not enabled, the C++ compiler will be used if enabled.

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

See modules [`CheckIncludeFile`](https://cmake.org/cmake/help/latest/module/CheckIncludeFile.html#module:CheckIncludeFile) and [`CheckIncludeFileCXX`](https://cmake.org/cmake/help/latest/module/CheckIncludeFileCXX.html#module:CheckIncludeFileCXX) to check for a single header file in `C` or `CXX` languages.