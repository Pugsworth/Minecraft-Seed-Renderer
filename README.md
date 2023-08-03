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