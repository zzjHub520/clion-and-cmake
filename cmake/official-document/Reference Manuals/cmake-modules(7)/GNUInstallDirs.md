# [GNUInstallDirs](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#)

Define GNU standard installation directories

Provides install directory variables as defined by the [GNU Coding Standards](https://www.gnu.org/prep/standards/html_node/Directory-Variables.html).

## [Result Variables](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#result-variables)

Inclusion of this module defines the following variables:

```
CMAKE_INSTALL_<dir>
```

> Destination for files of a given type. This value may be passed to the `DESTINATION` options of [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install) commands for the corresponding file type. It should typically be a path relative to the installation prefix so that it can be converted to an absolute path in a relocatable way (see `CMAKE_INSTALL_FULL_<dir>`). However, an absolute path is also allowed.

```
CMAKE_INSTALL_FULL_<dir>
```

> The absolute path generated from the corresponding `CMAKE_INSTALL_<dir>` value. If the value is not already an absolute path, an absolute path is constructed typically by prepending the value of the [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX) variable. However, there are some [special cases](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#special-cases) as documented below.

where `<dir>` is one of:

- `BINDIR`

  user executables (`bin`)

- `SBINDIR`

  system admin executables (`sbin`)

- `LIBEXECDIR`

  program executables (`libexec`)

- `SYSCONFDIR`

  read-only single-machine data (`etc`)

- `SHAREDSTATEDIR`

  modifiable architecture-independent data (`com`)

- `LOCALSTATEDIR`

  modifiable single-machine data (`var`)

- `RUNSTATEDIR`

  *New in version 3.9:* run-time variable data (`LOCALSTATEDIR/run`)

- `LIBDIR`

  object code libraries (`lib` or `lib64`)On Debian, this may be `lib/<multiarch-tuple>` when [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX) is `/usr`.

- `INCLUDEDIR`

  C header files (`include`)

- `OLDINCLUDEDIR`

  C header files for non-gcc (`/usr/include`)

- `DATAROOTDIR`

  read-only architecture-independent data root (`share`)

- `DATADIR`

  read-only architecture-independent data (`DATAROOTDIR`)

- `INFODIR`

  info documentation (`DATAROOTDIR/info`)

- `LOCALEDIR`

  locale-dependent data (`DATAROOTDIR/locale`)

- `MANDIR`

  man documentation (`DATAROOTDIR/man`)

- `DOCDIR`

  documentation root (`DATAROOTDIR/doc/PROJECT_NAME`)

If the includer does not define a value the above-shown default will be used and the value will appear in the cache for editing by the user.

## [Special Cases](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#special-cases)

*New in version 3.4.*

The following values of [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX) are special:

```
/
```

> For `<dir>` other than the `SYSCONFDIR`, `LOCALSTATEDIR` and `RUNSTATEDIR`, the value of `CMAKE_INSTALL_<dir>` is prefixed with `usr/` if it is not user-specified as an absolute path. For example, the `INCLUDEDIR` value `include` becomes `usr/include`. This is required by the [GNU Coding Standards](https://www.gnu.org/prep/standards/html_node/Directory-Variables.html), which state:
>
> > When building the complete GNU system, the prefix will be empty and `/usr` will be a symbolic link to `/`.

```
/usr
```

> For `<dir>` equal to `SYSCONFDIR`, `LOCALSTATEDIR` or `RUNSTATEDIR`, the `CMAKE_INSTALL_FULL_<dir>` is computed by prepending just `/` to the value of `CMAKE_INSTALL_<dir>` if it is not user-specified as an absolute path. For example, the `SYSCONFDIR` value `etc` becomes `/etc`. This is required by the [GNU Coding Standards](https://www.gnu.org/prep/standards/html_node/Directory-Variables.html).

```
/opt/...
```

> For `<dir>` equal to `SYSCONFDIR`, `LOCALSTATEDIR` or `RUNSTATEDIR`, the `CMAKE_INSTALL_FULL_<dir>` is computed by *appending* the prefix to the value of `CMAKE_INSTALL_<dir>` if it is not user-specified as an absolute path. For example, the `SYSCONFDIR` value `etc` becomes `/etc/opt/...`. This is defined by the [Filesystem Hierarchy Standard](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html).
>
> This behavior does not apply to paths under `/opt/homebrew/...`.

## [Macros](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#macros)

**GNUInstallDirs_get_absolute_install_dir**

```cmake
GNUInstallDirs_get_absolute_install_dir(absvar var dirname)
```

*New in version 3.7.*

Set the given variable `absvar` to the absolute path contained within the variable `var`. This is to allow the computation of an absolute path, accounting for all the special cases documented above. While this macro is used to compute the various `CMAKE_INSTALL_FULL_<dir>` variables, it is exposed publicly to allow users who create additional path variables to also compute absolute paths where necessary, using the same logic. `dirname` is the directory name to get, e.g. `BINDIR`.

*Changed in version 3.20:* Added the `<dirname>` parameter. Previous versions of CMake passed this value through the variable `${dir}`.