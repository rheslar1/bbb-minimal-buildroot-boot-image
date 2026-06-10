cmake_minimum_required(VERSION 3.16)
project(bbb_minimal_buildroot_boot_image LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(bbb_boot_core
  src/BbbBootImage.cpp
)
target_include_directories(bbb_boot_core PUBLIC include)
target_compile_options(bbb_boot_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE bbb_boot_core)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

add_executable(bbb_boot_image_tests tests/BbbBootImageTests.cpp)
target_link_libraries(bbb_boot_image_tests PRIVATE bbb_boot_core)
target_compile_options(bbb_boot_image_tests PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME bbb_boot_image_tests COMMAND bbb_boot_image_tests)
