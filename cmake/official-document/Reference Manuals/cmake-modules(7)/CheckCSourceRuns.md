# CheckCSourceRuns

Check if given C source compiles and links into an executable and can subsequently be run.

- **check_c_source_runs**

  ```cmake
  check_c_source_runs(<code> <resultVar>)
  ```

  Check that the source supplied in `<code>` can be compiled as a C source file, linked as an executable and then run. The `<code>` must contain at least a `main()` function. If the `<code>` could be built and run successfully, the internal cache variable specified by `<resultVar>` will be set to 1, otherwise it will be set to an value that evaluates to boolean false (e.g. an empty string or an error message).

  The underlying check is performed by the [`try_run()`](https://cmake.org/cmake/help/latest/command/try_run.html#command:try_run) command. The compile and link commands can be influenced by setting any of the following variables prior to calling `check_c_source_runs()`:

  - `CMAKE_REQUIRED_FLAGS`

    Additional flags to pass to the compiler. Note that the contents of [`CMAKE_C_FLAGS`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_FLAGS.html#variable:CMAKE__FLAGS) and its associated configuration-specific variable are automatically added to the compiler command before the contents of `CMAKE_REQUIRED_FLAGS`.

  - `CMAKE_REQUIRED_DEFINITIONS`

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of compiler definitions of the form `-DFOO` or `-DFOO=bar`. A definition for the name specified by `<resultVar>` will also be added automatically.

  - `CMAKE_REQUIRED_INCLUDES`

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of header search paths to pass to the compiler. These will be the only header search paths used by `try_run()`, i.e. the contents of the [`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_dir/INCLUDE_DIRECTORIES.html#prop_dir:INCLUDE_DIRECTORIES) directory property will be ignored.

  - `CMAKE_REQUIRED_LINK_OPTIONS`

    *New in version 3.14.*

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of options to add to the link command (see [`try_run()`](https://cmake.org/cmake/help/latest/command/try_run.html#command:try_run) for further details).

  - `CMAKE_REQUIRED_LIBRARIES`

    A [;-list](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) of libraries to add to the link command. These can be the name of system libraries or they can be [Imported Targets](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets) (see [`try_run()`](https://cmake.org/cmake/help/latest/command/try_run.html#command:try_run) for further details).

  - `CMAKE_REQUIRED_QUIET`

    *New in version 3.1.*

    If this variable evaluates to a boolean true value, all status messages associated with the check will be suppressed.

  The check is only performed once, with the result cached in the variable named by `<resultVar>`. Every subsequent CMake run will re-use this cached value rather than performing the check again, even if the `<code>` changes. In order to force the check to be re-evaluated, the variable named by `<resultVar>` must be manually removed from the cache.

