# Read before building!

Before you can build the project, first you have to install the arduino libraries.

## Run the following command if you are on linux:
```sh
sudo apt install arduino clang lld cmake
sudo snap install arduino-cli
```
if you install `arduino-cli` with a different method, then change the path to `.arduino15` folder in `ARDUINO_PATH`
cmake variable in `toolchain/avr.toolchain.cmake`.

## After installation, run the avr initalization:
```sh
arduino-cli core install arduino:avr --verbose
```


# To build, first initialize the subdirectories, then build the project with cmake
```
git submodule init
```

To build in the `build` directoriy:
```
cmake -S. -Bbuild -D CMAKE_TOOLCHAIN_FILE=toolchain/leonardo.toolchain.cmake
cmake --build build -j -t kbb_keyboard
```
