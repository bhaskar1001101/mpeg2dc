# Find bash
find_program(BASH_PROGRAM bash)
if(NOT BASH_PROGRAM)
    message(FATAL_ERROR "Bash not found")
endif()

# Define ffmpeg test scripts
set(FFMPEG_TESTS
    test_ffmpeg_generate
    test_ffmpeg_decode_yuv
    # test_3_file_info
    # test_4_extract_iframes
    # test_5_gop_structure
    # test_6_output_formats
    # test_7_decoding_speed
    # test_8_decoding_errors
    # test_9_bitrate
    # test_10_specific_frames
)

# Add individual ffmpeg tests
foreach(test ${FFMPEG_TESTS})
    add_test(
        NAME ${test}
        COMMAND ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/${test}.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg
    )
endforeach()

# Create a custom target for running all ffmpeg tests
add_custom_target(ffmpeg_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS ${FFMPEG_TESTS}
    COMMENT "Running FFmpeg tests"
)

# --------------------------------------------------------

# Unit tests
set(UNIT_TESTS
    test_bitstream
    test_vld
    test_idct
    test_motion_comp
    test_mpeg2_decoder
)

foreach(test ${UNIT_TESTS})
    add_executable(${test} mpeg2dc/${test}.c)
    target_link_libraries(${test} mpeg2_decoder_lib)
    add_test(NAME ${test} COMMAND ${test})
endforeach()

# Create a custom target for running all unit tests
add_custom_target(unit_test
    COMMAND ${CMAKE_CTEST_COMMAND} -R "^test_" --output-on-failure
    DEPENDS ${UNIT_TESTS}
    COMMENT "Running unit tests"
)