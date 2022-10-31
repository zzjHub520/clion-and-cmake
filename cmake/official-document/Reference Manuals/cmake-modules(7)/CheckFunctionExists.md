# CheckFunctionExists

Check if a C function can be linked

- **check_function_exists**

  ```cmake
  check_function_exists(<function> <variable>)
  ```

  Checks that the `<function>` is provided by libraries on the system and store the result in a `<variable>`, which will be created as an internal cache variable.

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

>Note: Prefer using [`CheckSymbolExists`](https://cmake.org/cmake/help/latest/module/CheckSymbolExists.html#module:CheckSymbolExists) instead of this module, for the following reasons:
>
>- `check_function_exists()` can't detect functions that are inlined in headers or specified as a macro.
>- `check_function_exists()` can't detect anything in the 32-bit versions of the Win32 API, because of a mismatch in calling conventions.
>- `check_function_exists()` only verifies linking, it does not verify that the function is declared in system headers.