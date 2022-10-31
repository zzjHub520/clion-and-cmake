# CheckCXXSymbolExists

Check if a symbol exists as a function, variable, or macro in `C++`.

- **check_cxx_symbol_exists**

  ```cmake
  check_cxx_symbol_exists(<symbol> <files> <variable>)
  ```

  Check that the `<symbol>` is available after including given header `<files>` and store the result in a `<variable>`. Specify the list of files in one argument as a semicolon-separated list. `check_cxx_symbol_exists()` can be used to check for symbols as seen by the C++ compiler, as opposed to [`check_symbol_exists()`](https://cmake.org/cmake/help/latest/module/CheckSymbolExists.html#command:check_symbol_exists), which always uses the `C` compiler.

  If the header files define the symbol as a macro it is considered available and assumed to work. If the header files declare the symbol as a function or variable then the symbol must also be available for linking. If the symbol is a type, enum value, or C++ template it will not be recognized: consider using the [`CheckTypeSize`](https://cmake.org/cmake/help/latest/module/CheckTypeSize.html#module:CheckTypeSize) or [`CheckSourceCompiles`](https://cmake.org/cmake/help/latest/module/CheckSourceCompiles.html#module:CheckSourceCompiles) module instead.

> Note: This command is unreliable when `<symbol>` is (potentially) an overloaded function. Since there is no reliable way to predict whether a given function in the system environment may be defined as an overloaded function or may be an overloaded function on other systems or will become so in the future, it is generally advised to use the [`CheckCXXSourceCompiles`](https://cmake.org/cmake/help/latest/module/CheckCXXSourceCompiles.html#module:CheckCXXSourceCompiles) module for checking any function symbol (unless somehow you surely know the checked function is not overloaded on other systems or will not be so in the future).

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

For example:

```cmake
include(CheckCXXSymbolExists)

# Check for macro SEEK_SET
check_cxx_symbol_exists(SEEK_SET "cstdio" HAVE_SEEK_SET)
# Check for function std::fopen
check_cxx_symbol_exists(std::fopen "cstdio" HAVE_STD_FOPEN)
```