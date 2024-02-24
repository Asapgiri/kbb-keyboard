# Read before building!

Before you can build the project, first you have to install the arduino libraries.

## Run the following command if you are on linux:
```
sudo apt install arduino clang lld cmake
```

## After installation, you need to run the newly installed Arduino IDE to install the basic AVR libraries fro building:

Under `Tools > Board > Board Manager`.


# To build, first initialize the subdirectories, then build the project with cmake
```
git submodule init
```
To build in the `build` directoriy:
```
cmake -S. -Bbuild -D CMAKE_TOOLCHAIN_FILE=Arduino-AVR-CMake/cmake/toolchain/leonardo.toolchain.cmake
cmake --build build -j -t kbb_keyboard
```
