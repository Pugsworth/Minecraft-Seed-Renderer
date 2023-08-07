# Prerequisites
This project depends on vcpkg to manage external dependencies.
To install vcpkg, run the following command:
```shell
git clone --depth 1 https://github.com/Microsoft/vcpkg.git
```
Next, run the bootstrap script to build vcpkg.
### Windows:
```shell
./vcpkg/bootstrap-vcpkg.bat
```
### Linux
```shell
./vcpkg/bootstrap-vcpkg.sh
```


# Installation
This project uses CMake to setup the build system.
To create the build files, run the following command from the root directory:
```shell
cmake -S . -B build -G "MinGW Makefiles"
```

Then, to build the project, run the following command from the root directory:
```shell
make -C ./build
```

Alternatively, we can leverage CMake itself to build and run:
```shell
cmake --build ./build --target run_test
```

# What??
I've been trying to write pure C with CMake as a build system. I keep running into weird stuff that I don't understand. This is causing the development time to inflate massively.
Here's some questions and issues I've run into that I don't have a good answer for:
- I want the executable and any built shared libraries to be deposited into the same "build" directory. I also don't want that directory bloated with intermediate build files. 
    e.g.
    build/
    - _deps/
    - CMakeFiles/
    - lib/
    - vcpkg_installed/
    - cmake_install.cmake
    - CMakeCache.txt
    - Makefile
    - \<binary\>
    - vcpkg-manifest-install.log

What ever happened to build/debug, build/release, etc.?

- Building requires a multiple step process with CMake. Generate the build files with cmake -S -B -etc...
Then, build the actual project with either `make -C build` or `cmake --build build --target <target>`. This is further expounded by utilizing vcpkg needing to do a bunch of stuff which takes forever.

- The actual CMake language is fine. But it's unclear how to use the various commands appropriately. There's two "styles" because CMake has gone through some updates. Using commands like `add_dependencies` is not favored. However, the documentation still uses all of it interchangeably.

- There's some kind of disconnect between VSCode's interpretation of the headers and the actual compiler. I am getting the wrong symbol signatures for Lua functions. I have tried to add the include paths to the `.vscode/settings.json` file, but it doesn't seem to be fully helping.

- Vcpkg seems to do its job well of finding and compiling packages. However, what am I supposed to do when there are libraries that aren't in the package system? I was using a `lib/` folder with subfolders before. That's working for the current libraries I have. This just further confuses how you're supposed to deal with dependencies.

- How do I actually separate debug from release builds?

- I much prefer to just use a text editor like NVim/VSCode over a full IDE like Visual Studio. This seems to add to the friction.