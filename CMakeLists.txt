cmake_minimum_required(VERSION 3.20)
project(Astrata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(astrata
    src/main.cpp
    src/astrata.cpp
    src/astrata.hpp
    src/tokenizer.cpp
    src/tokenizer.hpp
    src/model.cpp
    src/model.hpp
)

if (MSVC)
    target_compile_options(astrata PRIVATE /W4 /O2)
else()
    target_compile_options(astrata PRIVATE -Wall -Wextra -Wpedantic -O2)
endif()

include(GNUInstallDirs)
install(TARGETS astrata RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
