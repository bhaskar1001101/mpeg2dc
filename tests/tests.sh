#!/bin/bash

# Function to check if a command exists
command_exists () {
    type "$1" &> /dev/null ;
}

# Check if ffmpeg and ffprobe are installed
if ! command_exists ffmpeg || ! command_exists ffprobe ; then
    echo "Error: ffmpeg and ffprobe are required for these tests."
    exit 1
fi

# Create a directory for test files
mkdir -p test_files
cd test_files

# Test 1: Generate a test MPEG-2 file
echo "Test 1: Generating test MPEG-2 file..."
ffmpeg -f lavfi -i testsrc=duration=30:size=720x480:rate=30 -c:v mpeg2video -q:v 2 test_mpeg2.mpg

# Test 2: Decode MPEG-2 to raw YUV
echo "Test 2: Decoding MPEG-2 to raw YUV..."
ffmpeg -i test_mpeg2.mpg -c:v rawvideo -pix_fmt yuv420p test_decoded.yuv

# Test 3: Verify file information
echo "Test 3: Verifying file information..."
ffprobe -v error -select_streams v:0 -count_packets -show_entries stream=codec_name,width,height,r_frame_rate,nb_read_packets -of csv=p=0 test_mpeg2.mpg

# Test 4: Extract I-frames
echo "Test 4: Extracting I-frames..."
ffmpeg -i test_mpeg2.mpg -vf select='eq(pict_type\,I)' -fps_mode passthrough frame%03d.png

# Test 5: Verify GOP structure
echo "Test 5: Verifying GOP structure..."
ffprobe -v error -select_streams v:0 -show_entries frame=pict_type -of default=noprint_wrappers=1 test_mpeg2.mpg

# Test 6: Decode with different output formats
echo "Test 6: Decoding to different output formats..."
ffmpeg -i test_mpeg2.mpg test_decoded.y4m
ffmpeg -i test_mpeg2.mpg test_decoded.mp4

# Test 7: Verify decoding speed
echo "Test 7: Verifying decoding speed..."
time ffmpeg -i test_mpeg2.mpg -c:v rawvideo -pix_fmt yuv420p test_decoded.yuv

# Test 8: Check for any decoding errors or warnings
echo "Test 8: Checking for decoding errors or warnings..."
ffmpeg -v warning -i test_mpeg2.mpg -f null - 2>decoding_log.txt
cat decoding_log.txt

# Test 9: Verify video bitrate
echo "Test 9: Verifying video bitrate..."
ffprobe -v error -select_streams v:0 -show_entries stream=bit_rate -of default=noprint_wrappers=1:nokey=1 test_mpeg2.mpg

# Test 10: Decode specific frames
echo "Test 10: Decoding specific frames..."
ffmpeg -i test_mpeg2.mpg -vf select='gte(n\,10)',setpts=PTS-STARTPTS -fps_mode passthrough frame_10.png
ffmpeg -i test_mpeg2.mpg -vf select='gte(n\,50)',setpts=PTS-STARTPTS -fps_mode passthrough frame_50.png

echo "All tests completed. Check the 'test_files' directory for outputs."