cmake_minimum_required(VERSION 3.10)
project(mpeg2_decoder C)

set(CMAKE_C_STANDARD 11)

# Create a library target
add_library(mpeg2_decoder_lib
    mpeg2_decoder.c
    picture.c
    bitstream.c
    vld.c
    idct.c
    motion_comp.c
    picture.c
)

target_include_directories(mpeg2_decoder_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Link math library to mpeg2_decoder_lib
target_link_libraries(mpeg2_decoder_lib PRIVATE m)

# Create the main executable
add_executable(mpeg2_decoder main.c)
target_link_libraries(mpeg2_decoder PRIVATE mpeg2_decoder_lib)