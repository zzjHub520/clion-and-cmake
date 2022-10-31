# CheckCCompilerFlag

Check whether the C compiler supports a given flag.

- **check_c_compiler_flag**

  ```cmake
  check_c_compiler_flag(<flag> <var>)
  ```

  Check that the `<flag>` is accepted by the compiler without a diagnostic. Stores the result in an internal cache entry named `<var>`.

This command temporarily sets the `CMAKE_REQUIRED_DEFINITIONS` variable and calls the `check_c_source_compiles` macro from the [`CheckCSourceCompiles`](https://cmake.org/cmake/help/latest/module/CheckCSourceCompiles.html#module:CheckCSourceCompiles) module. See documentation of that module for a listing of variables that can otherwise modify the build.

A positive result from this check indicates only that the compiler did not issue a diagnostic message when given the flag. Whether the flag has any effect or even a specific one is beyond the scope of this module.

> Note: Since the [`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile) command forwards flags from variables like [`CMAKE_C_FLAGS`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_FLAGS.html#variable:CMAKE__FLAGS), unknown flags in such variables may cause a false negative for this check.