# [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html#)

*New in version 3.11.*

> Contents
>
> - [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html#fetchcontent)
>   - [Overview](https://cmake.org/cmake/help/latest/module/FetchContent.html#overview)
>   - [Commands](https://cmake.org/cmake/help/latest/module/FetchContent.html#commands)
>   - [Variables](https://cmake.org/cmake/help/latest/module/FetchContent.html#variables)
>   - [Examples](https://cmake.org/cmake/help/latest/module/FetchContent.html#examples)
>     - [Typical Case](https://cmake.org/cmake/help/latest/module/FetchContent.html#typical-case)
>     - [Integrating With find_package()](https://cmake.org/cmake/help/latest/module/FetchContent.html#integrating-with-find-package)
>     - [Overriding Where To Find CMakeLists.txt](https://cmake.org/cmake/help/latest/module/FetchContent.html#overriding-where-to-find-cmakelists-txt)
>     - [Complex Dependency Hierarchies](https://cmake.org/cmake/help/latest/module/FetchContent.html#complex-dependency-hierarchies)
>     - [Populating Content Without Adding It To The Build](https://cmake.org/cmake/help/latest/module/FetchContent.html#populating-content-without-adding-it-to-the-build)
>     - [Populating Content In CMake Script Mode](https://cmake.org/cmake/help/latest/module/FetchContent.html#populating-content-in-cmake-script-mode)

> Note: The [`Using Dependencies Guide`](https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#guide:Using Dependencies Guide) provides a high-level introduction to this general topic. It provides a broader overview of where the `FetchContent` module fits into the bigger picture, including its relationship to the [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) command. The guide is recommended pre-reading before moving on to the details below.

## [Overview](https://cmake.org/cmake/help/latest/module/FetchContent.html#overview)

This module enables populating content at configure time via any method supported by the [`ExternalProject`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#module:ExternalProject) module. Whereas [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) downloads at build time, the `FetchContent` module makes content available immediately, allowing the configure step to use the content in commands like [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory), [`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include) or [`file()`](https://cmake.org/cmake/help/latest/command/file.html#command:file) operations.

Content population details should be defined separately from the command that performs the actual population. This separation ensures that all the dependency details are defined before anything might try to use them to populate content. This is particularly important in more complex project hierarchies where dependencies may be shared between multiple projects.

The following shows a typical example of declaring content details for some dependencies and then ensuring they are populated with a separate call:

```cmake
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
FetchContent_Declare(
  myCompanyIcons
  URL      https://intranet.mycompany.com/assets/iconset_1.12.tar.gz
  URL_HASH MD5=5588a7b18261c20068beabfb4f530b87
)

FetchContent_MakeAvailable(googletest myCompanyIcons)
```

The [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) command ensures the named dependencies have been populated, either by an earlier call or by populating them itself. When performing the population, it will also add them to the main build, if possible, so that the main build can use the populated projects' targets, etc. See the command's documentation for how these steps are performed.

When using a hierarchical project arrangement, projects at higher levels in the hierarchy are able to override the declared details of content specified anywhere lower in the project hierarchy. The first details to be declared for a given dependency take precedence, regardless of where in the project hierarchy that occurs. Similarly, the first call that tries to populate a dependency "wins", with subsequent populations reusing the result of the first instead of repeating the population again. See the [Examples](https://cmake.org/cmake/help/latest/module/FetchContent.html#fetch-content-examples) which demonstrate this scenario.

In some cases, the main project may need to have more precise control over the population, or it may be required to explicitly define the population steps in a way that cannot be captured by the declared details alone. For such situations, the lower level [`FetchContent_GetProperties()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_getproperties) and [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate) commands can be used. These lack the richer features provided by [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) though, so their direct use should be considered a last resort. The typical pattern of such custom steps looks like this:

```cmake
# NOTE: Where possible, prefer to use FetchContent_MakeAvailable()
#       instead of custom logic like this

# Check if population has already been performed
FetchContent_GetProperties(depname)
if(NOT depname_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(depname)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${depname_SOURCE_DIR} ${depname_BINARY_DIR})
endif()
```

The `FetchContent` module also supports defining and populating content in a single call, with no check for whether the content has been populated elsewhere already. This should not be done in projects, but may be appropriate for populating content in CMake's script mode. See [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate) for details.

## [Commands](https://cmake.org/cmake/help/latest/module/FetchContent.html#commands)

### **FetchContent_Declare**

```cmake
FetchContent_Declare(
  <name>
  <contentOptions>...
  [SYSTEM]
  [OVERRIDE_FIND_PACKAGE |
   FIND_PACKAGE_ARGS args...]
)
```

The `FetchContent_Declare()` function records the options that describe how to populate the specified content. If such details have already been recorded earlier in this project (regardless of where in the project hierarchy), this and all later calls for the same content `<name>` are ignored. This "first to record, wins" approach is what allows hierarchical projects to have parent projects override content details of child projects.

The content `<name>` can be any string without spaces, but good practice would be to use only letters, numbers and underscores. The name will be treated case-insensitively and it should be obvious for the content it represents, often being the name of the child project or the value given to its top level [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project) command (if it is a CMake project). For well-known public projects, the name should generally be the official name of the project. Choosing an unusual name makes it unlikely that other projects needing that same content will use the same name, leading to the content being populated multiple times.

The `<contentOptions>` can be any of the download, update or patch options that the [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) command understands. The configure, build, install and test steps are explicitly disabled and therefore options related to them will be ignored. The `SOURCE_SUBDIR` option is an exception, see [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) for details on how that affects behavior.

In most cases, `<contentOptions>` will just be a couple of options defining the download method and method-specific details like a commit tag or archive hash. For example:

```cmake
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)

FetchContent_Declare(
  myCompanyIcons
  URL      https://intranet.mycompany.com/assets/iconset_1.12.tar.gz
  URL_HASH MD5=5588a7b18261c20068beabfb4f530b87
)

FetchContent_Declare(
  myCompanyCertificates
  SVN_REPOSITORY svn+ssh://svn.mycompany.com/srv/svn/trunk/certs
  SVN_REVISION   -r12345
)
```

Where contents are being fetched from a remote location and you do not control that server, it is advisable to use a hash for `GIT_TAG` rather than a branch or tag name. A commit hash is more secure and helps to confirm that the downloaded contents are what you expected.

*Changed in version 3.14:* Commands for the download, update or patch steps can access the terminal. This may be needed for things like password prompts or real-time display of command progress.

*New in version 3.22:* The [`CMAKE_TLS_VERIFY`](https://cmake.org/cmake/help/latest/variable/CMAKE_TLS_VERIFY.html#variable:CMAKE_TLS_VERIFY), [`CMAKE_TLS_CAINFO`](https://cmake.org/cmake/help/latest/variable/CMAKE_TLS_CAINFO.html#variable:CMAKE_TLS_CAINFO), [`CMAKE_NETRC`](https://cmake.org/cmake/help/latest/variable/CMAKE_NETRC.html#variable:CMAKE_NETRC) and [`CMAKE_NETRC_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_NETRC_FILE.html#variable:CMAKE_NETRC_FILE) variables now provide the defaults for their corresponding content options, just like they do for [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add). Previously, these variables were ignored by the `FetchContent` module.

*New in version 3.24:*

- `FIND_PACKAGE_ARGS`

  This option is for scenarios where the [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) command may first try a call to [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) to satisfy the dependency for `<name>`. By default, such a call would be simply `find_package(<name>)`, but `FIND_PACKAGE_ARGS` can be used to provide additional arguments to be appended after the `<name>`. `FIND_PACKAGE_ARGS` can also be given with nothing after it, which indicates that [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) can still be called if [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) is set to `OPT_IN` or is not set.

  Everything after the `FIND_PACKAGE_ARGS` keyword is appended to the [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) call, so all other `<contentOptions>` must come before the `FIND_PACKAGE_ARGS` keyword. If the [`CMAKE_FIND_PACKAGE_TARGETS_GLOBAL`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_TARGETS_GLOBAL.html#variable:CMAKE_FIND_PACKAGE_TARGETS_GLOBAL) variable is set to true at the time `FetchContent_Declare()` is called, a `GLOBAL` keyword will be appended to the [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) arguments if it was not already specified. It will also be appended if `FIND_PACKAGE_ARGS` was not given, but [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) was set to `ALWAYS`.

  `OVERRIDE_FIND_PACKAGE` cannot be used when `FIND_PACKAGE_ARGS` is given.

  [Dependency Providers](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers) discusses another way that [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) calls can be redirected. `FIND_PACKAGE_ARGS` is intended for project control, whereas dependency providers allow users to override project behavior.

- `OVERRIDE_FIND_PACKAGE`

  When a `FetchContent_Declare(<name> ...)` call includes this option, subsequent calls to `find_package(<name> ...)` will ensure that `FetchContent_MakeAvailable(<name>)` has been called, then use the config package files in the [`CMAKE_FIND_PACKAGE_REDIRECTS_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_REDIRECTS_DIR.html#variable:CMAKE_FIND_PACKAGE_REDIRECTS_DIR) directory (which are usually created by `FetchContent_MakeAvailable()`). This effectively makes [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) override [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) for the named dependency, allowing the former to satisfy the package requirements of the latter. `FIND_PACKAGE_ARGS` cannot be used when `OVERRIDE_FIND_PACKAGE` is given.

  If a [dependency provider](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers) has been set and the project calls [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) for the `<name>` dependency, `OVERRIDE_FIND_PACKAGE` will not prevent the provider from seeing that call. Dependency providers always have the opportunity to intercept any direct call to [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package), except if that call contains the `BYPASS_PROVIDER` option.

*New in version 3.25:*

- `SYSTEM`

  If the `SYSTEM` argument is provided, targets created by the dependency will have their [`SYSTEM`](https://cmake.org/cmake/help/latest/prop_tgt/SYSTEM.html#prop_tgt:SYSTEM) property set to true when populated by [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable). The entries in their [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES) will be treated as `SYSTEM` include directories when compiling consumers.

### **FetchContent_MakeAvailable**

*New in version 3.14.*

```cmake
FetchContent_MakeAvailable(<name1> [<name2>...])
```

This command ensures that each of the named dependencies are made available to the project by the time it returns. There must have been a call to [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) for each dependency, and the first such call will control how that dependency will be made available, as described below.

If `<lowercaseName>_SOURCE_DIR` is not set:

- *New in version 3.24:* If a [dependency provider](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers) is set, call the provider's command with `FETCHCONTENT_MAKEAVAILABLE_SERIAL` as the first argument, followed by the arguments of the first call to [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) for `<name>`. If `SOURCE_DIR` or `BINARY_DIR` were not part of the original declared arguments, they will be added with their default values. If [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) was set to `NEVER` when the details were declared, any `FIND_PACKAGE_ARGS` will be omitted. The `OVERRIDE_FIND_PACKAGE` keyword is also always omitted. If the provider fulfilled the request, `FetchContent_MakeAvailable()` will consider that dependency handled, skip the remaining steps below and move on to the next dependency in the list.
- *New in version 3.24:* If permitted, [`find_package( [...\])`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) will be called, where `<args>...` may be provided by the `FIND_PACKAGE_ARGS` option in [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare). The value of the [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) variable at the time [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) was called determines whether `FetchContent_MakeAvailable()` can call [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package). If the [`CMAKE_FIND_PACKAGE_TARGETS_GLOBAL`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_TARGETS_GLOBAL.html#variable:CMAKE_FIND_PACKAGE_TARGETS_GLOBAL) variable is set to true when `FetchContent_MakeAvailable()` is called, it still affects any imported targets created when that in turn calls [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package), even if that variable was false when the corresponding details were declared.

If the dependency was not satisfied by a provider or a [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) call, `FetchContent_MakeAvailable()` then uses the following logic to make the dependency available:

- If the dependency has already been populated earlier in this run, set the `<lowercaseName>_POPULATED`, `<lowercaseName>_SOURCE_DIR` and `<lowercaseName>_BINARY_DIR` variables in the same way as a call to [`FetchContent_GetProperties()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_getproperties), then skip the remaining steps below and move on to the next dependency in the list.

- Call [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate) to populate the dependency using the details recorded by an earlier call to [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare). Halt with a fatal error if no such details have been recorded. [`FETCHCONTENT_SOURCE_DIR_`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_SOURCE_DIR_) can be used to override the declared details and use content provided at the specified location instead.

- *New in version 3.24:* Ensure the [`CMAKE_FIND_PACKAGE_REDIRECTS_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_REDIRECTS_DIR.html#variable:CMAKE_FIND_PACKAGE_REDIRECTS_DIR) directory contains a `<lowercaseName>-config.cmake` and a `<lowercaseName>-config-version.cmake` file (or equivalently `<name>Config.cmake` and `<name>ConfigVersion.cmake`). The directory that the [`CMAKE_FIND_PACKAGE_REDIRECTS_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_REDIRECTS_DIR.html#variable:CMAKE_FIND_PACKAGE_REDIRECTS_DIR) variable points to is cleared at the start of every CMake run. If no config file exists when [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate) returns, a minimal one will be written which [`includes`](https://cmake.org/cmake/help/latest/command/include.html#command:include) any `<lowercaseName>-extra.cmake` or `<name>Extra.cmake` file with the `OPTIONAL` flag (so the files can be missing and won't generate a warning). Similarly, if no config version file exists, a very simple one will be written which sets `PACKAGE_VERSION_COMPATIBLE` and `PACKAGE_VERSION_EXACT` to true. This ensures all future calls to [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) for the dependency will use the redirected config file, regardless of any version requirements. CMake cannot automatically determine an arbitrary dependency's version, so it cannot set `PACKAGE_VERSION`. When a dependency is pulled in via [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory) in the next step, it may choose to overwrite the generated config version file in [`CMAKE_FIND_PACKAGE_REDIRECTS_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_REDIRECTS_DIR.html#variable:CMAKE_FIND_PACKAGE_REDIRECTS_DIR) with one that also sets `PACKAGE_VERSION`. The dependency may also write a `<lowercaseName>-extra.cmake` or `<name>Extra.cmake` file to perform custom processing or define any variables that their normal (installed) package config file would otherwise usually define (many projects don't do any custom processing or set any variables and therefore have no need to do this). If required, the main project can write these files instead if the dependency project doesn't do so. This allows the main project to add missing details from older dependencies that haven't or can't be updated to support this functionality. See [Integrating With find_package()](https://cmake.org/cmake/help/latest/module/FetchContent.html#integrating-with-find-package) for examples.

- If the top directory of the populated content contains a `CMakeLists.txt` file, call [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory) to add it to the main build. It is not an error for there to be no `CMakeLists.txt` file, which allows the command to be used for dependencies that make downloaded content available at a known location, but which do not need or support being added directly to the build.

  *New in version 3.18:* The `SOURCE_SUBDIR` option can be given in the declared details to look somewhere below the top directory instead (i.e. the same way that `SOURCE_SUBDIR` is used by the [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) command). The path provided with `SOURCE_SUBDIR` must be relative and will be treated as relative to the top directory. It can also point to a directory that does not contain a `CMakeLists.txt` file or even to a directory that doesn't exist. This can be used to avoid adding a project that contains a `CMakeLists.txt` file in its top directory.

Projects should aim to declare the details of all dependencies they might use before they call `FetchContent_MakeAvailable()` for any of them. This ensures that if any of the dependencies are also sub-dependencies of one or more of the others, the main project still controls the details that will be used (because it will declare them first before the dependencies get a chance to). In the following code samples, assume that the `uses_other` dependency also uses `FetchContent` to add the `other` dependency internally:

```cmake
# WRONG: Should declare all details first
FetchContent_Declare(uses_other ...)
FetchContent_MakeAvailable(uses_other)

FetchContent_Declare(other ...)    # Will be ignored, uses_other beat us to it
FetchContent_MakeAvailable(other)  # Would use details declared by uses_other
# CORRECT: All details declared first, so they will take priority
FetchContent_Declare(uses_other ...)
FetchContent_Declare(other ...)
FetchContent_MakeAvailable(uses_other other)
```

Note that [`CMAKE_VERIFY_INTERFACE_HEADER_SETS`](https://cmake.org/cmake/help/latest/variable/CMAKE_VERIFY_INTERFACE_HEADER_SETS.html#variable:CMAKE_VERIFY_INTERFACE_HEADER_SETS) is explicitly set to false upon entry to `FetchContent_MakeAvailable()`, and is restored to its original value before the command returns. Developers typically only want to verify header sets from the main project, not those from any dependencies. This local manipulation of the [`CMAKE_VERIFY_INTERFACE_HEADER_SETS`](https://cmake.org/cmake/help/latest/variable/CMAKE_VERIFY_INTERFACE_HEADER_SETS.html#variable:CMAKE_VERIFY_INTERFACE_HEADER_SETS) variable provides that intuitive behavior. You can use variables like [`CMAKE_PROJECT_INCLUDE`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_INCLUDE.html#variable:CMAKE_PROJECT_INCLUDE) or [`CMAKE_PROJECT__INCLUDE`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_PROJECT-NAME_INCLUDE.html#variable:CMAKE_PROJECT__INCLUDE) to turn verification back on for all or some dependencies. You can also set the [`VERIFY_INTERFACE_HEADER_SETS`](https://cmake.org/cmake/help/latest/prop_tgt/VERIFY_INTERFACE_HEADER_SETS.html#prop_tgt:VERIFY_INTERFACE_HEADER_SETS) property of individual targets.

### **FetchContent_Populate**



> Note: Where possible, prefer to use [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) instead of implementing population manually with this command.

```cmake
FetchContent_Populate(<name>)
```

In most cases, the only argument given to `FetchContent_Populate()` is the `<name>`. When used this way, the command assumes the content details have been recorded by an earlier call to [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare). The details are stored in a global property, so they are unaffected by things like variable or directory scope. Therefore, it doesn't matter where in the project the details were previously declared, as long as they have been declared before the call to `FetchContent_Populate()`. Those saved details are then used to construct a call to [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) in a private sub-build to perform the content population immediately. The implementation of `ExternalProject_Add()` ensures that if the content has already been populated in a previous CMake run, that content will be reused rather than repopulating them again. For the common case where population involves downloading content, the cost of the download is only paid once.

An internal global property records when a particular content population request has been processed. If `FetchContent_Populate()` is called more than once for the same content name within a configure run, the second call will halt with an error. Projects can and should check whether content population has already been processed with the [`FetchContent_GetProperties()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_getproperties) command before calling `FetchContent_Populate()`.

`FetchContent_Populate()` will set three variables in the scope of the caller:

- `<lowercaseName>_POPULATED`

  This will always be set to `TRUE` by the call.

- `<lowercaseName>_SOURCE_DIR`

  The location where the populated content can be found upon return.

- `<lowercaseName>_BINARY_DIR`

  A directory intended for use as a corresponding build directory.

The main use case for the `<lowercaseName>_SOURCE_DIR` and `<lowercaseName>_BINARY_DIR` variables is to call [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory) immediately after population:

```cmake
FetchContent_Populate(FooBar)
add_subdirectory(${foobar_SOURCE_DIR} ${foobar_BINARY_DIR})
```

The values of the three variables can also be retrieved from anywhere in the project hierarchy using the [`FetchContent_GetProperties()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_getproperties) command.

The `FetchContent_Populate()` command also supports a syntax allowing the content details to be specified directly rather than using any saved details. This is more low-level and use of this form is generally to be avoided in favor of using saved content details as outlined above. Nevertheless, in certain situations it can be useful to invoke the content population as an isolated operation (typically as part of implementing some other higher level feature or when using CMake in script mode):

```cmake
FetchContent_Populate(
  <name>
  [QUIET]
  [SUBBUILD_DIR <subBuildDir>]
  [SOURCE_DIR <srcDir>]
  [BINARY_DIR <binDir>]
  ...
)
```

This form has a number of key differences to that where only `<name>` is provided:

- All required population details are assumed to have been provided directly in the call to `FetchContent_Populate()`. Any saved details for `<name>` are ignored.
- No check is made for whether content for `<name>` has already been populated.
- No global property is set to record that the population has occurred.
- No global properties record the source or binary directories used for the populated content.
- The `FETCHCONTENT_FULLY_DISCONNECTED` and `FETCHCONTENT_UPDATES_DISCONNECTED` cache variables are ignored.

The `<lowercaseName>_SOURCE_DIR` and `<lowercaseName>_BINARY_DIR` variables are still returned to the caller, but since these locations are not stored as global properties when this form is used, they are only available to the calling scope and below rather than the entire project hierarchy. No `<lowercaseName>_POPULATED` variable is set in the caller's scope with this form.

The supported options for `FetchContent_Populate()` are the same as those for [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare). Those few options shown just above are either specific to `FetchContent_Populate()` or their behavior is slightly modified from how [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) treats them:

- `QUIET`

  The `QUIET` option can be given to hide the output associated with populating the specified content. If the population fails, the output will be shown regardless of whether this option was given or not so that the cause of the failure can be diagnosed. The global `FETCHCONTENT_QUIET` cache variable has no effect on `FetchContent_Populate()` calls where the content details are provided directly.

- `SUBBUILD_DIR`

  The `SUBBUILD_DIR` argument can be provided to change the location of the sub-build created to perform the population. The default value is `${CMAKE_CURRENT_BINARY_DIR}/<lowercaseName>-subbuild` and it would be unusual to need to override this default. If a relative path is specified, it will be interpreted as relative to [`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR). This option should not be confused with the `SOURCE_SUBDIR` option which only affects the [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) command.

- `SOURCE_DIR`, `BINARY_DIR`

  The `SOURCE_DIR` and `BINARY_DIR` arguments are supported by [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add), but different default values are used by `FetchContent_Populate()`. `SOURCE_DIR` defaults to `${CMAKE_CURRENT_BINARY_DIR}/<lowercaseName>-src` and `BINARY_DIR` defaults to `${CMAKE_CURRENT_BINARY_DIR}/<lowercaseName>-build`. If a relative path is specified, it will be interpreted as relative to [`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR).

In addition to the above explicit options, any other unrecognized options are passed through unmodified to [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) to perform the download, patch and update steps. The following options are explicitly prohibited (they are disabled by the `FetchContent_Populate()` command):

- `CONFIGURE_COMMAND`
- `BUILD_COMMAND`
- `INSTALL_COMMAND`
- `TEST_COMMAND`

If using `FetchContent_Populate()` within CMake's script mode, be aware that the implementation sets up a sub-build which therefore requires a CMake generator and build tool to be available. If these cannot be found by default, then the [`CMAKE_GENERATOR`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR.html#variable:CMAKE_GENERATOR) and/or [`CMAKE_MAKE_PROGRAM`](https://cmake.org/cmake/help/latest/variable/CMAKE_MAKE_PROGRAM.html#variable:CMAKE_MAKE_PROGRAM) variables will need to be set appropriately on the command line invoking the script.

*New in version 3.18:* Added support for the `DOWNLOAD_NO_EXTRACT` option.

### **FetchContent_GetProperties**


When using saved content details, a call to [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) or [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate) records information in global properties which can be queried at any time. This information may include the source and binary directories associated with the content and also whether or not the content population has been processed during the current configure run.

```cmake
FetchContent_GetProperties(
  <name>
  [SOURCE_DIR <srcDirVar>]
  [BINARY_DIR <binDirVar>]
  [POPULATED <doneVar>]
)
```

The `SOURCE_DIR`, `BINARY_DIR` and `POPULATED` options can be used to specify which properties should be retrieved. Each option accepts a value which is the name of the variable in which to store that property. Most of the time though, only `<name>` is given, in which case the call will then set the same variables as a call to [`FetchContent_MakeAvailable(name)`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) or [`FetchContent_Populate(name)`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate). Note that the `SOURCE_DIR` and `BINARY_DIR` values can be empty if the call is fulfilled by a [dependency provider](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers).

This command is rarely needed when using [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable). It is more commonly used as part of implementing the following pattern with [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate), which ensures that the relevant variables will always be defined regardless of whether or not the population has been performed elsewhere in the project already:

```cmake
# Check if population has already been performed
FetchContent_GetProperties(depname)
if(NOT depname_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(depname)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${depname_SOURCE_DIR} ${depname_BINARY_DIR})
endif()
```

### **FetchContent_SetPopulated**

*New in version 3.24.*

> Note: This command should only be called by [dependency providers](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers). Calling it in any other context is unsupported and future CMake versions may halt with a fatal error in such cases.

```cmake
FetchContent_SetPopulated(
  <name>
  [SOURCE_DIR <srcDir>]
  [BINARY_DIR <binDir>]
)
```

If a provider command fulfills a `FETCHCONTENT_MAKEAVAILABLE_SERIAL` request, it must call this function before returning. The `SOURCE_DIR` and `BINARY_DIR` arguments can be used to specify the values that [`FetchContent_GetProperties()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_getproperties) should return for its corresponding arguments. Only provide `SOURCE_DIR` and `BINARY_DIR` if they have the same meaning as if they had been populated by the built-in [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) implementation.

## [Variables](https://cmake.org/cmake/help/latest/module/FetchContent.html#variables)

A number of cache variables can influence the behavior where details from a [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) call are used to populate content.

> Note: All of these variables are intended for the developer to customize behavior. They should not normally be set by the project.

### **FETCHCONTENT_BASE_DIR**

In most cases, the saved details do not specify any options relating to the directories to use for the internal sub-build, final source and build areas. It is generally best to leave these decisions up to the `FetchContent` module to handle on the project's behalf. The `FETCHCONTENT_BASE_DIR` cache variable controls the point under which all content population directories are collected, but in most cases, developers would not need to change this. The default location is `${CMAKE_BINARY_DIR}/_deps`, but if developers change this value, they should aim to keep the path short and just below the top level of the build tree to avoid running into path length problems on Windows.

### **FETCHCONTENT_QUIET**

The logging output during population can be quite verbose, making the configure stage quite noisy. This cache option (`ON` by default) hides all population output unless an error is encountered. If experiencing problems with hung downloads, temporarily switching this option off may help diagnose which content population is causing the issue.

### **FETCHCONTENT_FULLY_DISCONNECTED**

When this option is enabled, no attempt is made to download or update any content. It is assumed that all content has already been populated in a previous run or the source directories have been pointed at existing contents the developer has provided manually (using options described further below). When the developer knows that no changes have been made to any content details, turning this option `ON` can significantly speed up the configure stage. It is `OFF` by default.

### **FETCHCONTENT_UPDATES_DISCONNECTED**

This is a less severe download/update control compared to [`FETCHCONTENT_FULLY_DISCONNECTED`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_FULLY_DISCONNECTED). Instead of bypassing all download and update logic, `FETCHCONTENT_UPDATES_DISCONNECTED` only disables the update stage. Therefore, if content has not been downloaded previously, it will still be downloaded when this option is enabled. This can speed up the configure stage, but not as much as [`FETCHCONTENT_FULLY_DISCONNECTED`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_FULLY_DISCONNECTED). It is `OFF` by default.

### **FETCHCONTENT_TRY_FIND_PACKAGE_MODE**

*New in version 3.24.*

This variable modifies the details that [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) records for a given dependency. While it ultimately controls the behavior of [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable), it is the variable's value when [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) is called that gets used. It makes no difference what the variable is set to when [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) is called. Since the variable should only be set by the user and not by projects directly, it will typically have the same value throughout anyway, so this distinction is not usually noticeable.

`FETCHCONTENT_TRY_FIND_PACKAGE_MODE` ultimately controls whether [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) is allowed to call [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) to satisfy a dependency. The variable can be set to one of the following values:

- `OPT_IN`

  [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) will only call [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) if the [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) call included a `FIND_PACKAGE_ARGS` keyword. This is also the default behavior if `FETCHCONTENT_TRY_FIND_PACKAGE_MODE` is not set.

- `ALWAYS`

  [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) can be called by [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) regardless of whether the [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) call included a `FIND_PACKAGE_ARGS` keyword or not. If no `FIND_PACKAGE_ARGS` keyword was given, the behavior will be as though `FIND_PACKAGE_ARGS` had been provided, with no additional arguments after it.

- `NEVER`

  [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) will not call [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package). Any `FIND_PACKAGE_ARGS` given to the [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) call will be ignored.

  As a special case, if the [`FETCHCONTENT_SOURCE_DIR_`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_SOURCE_DIR_) variable has a non-empty value for a dependency, it is assumed that the user is overriding all other methods of making that dependency available. `FETCHCONTENT_TRY_FIND_PACKAGE_MODE` will have no effect on that dependency and [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) will not try to call [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) for it.

In addition to the above, the following variables are also defined for each content name:

### **FETCHCONTENT_SOURCE_DIR_\<uppercaseName>**

If this is set, no download or update steps are performed for the specified content and the `<lowercaseName>_SOURCE_DIR` variable returned to the caller is pointed at this location. This gives developers a way to have a separate checkout of the content that they can modify freely without interference from the build. The build simply uses that existing source, but it still defines `<lowercaseName>_BINARY_DIR` to point inside its own build area. Developers are strongly encouraged to use this mechanism rather than editing the sources populated in the default location, as changes to sources in the default location can be lost when content population details are changed by the project.

### **FETCHCONTENT_UPDATES_DISCONNECTED_\<uppercaseName>**

This is the per-content equivalent of [`FETCHCONTENT_UPDATES_DISCONNECTED`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_UPDATES_DISCONNECTED). If the global option or this option is `ON`, then updates will be disabled for the named content. Disabling updates for individual content can be useful for content whose details rarely change, while still leaving other frequently changing content with updates enabled.

## Examples

### [Typical Case](https://cmake.org/cmake/help/latest/module/FetchContent.html#typical-case)

This first fairly straightforward example ensures that some popular testing frameworks are available to the main build:

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        de6fe184a9ac1a06895cdd1c9b437f0a0bdf14ad # v2.13.4
)

# After the following call, the CMake targets defined by googletest and
# Catch2 will be available to the rest of the build
FetchContent_MakeAvailable(googletest Catch2)
```

### [Integrating With find_package()](https://cmake.org/cmake/help/latest/module/FetchContent.html#integrating-with-find-package)

For the previous example, if the user wanted to try to find `googletest` and `Catch2` via [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) first before trying to download and build them from source, they could set the [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) variable to `ALWAYS`. This would also affect any other calls to [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) throughout the project, which might not be acceptable. The behavior can be enabled for just these two dependencies instead by adding `FIND_PACKAGE_ARGS` to the declared details and leaving [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) unset, or set to `OPT_IN`:

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  FIND_PACKAGE_ARGS NAMES GTest
)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        de6fe184a9ac1a06895cdd1c9b437f0a0bdf14ad # v2.13.4
  FIND_PACKAGE_ARGS
)

# This will try calling find_package() first for both dependencies
FetchContent_MakeAvailable(googletest Catch2)
```

For `Catch2`, no additional arguments to [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) are needed, so no additional arguments are provided after the `FIND_PACKAGE_ARGS` keyword. For `googletest`, its package is more commonly called `GTest`, so arguments are added to support it being found by that name.

If the user wanted to disable [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) from calling [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) for any dependency, even if it provided `FIND_PACKAGE_ARGS` in its declared details, they could set [`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) to `NEVER`.

If the project wanted to indicate that these two dependencies should be downloaded and built from source and that [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) calls should be redirected to use the built dependencies, the `OVERRIDE_FIND_PACKAGE` option should be used when declaring the content details:

```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  OVERRIDE_FIND_PACKAGE
)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        de6fe184a9ac1a06895cdd1c9b437f0a0bdf14ad # v2.13.4
  OVERRIDE_FIND_PACKAGE
)

# The following will automatically forward through to FetchContent_MakeAvailable()
find_package(googletest)
find_package(Catch2)
```

CMake provides a FindGTest module which defines some variables that older projects may use instead of linking to the imported targets. To support those cases, we can provide an extra file. In keeping with the "first to define, wins" philosophy of `FetchContent`, we only write out that file if something else hasn't already done so.

```cmake
FetchContent_MakeAvailable(googletest)

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletest-extra.cmake AND
   NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletestExtra.cmake)
  file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletest-extra.cmake
[=[
if("${GTEST_LIBRARIES}" STREQUAL "" AND TARGET GTest::gtest)
  set(GTEST_LIBRARIES GTest::gtest)
endif()
if("${GTEST_MAIN_LIBRARIES}" STREQUAL "" AND TARGET GTest::gtest_main)
  set(GTEST_MAIN_LIBRARIES GTest::gtest_main)
endif()
if("${GTEST_BOTH_LIBRARIES}" STREQUAL "")
  set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
endif()
]=])
endif()
```

Projects will also likely be using `find_package(GTest)` rather than `find_package(googletest)`, but it is possible to make use of the [`CMAKE_FIND_PACKAGE_REDIRECTS_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_REDIRECTS_DIR.html#variable:CMAKE_FIND_PACKAGE_REDIRECTS_DIR) area to pull in the latter as a dependency of the former. This is likely to be sufficient to satisfy a typical `find_package(GTest)` call.

```cmake
FetchContent_MakeAvailable(googletest)

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config.cmake AND
   NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/GTestConfig.cmake)
  file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config.cmake
[=[
include(CMakeFindDependencyMacro)
find_dependency(googletest)
]=])
endif()

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config-version.cmake AND
   NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/GTestConfigVersion.cmake)
  file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config-version.cmake
[=[
include(${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletest-config-version.cmake OPTIONAL)
if(NOT PACKAGE_VERSION_COMPATIBLE)
  include(${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletestConfigVersion.cmake OPTIONAL)
endif()
]=])
endif()
```

### [Overriding Where To Find CMakeLists.txt](https://cmake.org/cmake/help/latest/module/FetchContent.html#overriding-where-to-find-cmakelists-txt)

If the sub-project's `CMakeLists.txt` file is not at the top level of its source tree, the `SOURCE_SUBDIR` option can be used to tell `FetchContent` where to find it. The following example shows how to use that option, and it also sets a variable which is meaningful to the subproject before pulling it into the main build (set as an `INTERNAL` cache variable to avoid problems with policy [`CMP0077`](https://cmake.org/cmake/help/latest/policy/CMP0077.html#policy:CMP0077)):

```cmake
include(FetchContent)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        ae50d9b9902526efd6c7a1907d09739f959c6297 # v3.15.0
  SOURCE_SUBDIR  cmake
)
set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(protobuf)
```

### [Complex Dependency Hierarchies](https://cmake.org/cmake/help/latest/module/FetchContent.html#complex-dependency-hierarchies)

In more complex project hierarchies, the dependency relationships can be more complicated. Consider a hierarchy where `projA` is the top level project and it depends directly on projects `projB` and `projC`. Both `projB` and `projC` can be built standalone and they also both depend on another project `projD`. `projB` additionally depends on `projE`. This example assumes that all five projects are available on a company git server. The `CMakeLists.txt` of each project might have sections like the following:

*projA*:

```cmake
include(FetchContent)
FetchContent_Declare(
  projB
  GIT_REPOSITORY git@mycompany.com:git/projB.git
  GIT_TAG        4a89dc7e24ff212a7b5167bef7ab079d
)
FetchContent_Declare(
  projC
  GIT_REPOSITORY git@mycompany.com:git/projC.git
  GIT_TAG        4ad4016bd1d8d5412d135cf8ceea1bb9
)
FetchContent_Declare(
  projD
  GIT_REPOSITORY git@mycompany.com:git/projD.git
  GIT_TAG        origin/integrationBranch
)
FetchContent_Declare(
  projE
  GIT_REPOSITORY git@mycompany.com:git/projE.git
  GIT_TAG        v2.3-rc1
)

# Order is important, see notes in the discussion further below
FetchContent_MakeAvailable(projD projB projC)
```

*projB*:

```cmake
include(FetchContent)
FetchContent_Declare(
  projD
  GIT_REPOSITORY git@mycompany.com:git/projD.git
  GIT_TAG        20b415f9034bbd2a2e8216e9a5c9e632
)
FetchContent_Declare(
  projE
  GIT_REPOSITORY git@mycompany.com:git/projE.git
  GIT_TAG        68e20f674a48be38d60e129f600faf7d
)

FetchContent_MakeAvailable(projD projE)
```

*projC*:

```cmake
include(FetchContent)
FetchContent_Declare(
  projD
  GIT_REPOSITORY git@mycompany.com:git/projD.git
  GIT_TAG        7d9a17ad2c962aa13e2fbb8043fb6b8a
)

# This particular version of projD requires workarounds
FetchContent_GetProperties(projD)
if(NOT projd_POPULATED)
  FetchContent_Populate(projD)

  # Copy an additional/replacement file into the populated source
  file(COPY someFile.c DESTINATION ${projd_SOURCE_DIR}/src)

  add_subdirectory(${projd_SOURCE_DIR} ${projd_BINARY_DIR})
endif()
```

A few key points should be noted in the above:

- `projB` and `projC` define different content details for `projD`, but `projA` also defines a set of content details for `projD`. Because `projA` will define them first, the details from `projB` and `projC` will not be used. The override details defined by `projA` are not required to match either of those from `projB` or `projC`, but it is up to the higher level project to ensure that the details it does define still make sense for the child projects.
- In the `projA` call to [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable), `projD` is listed ahead of `projB` and `projC` to ensure that `projA` is in control of how `projD` is populated.
- While `projA` defines content details for `projE`, it does not need to explicitly call `FetchContent_MakeAvailable(projE)` or `FetchContent_Populate(projD)` itself. Instead, it leaves that to the child `projB`. For higher level projects, it is often enough to just define the override content details and leave the actual population to the child projects. This saves repeating the same thing at each level of the project hierarchy unnecessarily.

### [Populating Content Without Adding It To The Build](https://cmake.org/cmake/help/latest/module/FetchContent.html#populating-content-without-adding-it-to-the-build)

Projects don't always need to add the populated content to the build. Sometimes the project just wants to make the downloaded content available at a predictable location. The next example ensures that a set of standard company toolchain files (and potentially even the toolchain binaries themselves) is available early enough to be used for that same build.

```cmake
cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  mycom_toolchains
  URL  https://intranet.mycompany.com//toolchains_1.3.2.tar.gz
)
FetchContent_MakeAvailable(mycom_toolchains)

project(CrossCompileExample)
```

The project could be configured to use one of the downloaded toolchains like so:

```sh
cmake -DCMAKE_TOOLCHAIN_FILE=_deps/mycom_toolchains-src/toolchain_arm.cmake /path/to/src
```

When CMake processes the `CMakeLists.txt` file, it will download and unpack the tarball into `_deps/mycompany_toolchains-src` relative to the build directory. The [`CMAKE_TOOLCHAIN_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html#variable:CMAKE_TOOLCHAIN_FILE) variable is not used until the [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project) command is reached, at which point CMake looks for the named toolchain file relative to the build directory. Because the tarball has already been downloaded and unpacked by then, the toolchain file will be in place, even the very first time that `cmake` is run in the build directory.

### [Populating Content In CMake Script Mode](https://cmake.org/cmake/help/latest/module/FetchContent.html#populating-content-in-cmake-script-mode)

This last example demonstrates how one might download and unpack a firmware tarball using CMake's [`script mode`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1)). The call to [`FetchContent_Populate()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_populate) specifies all the content details and the unpacked firmware will be placed in a `firmware` directory below the current working directory.

*getFirmware.cmake*:

```cmake
# NOTE: Intended to be run in script mode with cmake -P
include(FetchContent)
FetchContent_Populate(
  firmware
  URL        https://mycompany.com/assets/firmware-1.23-arm.tar.gz
  URL_HASH   MD5=68247684da89b608d466253762b0ff11
  SOURCE_DIR firmware
)
```
