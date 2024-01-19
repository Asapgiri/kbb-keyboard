cmake_minimum_required(VERSION 3.19)
project(KBB_keyboard LANGUAGES C CXX ASM)

include(Arduino-AVR-CMake/cmake/lto.cmake)
include(Arduino-AVR-CMake/cmake/arduino_core.cmake)
include(Arduino-AVR-CMake/cmake/arduino_hex.cmake)
include(Arduino-AVR-CMake/cmake/arduino_upload.cmake)


add_executable(kbb_keyboard src/main.cpp)

target_include_directories(kbb_keyboard PUBLIC include/)
target_include_directories(kbb_keyboard PUBLIC Keyboard/src/)
target_include_directories(kbb_keyboard PUBLIC ArduinoCore-avr/libraries/HID/src/)
target_include_directories(kbb_keyboard PUBLIC ArduinoCore-avr/libraries/EEPROM/src/)

target_sources(kbb_keyboard PUBLIC src/KBB.cpp)
target_sources(kbb_keyboard PUBLIC src/KeyboardMapInterface.cpp)
target_sources(kbb_keyboard PUBLIC src/MapInterface.cpp)

target_link_libraries(kbb_keyboard PUBLIC ArduinoCore)
target_sources(kbb_keyboard PUBLIC ArduinoCore-avr/libraries/HID/src/HID.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/Keyboard.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_da_DK.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_de_DE.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_en_US.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_es_ES.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_fr_FR.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_hu_HU.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_it_IT.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_pt_PT.cpp)
target_sources(kbb_keyboard PUBLIC Keyboard/src/KeyboardLayout_sv_SE.cpp)
  
target_compile_options(kbb_keyboard PUBLIC
    "-Wall"
    "-Wextra"
    "-pedantic"
)
arduino_avr_hex(kbb_keyboard)

set(ARDUINO_PORT "/dev/ttyACM0"
    CACHE STRING "The serial port for uploading using avrdude")
arduino_avr_upload(kbb_keyboard ${ARDUINO_PORT})

