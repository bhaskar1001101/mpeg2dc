#!/bin/bash

# Test 1: Generate a test MPEG-2 file
echo "Test 1: Generating test MPEG-2 file..."

# Use new files.
rm -r files/
mkdir files

ffmpeg -f lavfi -i testsrc=duration=5:size=720x480:rate=30 -c:v mpeg2video -q:v 2 files/test_mpeg2.mpg 2>&1 | tee test_1.log

if [ -f files/test_mpeg2.mpg ]; then
    echo "PASS: Test MPEG-2 file generated successfully."
    exit 0
else
    echo "FAIL: Failed to generate test MPEG-2 file."
    exit 1
fi