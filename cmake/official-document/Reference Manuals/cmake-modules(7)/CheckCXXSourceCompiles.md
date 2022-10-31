# CheckCXXSourceCompiles

Check if given C++ source compiles and links into an executable.

- **check_cxx_source_compiles**

  ```cmake
  check_cxx_source_compiles(<code> <resultVar>
                            [FAIL_REGEX <regex1> [<regex2>...]])
  ```

  Check that the source supplied in `<code>` can be compiled as a C++ source file and linked as an executable (so it must contain at least a `main()` function). The result will be stored in the internal cache variable specified by `<resultVar>`, with a boolean true value for success and boolean false for failure. If `FAIL_REGEX` is provided, then failure is determined by checking if anything in the output matches any of the specified regular expressions.

  The underlying check is performed by the [`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile) command. The compile and link commands can be influenced by setting any of the following variables prior to calling `check_cxx_source_compiles()`:

  - `CMAKE_REQUIRED_FLAGS`

    Additional flags to pass to the compiler. Note that the contents of [`CMAKE_CXX_FLAGS`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_FLAGS.html#variable:CMAKE__FLAGS) and its associated configuration-specific variable are automatically added to the compiler command before the contents of `CMAKE_REQUIRED_FLAGS`.

  - `CMAKE_REQUIRED_DEFINITIONS`

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of compiler definitions of the form `-DFOO` or `-DFOO=bar`. A definition for the name specified by `<resultVar>` will also be added automatically.

  - `CMAKE_REQUIRED_INCLUDES`

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of header search paths to pass to the compiler. These will be the only header search paths used by `try_compile()`, i.e. the contents of the [`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_dir/INCLUDE_DIRECTORIES.html#prop_dir:INCLUDE_DIRECTORIES) directory property will be ignored.

  - `CMAKE_REQUIRED_LINK_OPTIONS`

    *New in version 3.14.*

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of options to add to the link command (see [`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile) for further details).

  - `CMAKE_REQUIRED_LIBRARIES`

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of libraries to add to the link command. These can be the name of system libraries or they can be [Imported Targets](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets) (see [`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile) for further details).

  - `CMAKE_REQUIRED_QUIET`

    *New in version 3.1.*

    If this variable evaluates to a boolean true value, all status messages associated with the check will be suppressed.

  The check is only performed once, with the result cached in the variable named by `<resultVar>`. Every subsequent CMake run will re-use this cached value rather than performing the check again, even if the `<code>` changes. In order to force the check to be re-evaluated, the variable named by `<resultVar>` must be manually removed from the cache.