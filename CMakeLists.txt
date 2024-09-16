cmake_minimum_required(VERSION 3.10)
project(MPEG2Decoder)


# Add your source directory
add_subdirectory(src)

# Add the tests
enable_testing()
add_subdirectory(tests)