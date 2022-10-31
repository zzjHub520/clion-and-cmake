# [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html#id1)

> Contents
>
> - [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html#externalproject)
>   - [Commands](https://cmake.org/cmake/help/latest/module/ExternalProject.html#commands)
>     - [External Project Definition](https://cmake.org/cmake/help/latest/module/ExternalProject.html#external-project-definition)
>     - [Obtaining Project Properties](https://cmake.org/cmake/help/latest/module/ExternalProject.html#obtaining-project-properties)
>     - [Explicit Step Management](https://cmake.org/cmake/help/latest/module/ExternalProject.html#explicit-step-management)
>   - [Examples](https://cmake.org/cmake/help/latest/module/ExternalProject.html#examples)

## [Commands](https://cmake.org/cmake/help/latest/module/ExternalProject.html#id2)

### [External Project Definition](https://cmake.org/cmake/help/latest/module/ExternalProject.html#id3)

#### **ExternalProject_Add**

The `ExternalProject_Add()` function creates a custom target to drive download, update/patch, configure, build, install and test steps of an external project:

ExternalProject_Add(<name> [<option>...])

The individual steps within the process can be driven independently if required (e.g. for CDash submission) and extra custom steps can be defined, along with the ability to control the step dependencies. The directory structure used for the management of the external project can also be customized. The function supports a large number of options which can be used to tailor the external project behavior.

##### **Directory Options:**

Most of the time, the default directory layout is sufficient. It is largely an implementation detail that the main project usually doesn't need to change. In some circumstances, however, control over the directory layout can be useful or necessary. The directory options are potentially more useful from the point of view that the main build can use the [`ExternalProject_Get_Property()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_get_property) command to retrieve their values, thereby allowing the main project to refer to build artifacts of the external project.

- `PREFIX <dir>`

  Root directory for the external project. Unless otherwise noted below, all other directories associated with the external project will be created under here.

- `TMP_DIR <dir>`

  Directory in which to store temporary files.

- `STAMP_DIR <dir>`

  Directory in which to store the timestamps of each step. Log files from individual steps are also created in here unless overridden by LOG_DIR (see *Logging Options* below).

- `LOG_DIR <dir>`

  *New in version 3.14.*

  Directory in which to store the logs of each step.

- `DOWNLOAD_DIR <dir>`

  Directory in which to store downloaded files before unpacking them. This directory is only used by the URL download method, all other download methods use `SOURCE_DIR` directly instead.

- `SOURCE_DIR <dir>`

  Source directory into which downloaded contents will be unpacked, or for non-URL download methods, the directory in which the repository should be checked out, cloned, etc. If no download method is specified, this must point to an existing directory where the external project has already been unpacked or cloned/checked out.Note If a download method is specified, any existing contents of the source directory may be deleted. Only the URL download method checks whether this directory is either missing or empty before initiating the download, stopping with an error if it is not empty. All other download methods silently discard any previous contents of the source directory.

- `BINARY_DIR <dir>`

  Specify the build directory location. This option is ignored if `BUILD_IN_SOURCE` is enabled.

- `INSTALL_DIR <dir>`

  Installation prefix to be placed in the `<INSTALL_DIR>` placeholder. This does not actually configure the external project to install to the given prefix. That must be done by passing appropriate arguments to the external project configuration step, e.g. using `<INSTALL_DIR>`.

If any of the above `..._DIR` options are not specified, their defaults are computed as follows. If the `PREFIX` option is given or the `EP_PREFIX` directory property is set, then an external project is built and installed under the specified prefix:

```cmake
TMP_DIR      = <prefix>/tmp
STAMP_DIR    = <prefix>/src/<name>-stamp
DOWNLOAD_DIR = <prefix>/src
SOURCE_DIR   = <prefix>/src/<name>
BINARY_DIR   = <prefix>/src/<name>-build
INSTALL_DIR  = <prefix>
LOG_DIR      = <STAMP_DIR>
```

Otherwise, if the `EP_BASE` directory property is set then components of an external project are stored under the specified base:

```cmake
TMP_DIR      = <base>/tmp/<name>
STAMP_DIR    = <base>/Stamp/<name>
DOWNLOAD_DIR = <base>/Download/<name>
SOURCE_DIR   = <base>/Source/<name>
BINARY_DIR   = <base>/Build/<name>
INSTALL_DIR  = <base>/Install/<name>
LOG_DIR      = <STAMP_DIR>
```

If no `PREFIX`, `EP_PREFIX`, or `EP_BASE` is specified, then the default is to set `PREFIX` to `<name>-prefix`. Relative paths are interpreted with respect to [`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR) at the point where `ExternalProject_Add()` is called.

##### **Download Step Options:**

A download method can be omitted if the `SOURCE_DIR` option is used to point to an existing non-empty directory. Otherwise, one of the download methods below must be specified (multiple download methods should not be given) or a custom `DOWNLOAD_COMMAND` provided.

- `DOWNLOAD_COMMAND <cmd>...`

  Overrides the command used for the download step ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). If this option is specified, all other download options will be ignored. Providing an empty string for `<cmd>` effectively disables the download step.

- *URL Download*

  - `URL <url1> [<url2>...]`

    List of paths and/or URL(s) of the external project's source. When more than one URL is given, they are tried in turn until one succeeds. A URL may be an ordinary path in the local file system (in which case it must be the only URL provided) or any downloadable URL supported by the [`file(DOWNLOAD)`](https://cmake.org/cmake/help/latest/command/file.html#command:file) command. A local filesystem path may refer to either an existing directory or to an archive file, whereas a URL is expected to point to a file which can be treated as an archive. When an archive is used, it will be unpacked automatically unless the `DOWNLOAD_NO_EXTRACT` option is set to prevent it. The archive type is determined by inspecting the actual content rather than using logic based on the file extension.

    *Changed in version 3.7:* Multiple URLs are allowed.

  - `URL_HASH <algo>=<hashValue>`

    Hash of the archive file to be downloaded. The argument should be of the form `<algo>=<hashValue>` where `algo` can be any of the hashing algorithms supported by the [`file()`](https://cmake.org/cmake/help/latest/command/file.html#command:file) command. Specifying this option is strongly recommended for URL downloads, as it ensures the integrity of the downloaded content. It is also used as a check for a previously downloaded file, allowing connection to the remote location to be avoided altogether if the local directory already has a file from an earlier download that matches the specified hash.

  - `URL_MD5 <md5>`

    Equivalent to `URL_HASH MD5=<md5>`.

  - `DOWNLOAD_NAME <fname>`

    File name to use for the downloaded file. If not given, the end of the URL is used to determine the file name. This option is rarely needed, the default name is generally suitable and is not normally used outside of code internal to the `ExternalProject` module.

  - `DOWNLOAD_EXTRACT_TIMESTAMP <bool>`

    *New in version 3.24.*

    When specified with a true value, the timestamps of the extracted files will match those in the archive. When false, the timestamps of the extracted files will reflect the time at which the extraction was performed. If the download URL changes, timestamps based off those in the archive can result in dependent targets not being rebuilt when they potentially should have been. Therefore, unless the file timestamps are significant to the project in some way, use a false value for this option. If `DOWNLOAD_EXTRACT_TIMESTAMP` is not given, the default is false. See policy [`CMP0135`](https://cmake.org/cmake/help/latest/policy/CMP0135.html#policy:CMP0135).

  - `DOWNLOAD_NO_EXTRACT <bool>`

    *New in version 3.6.*

    Allows the extraction part of the download step to be disabled by passing a boolean true value for this option. If this option is not given, the downloaded contents will be unpacked automatically if required. If extraction has been disabled, the full path to the downloaded file is available as `<DOWNLOADED_FILE>` in subsequent steps or as the property `DOWNLOADED_FILE` with the [`ExternalProject_Get_Property()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_get_property) command.

  - `DOWNLOAD_NO_PROGRESS <bool>`

    Can be used to disable logging the download progress. If this option is not given, download progress messages will be logged.

  - `TIMEOUT <seconds>`

    Maximum time allowed for file download operations.

  - `INACTIVITY_TIMEOUT <seconds>`

    *New in version 3.19.*

    Terminate the operation after a period of inactivity.

  - `HTTP_USERNAME <username>`

    *New in version 3.7.*

    Username for the download operation if authentication is required.

  - `HTTP_PASSWORD <password>`

    *New in version 3.7.*

    Password for the download operation if authentication is required.

  - `HTTP_HEADER <header1> [<header2>...]`

    *New in version 3.7.*

    Provides an arbitrary list of HTTP headers for the download operation. This can be useful for accessing content in systems like AWS, etc.

  - `TLS_VERIFY <bool>`

    Specifies whether certificate verification should be performed for https URLs. If this option is not provided, the default behavior is determined by the [`CMAKE_TLS_VERIFY`](https://cmake.org/cmake/help/latest/variable/CMAKE_TLS_VERIFY.html#variable:CMAKE_TLS_VERIFY) variable (see [`file(DOWNLOAD)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)). If that is also not set, certificate verification will not be performed. In situations where `URL_HASH` cannot be provided, this option can be an alternative verification measure.*Changed in version 3.6:* This option also applies to `git clone` invocations.

  - `TLS_CAINFO <file>`

    Specify a custom certificate authority file to use if `TLS_VERIFY` is enabled. If this option is not specified, the value of the [`CMAKE_TLS_CAINFO`](https://cmake.org/cmake/help/latest/variable/CMAKE_TLS_CAINFO.html#variable:CMAKE_TLS_CAINFO) variable will be used instead (see [`file(DOWNLOAD)`](https://cmake.org/cmake/help/latest/command/file.html#command:file))

  - `NETRC <level>`

    *New in version 3.11.*

    Specify whether the `.netrc` file is to be used for operation. If this option is not specified, the value of the [`CMAKE_NETRC`](https://cmake.org/cmake/help/latest/variable/CMAKE_NETRC.html#variable:CMAKE_NETRC) variable will be used instead (see [`file(DOWNLOAD)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)). Valid levels are:`IGNORED`The `.netrc` file is ignored. This is the default.`OPTIONAL`The `.netrc` file is optional, and information in the URL is preferred. The file will be scanned to find which ever information is not specified in the URL.`REQUIRED`The `.netrc` file is required, and information in the URL is ignored.

  - `NETRC_FILE <file>`

    *New in version 3.11.*

    Specify an alternative `.netrc` file to the one in your home directory if the `NETRC` level is `OPTIONAL` or `REQUIRED`. If this option is not specified, the value of the [`CMAKE_NETRC_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_NETRC_FILE.html#variable:CMAKE_NETRC_FILE) variable will be used instead (see [`file(DOWNLOAD)`](https://cmake.org/cmake/help/latest/command/file.html#command:file))

  *New in version 3.1:* Added support for tbz2, .tar.xz, .txz, and .7z extensions.

  

- *Git*

  NOTE: A git version of 1.6.5 or later is required if this download method is used.

  - `GIT_REPOSITORY <url>`

    URL of the git repository. Any URL understood by the `git` command may be used.

  - `GIT_TAG <tag>`

    Git branch name, tag or commit hash. Note that branch names and tags should generally be specified as remote names (i.e. `origin/myBranch` rather than simply `myBranch`). This ensures that if the remote end has its tag moved or branch rebased or history rewritten, the local clone will still be updated correctly. In general, however, specifying a commit hash should be preferred for a number of reasons:

    - If the local clone already has the commit corresponding to the hash, no `git fetch` needs to be performed to check for changes each time CMake is re-run. This can result in a significant speed up if many external projects are being used.
    - Using a specific git hash ensures that the main project's own history is fully traceable to a specific point in the external project's evolution. If a branch or tag name is used instead, then checking out a specific commit of the main project doesn't necessarily pin the whole build to a specific point in the life of the external project. The lack of such deterministic behavior makes the main project lose traceability and repeatability.

    If `GIT_SHALLOW` is enabled then `GIT_TAG` works only with branch names and tags. A commit hash is not allowed.

    Note that if not provided, `GIT_TAG` defaults to `master`, not the default Git branch name.

  - `GIT_REMOTE_NAME <name>`

    The optional name of the remote. If this option is not specified, it defaults to `origin`.

  - `GIT_SUBMODULES <module>...`

    Specific git submodules that should also be updated. If this option is not provided, all git submodules will be updated.*Changed in version 3.16:* When [`CMP0097`](https://cmake.org/cmake/help/latest/policy/CMP0097.html#policy:CMP0097) is set to `NEW`, if this value is set to an empty string then no submodules are initialized or updated.

  - `GIT_SUBMODULES_RECURSE <bool>`

    *New in version 3.17.*

    Specify whether git submodules (if any) should update recursively by passing the `--recursive` flag to `git submodule update`. If not specified, the default is on.

  - `GIT_SHALLOW <bool>`

    *New in version 3.6.*

    When this option is enabled, the `git clone` operation will be given the `--depth 1` option. This performs a shallow clone, which avoids downloading the whole history and instead retrieves just the commit denoted by the `GIT_TAG` option.

  - `GIT_PROGRESS <bool>`

    *New in version 3.8.*

    When enabled, this option instructs the `git clone` operation to report its progress by passing it the `--progress` option. Without this option, the clone step for large projects may appear to make the build stall, since nothing will be logged until the clone operation finishes. While this option can be used to provide progress to prevent the appearance of the build having stalled, it may also make the build overly noisy if lots of external projects are used.

  - `GIT_CONFIG <option1> [<option2>...]`

    *New in version 3.8.*

    Specify a list of config options to pass to `git clone`. Each option listed will be transformed into its own `--config <option>` on the `git clone` command line, with each option required to be in the form `key=value`.

  - `GIT_REMOTE_UPDATE_STRATEGY <strategy>`

    *New in version 3.18.*

    When `GIT_TAG` refers to a remote branch, this option can be used to specify how the update step behaves. The `<strategy>` must be one of the following:

    - `CHECKOUT`Ignore the local branch and always checkout the branch specified by `GIT_TAG`.
    - `REBASE`Try to rebase the current branch to the one specified by `GIT_TAG`. If there are local uncommitted changes, they will be stashed first and popped again after rebasing. If rebasing or popping stashed changes fail, abort the rebase and halt with an error. When `GIT_REMOTE_UPDATE_STRATEGY` is not present, this is the default strategy unless the default has been overridden with `CMAKE_EP_GIT_REMOTE_UPDATE_STRATEGY` (see below). Note that if the branch specified in `GIT_TAG` is different to the upstream branch currently being tracked, it is not safe to perform a rebase. In that situation, `REBASE` will silently be treated as `CHECKOUT` instead.
    - `REBASE_CHECKOUT`Same as `REBASE` except if the rebase fails, an annotated tag will be created at the original `HEAD` position from before the rebase and then checkout `GIT_TAG` just like the `CHECKOUT` strategy. The message stored on the annotated tag will give information about what was attempted and the tag name will include a timestamp so that each failed run will add a new tag. This strategy ensures no changes will be lost, but updates should always succeed if `GIT_TAG` refers to a valid ref unless there are uncommitted changes that cannot be popped successfully.

    The variable `CMAKE_EP_GIT_REMOTE_UPDATE_STRATEGY` can be set to override the default strategy. This variable should not be set by a project, it is intended for the user to set. It is primarily intended for use in continuous integration scripts to ensure that when history is rewritten on a remote branch, the build doesn't end up with unintended changes or failed builds resulting from conflicts during rebase operations.

- *Subversion*

  ```cmake
  SVN_REPOSITORY <url>
  ```

  URL of the Subversion repository.

  ```
  SVN_REVISION -r<rev>
  ```

  Revision to checkout from the Subversion repository.

  ```
  SVN_USERNAME <username>
  ```

  Username for the Subversion checkout and update.

  ```
  SVN_PASSWORD <password>
  ```

  Password for the Subversion checkout and update.

  ```
  SVN_TRUST_CERT <bool>
  ```

  Specifies whether to trust the Subversion server site certificate. If enabled, the `--trust-server-cert` option is passed to the `svn` checkout and update commands.

- *Mercurial* 

  ```
  HG_REPOSITORY <url>
  ```

  URL of the mercurial repository.

  ```
  HG_TAG <tag>
  ```

  Mercurial branch name, tag or commit id.

- *CVS*

  ```
  CVS_REPOSITORY <cvsroot>
  ```

  CVSROOT of the CVS repository.

  ```
  CVS_MODULE <mod>
  ```

  Module to checkout from the CVS repository.

  ```
  CVS_TAG <tag>
  ```

  Tag to checkout from the CVS repository.

##### **Update Step Options:**

Whenever CMake is re-run, by default the external project's sources will be updated if the download method supports updates (e.g. a git repository would be checked if the `GIT_TAG` does not refer to a specific commit).

- `UPDATE_COMMAND <cmd>...`

  Overrides the download method's update step with a custom command. The command may use [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `UPDATE_DISCONNECTED <bool>`

  *New in version 3.2.

  When enabled, this option causes the update step to be skipped. It does not, however, prevent the download step. The update step can still be added as a step target (see [`ExternalProject_Add_StepTargets()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_steptargets)) and called manually. This is useful if you want to allow developers to build the project when disconnected from the network (the network may still be needed for the download step though).

  When this option is present, it is generally advisable to make the value a cache variable under the developer's control rather than hard-coding it. If this option is not present, the default value is taken from the `EP_UPDATE_DISCONNECTED` directory property. If that is also not defined, updates are performed as normal. The `EP_UPDATE_DISCONNECTED` directory property is intended as a convenience for controlling the `UPDATE_DISCONNECTED` behavior for an entire section of a project's directory hierarchy and may be a more convenient method of giving developers control over whether or not to perform updates (assuming the project also provides a cache variable or some other convenient method for setting the directory property).

  This may cause a step target to be created automatically for the `download` step. See policy [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114).

##### **Patch Step Options:**

```
PATCH_COMMAND <cmd>...
```

Specifies a custom command to patch the sources after an update. By default, no patch command is defined. Note that it can be quite difficult to define an appropriate patch command that performs robustly, especially for download methods such as git where changing the `GIT_TAG` will not discard changes from a previous patch, but the patch command will be called again after updating to the new tag.

##### **Configure Step Options:**

The configure step is run after the download and update steps. By default, the external project is assumed to be a CMake project, but this can be overridden if required.

- `CONFIGURE_COMMAND <cmd>...`

  The default configure command runs CMake with a few options based on the main project. The options added are typically only those needed to use the same generator as the main project, but the `CMAKE_GENERATOR` option can be given to override this. The project is responsible for adding any toolchain details, flags or other settings it wants to re-use from the main project or otherwise specify (see `CMAKE_ARGS`, `CMAKE_CACHE_ARGS` and `CMAKE_CACHE_DEFAULT_ARGS` below).

  For non-CMake external projects, the `CONFIGURE_COMMAND` option must be used to override the default configure command ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). For projects that require no configure step, specify this option with an empty string as the command to execute.

- `CMAKE_COMMAND /.../cmake`

  Specify an alternative cmake executable for the configure step (use an absolute path). This is generally not recommended, since it is usually desirable to use the same CMake version throughout the whole build. This option is ignored if a custom configure command has been specified with `CONFIGURE_COMMAND`.

- `CMAKE_GENERATOR <gen>`

  Override the CMake generator used for the configure step. Without this option, the same generator as the main build will be used. This option is ignored if a custom configure command has been specified with the `CONFIGURE_COMMAND` option.

- `CMAKE_GENERATOR_PLATFORM <platform>`

  *New in version 3.1.*

  Pass a generator-specific platform name to the CMake command (see [`CMAKE_GENERATOR_PLATFORM`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_PLATFORM.html#variable:CMAKE_GENERATOR_PLATFORM)). It is an error to provide this option without the `CMAKE_GENERATOR` option.

- `CMAKE_GENERATOR_TOOLSET <toolset>`

  Pass a generator-specific toolset name to the CMake command (see [`CMAKE_GENERATOR_TOOLSET`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_TOOLSET.html#variable:CMAKE_GENERATOR_TOOLSET)). It is an error to provide this option without the `CMAKE_GENERATOR` option.

- `CMAKE_GENERATOR_INSTANCE <instance>`

  *New in version 3.11.*

  Pass a generator-specific instance selection to the CMake command (see [`CMAKE_GENERATOR_INSTANCE`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_INSTANCE.html#variable:CMAKE_GENERATOR_INSTANCE)). It is an error to provide this option without the `CMAKE_GENERATOR` option.

- `CMAKE_ARGS <arg>...`

  The specified arguments are passed to the `cmake` command line. They can be any argument the `cmake` command understands, not just cache values defined by `-D...` arguments (see also [`CMake Options`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))).

  *New in version 3.3:* Arguments may use [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `CMAKE_CACHE_ARGS <arg>...`

  This is an alternate way of specifying cache variables where command line length issues may become a problem. The arguments are expected to be in the form `-Dvar:STRING=value`, which are then transformed into CMake [`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set) commands with the `FORCE` option used. These `set()` commands are written to a pre-load script which is then applied using the [`cmake -C`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1)) command line option.

  *New in version 3.3:* Arguments may use [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `CMAKE_CACHE_DEFAULT_ARGS <arg>...`

  *New in version 3.2.*

  This is the same as the `CMAKE_CACHE_ARGS` option except the `set()` commands do not include the `FORCE` keyword. This means the values act as initial defaults only and will not override any variables already set from a previous run. Use this option with care, as it can lead to different behavior depending on whether the build starts from a fresh build directory or re-uses previous build contents.

  *New in version 3.15:* If the CMake generator is the `Green Hills MULTI` and not overridden, the original project's settings for the GHS toolset and target system customization cache variables are propagated into the external project.

- `SOURCE_SUBDIR <dir>`

  *New in version 3.7.*

  When no `CONFIGURE_COMMAND` option is specified, the configure step assumes the external project has a `CMakeLists.txt` file at the top of its source tree (i.e. in `SOURCE_DIR`). The `SOURCE_SUBDIR` option can be used to point to an alternative directory within the source tree to use as the top of the CMake source tree instead. This must be a relative path and it will be interpreted as being relative to `SOURCE_DIR`.

  *New in version 3.14:* When `BUILD_IN_SOURCE` option is enabled, the `BUILD_COMMAND` is used to point to an alternative directory within the source tree.

- `CONFIGURE_HANDLED_BY_BUILD <bool>`

  *New in version 3.20.*

  Enabling this option relaxes the dependencies of the configure step on other external projects to order-only. This means the configure step will be executed after its external project dependencies are built but it will not be marked dirty when one of its external project dependencies is rebuilt. This option can be enabled when the build step is smart enough to figure out if the configure step needs to be rerun. CMake and Meson are examples of build systems whose build step is smart enough to know if the configure step needs to be rerun.

##### **Build Step Options:**

If the configure step assumed the external project uses CMake as its build system, the build step will also. Otherwise, the build step will assume a Makefile-based build and simply run `make` with no arguments as the default build step. This can be overridden with custom build commands if required.

If both the main project and the external project use make as their build tool, the build step of the external project is invoked as a recursive make using `$(MAKE)`. This will communicate some build tool settings from the main project to the external project. If either the main project or external project is not using make, no build tool settings will be passed to the external project other than those established by the configure step (i.e. running `ninja -v` in the main project will not pass `-v` to the external project's build step, even if it also uses `ninja` as its build tool).

- `BUILD_COMMAND <cmd>...`

  Overrides the default build command ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). If this option is not given, the default build command will be chosen to integrate with the main build in the most appropriate way (e.g. using recursive `make` for Makefile generators or `cmake --build` if the project uses a CMake build). This option can be specified with an empty string as the command to make the build step do nothing.

- `BUILD_IN_SOURCE <bool>`

  When this option is enabled, the build will be done directly within the external project's source tree. This should generally be avoided, the use of a separate build directory is usually preferred, but it can be useful when the external project assumes an in-source build. The `BINARY_DIR` option should not be specified if building in-source.

- `BUILD_ALWAYS <bool>`

  Enabling this option forces the build step to always be run. This can be the easiest way to robustly ensure that the external project's own build dependencies are evaluated rather than relying on the default success timestamp-based method. This option is not normally needed unless developers are expected to modify something the external project's build depends on in a way that is not detectable via the step target dependencies (e.g. `SOURCE_DIR` is used without a download method and developers might modify the sources in `SOURCE_DIR`).

- `BUILD_BYPRODUCTS <file>...`

  *New in version 3.2.*

  Specifies files that will be generated by the build command but which might or might not have their modification time updated by subsequent builds. These ultimately get passed through as `BYPRODUCTS` to the build step's own underlying call to [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command).

##### **Install Step Options:**

If the configure step assumed the external project uses CMake as its build system, the install step will also. Otherwise, the install step will assume a Makefile-based build and simply run `make install` as the default build step. This can be overridden with custom install commands if required.

- `INSTALL_COMMAND <cmd>...`

  The external project's own install step is invoked as part of the main project's *build*. It is done after the external project's build step and may be before or after the external project's test step (see the `TEST_BEFORE_INSTALL` option below). The external project's install rules are not part of the main project's install rules, so if anything from the external project should be installed as part of the main build, these need to be specified in the main build as additional [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install) commands. The default install step builds the `install` target of the external project, but this can be overridden with a custom command using this option ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). Passing an empty string as the `<cmd>` makes the install step do nothing.

  > Note: If the [`CMAKE_INSTALL_MODE`](https://cmake.org/cmake/help/latest/envvar/CMAKE_INSTALL_MODE.html#envvar:CMAKE_INSTALL_MODE) environment variable is set when the main project is built, it will only have an effect if the following conditions are met:
  >
  > 
  >
  > - The main project's configure step assumed the external project uses CMake as its build system.
  > - The external project's install command actually runs. Note that due to the way `ExternalProject` may use timestamps internally, if nothing the install step depends on needs to be re-executed, the install command might also not need to run.
  >
  > Note also that `ExternalProject` does not check whether the [`CMAKE_INSTALL_MODE`](https://cmake.org/cmake/help/latest/envvar/CMAKE_INSTALL_MODE.html#envvar:CMAKE_INSTALL_MODE) environment variable changes from one run to another.

##### **Test Step Options:**

The test step is only defined if at least one of the following `TEST_...` options are provided.

- `TEST_COMMAND <cmd>...`

  Overrides the default test command ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). If this option is not given, the default behavior of the test step is to build the external project's own `test` target. This option can be specified with `<cmd>` as an empty string, which allows the test step to still be defined, but it will do nothing. Do not specify any of the other `TEST_...` options if providing an empty string as the test command, but prefer to omit all `TEST_...` options altogether if the test step target is not needed.

- `TEST_BEFORE_INSTALL <bool>`

  When this option is enabled, the test step will be executed before the install step. The default behavior is for the test step to run after the install step.

- `TEST_AFTER_INSTALL <bool>`

  This option is mainly useful as a way to indicate that the test step is desired but all default behavior is sufficient. Specifying this option with a boolean true value ensures the test step is defined and that it comes after the install step. If both `TEST_BEFORE_INSTALL` and `TEST_AFTER_INSTALL` are enabled, the latter is silently ignored.

- `TEST_EXCLUDE_FROM_MAIN <bool>`

  *New in version 3.2.*

  If enabled, the main build's default ALL target will not depend on the test step. This can be a useful way of ensuring the test step is defined but only gets invoked when manually requested. This may cause a step target to be created automatically for either the `install` or `build` step. See policy [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114).

##### **Output Logging Options:**

Each of the following `LOG_...` options can be used to wrap the relevant step in a script to capture its output to files. The log files will be created in `LOG_DIR` if supplied or otherwise the `STAMP_DIR` directory with step-specific file names.

- `LOG_DOWNLOAD <bool>`

  When enabled, the output of the download step is logged to files.

- `LOG_UPDATE <bool>`

  When enabled, the output of the update step is logged to files.

- `LOG_PATCH <bool>`

  *New in version 3.14.*

  When enabled, the output of the patch step is logged to files.

- `LOG_CONFIGURE <bool>`

  When enabled, the output of the configure step is logged to files.

- `LOG_BUILD <bool>`

  When enabled, the output of the build step is logged to files.

- `LOG_INSTALL <bool>`

  When enabled, the output of the install step is logged to files.

- `LOG_TEST <bool>`

  When enabled, the output of the test step is logged to files.

- `LOG_MERGED_STDOUTERR <bool>`

  *New in version 3.14.*

  When enabled, stdout and stderr will be merged for any step whose output is being logged to files.

- `LOG_OUTPUT_ON_FAILURE <bool>`

  *New in version 3.14.*

  This option only has an effect if at least one of the other `LOG_<step>` options is enabled. If an error occurs for a step which has logging to file enabled, that step's output will be printed to the console if `LOG_OUTPUT_ON_FAILURE` is set to true. For cases where a large amount of output is recorded, just the end of that output may be printed to the console.

##### **Terminal Access Options:**

*New in version 3.4.*

Steps can be given direct access to the terminal in some cases. Giving a step access to the terminal may allow it to receive terminal input if required, such as for authentication details not provided by other options. With the [`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja) generator, these options place the steps in the `console` [`job pool`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS). Each step can be given access to the terminal individually via the following options:

- `USES_TERMINAL_DOWNLOAD <bool>`

  Give the download step access to the terminal.

- `USES_TERMINAL_UPDATE <bool>`

  Give the update step access to the terminal.

- `USES_TERMINAL_PATCH <bool>`

  *New in version 3.23.*Give the patch step access to the terminal.

- `USES_TERMINAL_CONFIGURE <bool>`

  Give the configure step access to the terminal.

- `USES_TERMINAL_BUILD <bool>`

  Give the build step access to the terminal.

- `USES_TERMINAL_INSTALL <bool>`

  Give the install step access to the terminal.

- `USES_TERMINAL_TEST <bool>`

  Give the test step access to the terminal.

##### **Target Options:**

```
DEPENDS <targets>...
```

Specify other targets on which the external project depends. The other targets will be brought up to date before any of the external project's steps are executed. Because the external project uses additional custom targets internally for each step, the `DEPENDS` option is the most convenient way to ensure all of those steps depend on the other targets. Simply doing [`add_dependencies( )`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies) will not make any of the steps dependent on `<targets>`.

```
EXCLUDE_FROM_ALL <bool>
```

When enabled, this option excludes the external project from the default ALL target of the main build.

```
STEP_TARGETS <step-target>...
```

Generate custom targets for the specified steps. This is required if the steps need to be triggered manually or if they need to be used as dependencies of other targets. If this option is not specified, the default value is taken from the `EP_STEP_TARGETS` directory property. See [`ExternalProject_Add_StepTargets()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_steptargets) below for further discussion of the effects of this option.

```
INDEPENDENT_STEP_TARGETS <step-target>...
```

*Deprecated since version 3.19:* This is allowed only if policy [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114) is not set to `NEW`.

Generates custom targets for the specified steps and prevent these targets from having the usual dependencies applied to them. If this option is not specified, the default value is taken from the `EP_INDEPENDENT_STEP_TARGETS` directory property. This option is mostly useful for allowing individual steps to be driven independently, such as for a CDash setup where each step should be initiated and reported individually rather than as one whole build. See [`ExternalProject_Add_StepTargets()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_steptargets) below for further discussion of the effects of this option.

##### **Miscellaneous Options:**

- `LIST_SEPARATOR <sep>`

  For any of the various `..._COMMAND` options, and `CMAKE_ARGS`, replace `;` with `<sep>` in the specified command lines. This can be useful where list variables may be given in commands where they should end up as space-separated arguments (`<sep>` would be a single space character string in this case).

- `COMMAND <cmd>...`

  Any of the other `..._COMMAND` options can have additional commands appended to them by following them with as many `COMMAND ...` options as needed ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). For example:

  ```cmake
  ExternalProject_Add(example
    ... # Download options, etc.
    BUILD_COMMAND ${CMAKE_COMMAND} -E echo "Starting $<CONFIG> build"
    COMMAND       ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
    COMMAND       ${CMAKE_COMMAND} -E echo "$<CONFIG> build complete"
  )
  ```

It should also be noted that each build step is created via a call to [`ExternalProject_Add_Step()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_step). See that command's documentation for the automatic substitutions that are supported for some options.

### [Obtaining Project Properties](https://cmake.org/cmake/help/latest/module/ExternalProject.html#id4)

#### **ExternalProject_Get_Property**

The `ExternalProject_Get_Property()` function retrieves external project target properties:

```cmake
ExternalProject_Get_Property(<name> <prop1> [<prop2>...])
```

The function stores property values in variables of the same name. Property names correspond to the keyword argument names of `ExternalProject_Add()`. For example, the source directory might be retrieved like so:

```cmake
ExternalProject_Get_property(myExtProj SOURCE_DIR)
message("Source dir of myExtProj = ${SOURCE_DIR}")
```

### [Explicit Step Management](https://cmake.org/cmake/help/latest/module/ExternalProject.html#id5)

The `ExternalProject_Add()` function on its own is often sufficient for incorporating an external project into the main build. Certain scenarios require additional work to implement desired behavior, such as adding in a custom step or making steps available as manually triggerable targets. The `ExternalProject_Add_Step()`, `ExternalProject_Add_StepTargets()` and `ExternalProject_Add_StepDependencies` functions provide the lower level control needed to implement such step-level capabilities.

#### **ExternalProject_Add_Step**

The `ExternalProject_Add_Step()` function specifies an additional custom step for an external project defined by an earlier call to [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add):

```cmake
ExternalProject_Add_Step(<name> <step> [<option>...])
```

`<name>` is the same as the name passed to the original call to [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add). The specified `<step>` must not be one of the pre-defined steps (`mkdir`, `download`, `update`, `patch`, `configure`, `build`, `install` or `test`). The supported options are:

- `COMMAND <cmd>...`

  The command line to be executed by this custom step ([`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) are supported). This option can be repeated multiple times to specify multiple commands to be executed in order.

- `COMMENT "<text>..."`

  Text to be printed when the custom step executes.

- `DEPENDEES <step>...`

  Other steps (custom or pre-defined) on which this step depends.

- `DEPENDERS <step>...`

  Other steps (custom or pre-defined) that depend on this new custom step.

- `DEPENDS <file>...`

  Files on which this custom step depends.

- `INDEPENDENT <bool>`

  *New in version 3.19.*

  Specifies whether this step is independent of the external dependencies specified by the [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add)'s `DEPENDS` option. The default is `FALSE`. Steps marked as independent may depend only on other steps marked independent. See policy [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114).

  Note that this use of the term "independent" refers only to independence from external targets specified by the `DEPENDS` option and is orthogonal to a step's dependencies on other steps.

  If a step target is created for an independent step by the [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) `STEP_TARGETS` option or by the [`ExternalProject_Add_StepTargets()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_steptargets) function, it will not depend on the external targets, but may depend on targets for other steps.

- `BYPRODUCTS <file>...`

  *New in version 3.2.*

  Files that will be generated by this custom step but which might or might not have their modification time updated by subsequent builds. This list of files will ultimately be passed through as the `BYPRODUCTS` option to the [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command) used to implement the custom step internally.

- `ALWAYS <bool>`

  When enabled, this option specifies that the custom step should always be run (i.e. that it is always considered out of date).

- `EXCLUDE_FROM_MAIN <bool>`

  When enabled, this option specifies that the external project's main target does not depend on the custom step. This may cause step targets to be created automatically for the steps on which this step depends. See policy [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114).

- `WORKING_DIRECTORY <dir>`

  Specifies the working directory to set before running the custom step's command. If this option is not specified, the directory will be the value of the [`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR) at the point where `ExternalProject_Add_Step()` was called.

- `LOG <bool>`

  If set, this causes the output from the custom step to be captured to files in the external project's `LOG_DIR` if supplied or `STAMP_DIR`.

- `USES_TERMINAL <bool>`

  If enabled, this gives the custom step direct access to the terminal if possible.

The command line, comment, working directory and byproducts of every standard and custom step are processed to replace the tokens `<SOURCE_DIR>`, `<SOURCE_SUBDIR>`, `<BINARY_DIR>`, `<INSTALL_DIR>` `<TMP_DIR>`, `<DOWNLOAD_DIR>` and `<DOWNLOADED_FILE>` with their corresponding property values defined in the original call to [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add).

*New in version 3.3:* Token replacement is extended to byproducts.

*New in version 3.11:* The `<DOWNLOAD_DIR>` substitution token.

#### **ExternalProject_Add_StepTargets**

The `ExternalProject_Add_StepTargets()` function generates targets for the steps listed. The name of each created target will be of the form `<name>-<step>`:

```cmake
ExternalProject_Add_StepTargets(<name> <step1> [<step2>...])
```

Creating a target for a step allows it to be used as a dependency of another target or to be triggered manually. Having targets for specific steps also allows them to be driven independently of each other by specifying targets on build command lines. For example, you may be submitting to a sub-project based dashboard where you want to drive the configure portion of the build, then submit to the dashboard, followed by the build portion, followed by tests. If you invoke a custom target that depends on a step halfway through the step dependency chain, then all the previous steps will also run to ensure everything is up to date.

Internally, [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) calls [`ExternalProject_Add_Step()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_step) to create each step. If any `STEP_TARGETS` were specified, then `ExternalProject_Add_StepTargets()` will also be called after [`ExternalProject_Add_Step()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_step). Even if a step is not mentioned in the `STEP_TARGETS` option, `ExternalProject_Add_StepTargets()` can still be called later to manually define a target for the step.

The `STEP_TARGETS` option for [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add) is generally the easiest way to ensure targets are created for specific steps of interest. For custom steps, `ExternalProject_Add_StepTargets()` must be called explicitly if a target should also be created for that custom step. An alternative to these two options is to populate the `EP_STEP_TARGETS` directory property. It acts as a default for the step target options and can save having to repeatedly specify the same set of step targets when multiple external projects are being defined.

*New in version 3.19:* If [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114) is set to `NEW`, step targets are fully responsible for holding the custom commands implementing their steps. The primary target created by `ExternalProject_Add` depends on the step targets, and the step targets depend on each other. The target-level dependencies match the file-level dependencies used by the custom commands for each step. The targets for steps created with [`ExternalProject_Add_Step()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_step)'s `INDEPENDENT` option do not depend on the external targets specified by [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add)'s `DEPENDS` option. The predefined steps `mkdir`, `download`, `update`, and `patch` are independent.

If [`CMP0114`](https://cmake.org/cmake/help/latest/policy/CMP0114.html#policy:CMP0114) is not `NEW`, the following deprecated behavior is available:

- A deprecated `NO_DEPENDS` option may be specified immediately after the `<name>` and before the first step. If the `NO_DEPENDS` option is specified, the step target will not depend on the dependencies of the external project (i.e. on any dependencies of the `<name>` custom target created by [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add)). This is usually safe for the `download`, `update` and `patch` steps, since they do not typically require that the dependencies are updated and built. Using `NO_DEPENDS` for any of the other pre-defined steps, however, may break parallel builds. Only use `NO_DEPENDS` where it is certain that the named steps genuinely do not have dependencies. For custom steps, consider whether or not the custom commands require the dependencies to be configured, built and installed.
- The `INDEPENDENT_STEP_TARGETS` option for [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add), or the `EP_INDEPENDENT_STEP_TARGETS` directory property, tells the function to call `ExternalProject_Add_StepTargets()` internally using the `NO_DEPENDS` option for the specified steps.

#### **ExternalProject_Add_StepDependencies**[¶](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_stepdependencies)

*New in version 3.2.*

The `ExternalProject_Add_StepDependencies()` function can be used to add dependencies to a step. The dependencies added must be targets CMake already knows about (these can be ordinary executable or library targets, custom targets or even step targets of another external project):

```cmake
ExternalProject_Add_StepDependencies(<name> <step> <target1> [<target2>...])
```

This function takes care to set both target and file level dependencies and will ensure that parallel builds will not break. It should be used instead of [`add_dependencies()`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies) whenever adding a dependency for some of the step targets generated by the `ExternalProject` module.

## [Examples](https://cmake.org/cmake/help/latest/module/ExternalProject.html#id6)[¶](https://cmake.org/cmake/help/latest/module/ExternalProject.html#examples)

The following example shows how to download and build a hypothetical project called *FooBar* from github:

```cmake
include(ExternalProject)
ExternalProject_Add(foobar
  GIT_REPOSITORY    git@github.com:FooCo/FooBar.git
  GIT_TAG           origin/release/1.2.3
)
```

For the sake of the example, also define a second hypothetical external project called *SecretSauce*, which is downloaded from a web server. Two URLs are given to take advantage of a faster internal network if available, with a fallback to a slower external server. The project is a typical `Makefile` project with no configure step, so some of the default commands are overridden. The build is only required to build the *sauce* target:

```cmake
find_program(MAKE_EXE NAMES gmake nmake make)
ExternalProject_Add(secretsauce
  URL               http://intranet.somecompany.com/artifacts/sauce-2.7.tgz
                    https://www.somecompany.com/downloads/sauce-2.7.zip
  URL_HASH          MD5=d41d8cd98f00b204e9800998ecf8427e
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ${MAKE_EXE} sauce
)
```

Suppose the build step of `secretsauce` requires that `foobar` must already be built. This could be enforced like so:

```cmake
ExternalProject_Add_StepDependencies(secretsauce build foobar)
```

Another alternative would be to create a custom target for `foobar`'s build step and make `secretsauce` depend on that rather than the whole `foobar` project. This would mean `foobar` only needs to be built, it doesn't need to run its install or test steps before `secretsauce` can be built. The dependency can also be defined along with the `secretsauce` project:

```cmake
ExternalProject_Add_StepTargets(foobar build)
ExternalProject_Add(secretsauce
  URL               http://intranet.somecompany.com/artifacts/sauce-2.7.tgz
                    https://www.somecompany.com/downloads/sauce-2.7.zip
  URL_HASH          MD5=d41d8cd98f00b204e9800998ecf8427e
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ${MAKE_EXE} sauce
  DEPENDS           foobar-build
)
```

Instead of calling [`ExternalProject_Add_StepTargets()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add_steptargets), the target could be defined along with the `foobar` project itself:

```cmake
ExternalProject_Add(foobar
  GIT_REPOSITORY git@github.com:FooCo/FooBar.git
  GIT_TAG        origin/release/1.2.3
  STEP_TARGETS   build
)
```

If many external projects should have the same set of step targets, setting a directory property may be more convenient. The `build` step target could be created automatically by setting the `EP_STEP_TARGETS` directory property before creating the external projects with [`ExternalProject_Add()`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add):

```cmake
set_property(DIRECTORY PROPERTY EP_STEP_TARGETS build)
```

Lastly, suppose that `secretsauce` provides a script called `makedoc` which can be used to generate its own documentation. Further suppose that the script expects the output directory to be provided as the only parameter and that it should be run from the `secretsauce` source directory. A custom step and a custom target to trigger the script can be defined like so:

```cmake
ExternalProject_Add_Step(secretsauce docs
  COMMAND           <SOURCE_DIR>/makedoc <BINARY_DIR>
  WORKING_DIRECTORY <SOURCE_DIR>
  COMMENT           "Building secretsauce docs"
  ALWAYS            TRUE
  EXCLUDE_FROM_MAIN TRUE
)
ExternalProject_Add_StepTargets(secretsauce docs)
```

The custom step could then be triggered from the main build like so:

```sh
cmake --build . --target secretsauce-docs
```















