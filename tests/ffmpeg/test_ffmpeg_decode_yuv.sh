#!/bin/bash
echo "Test 2: Decoding MPEG-2 to raw YUV..."
ffmpeg -i files/test_mpeg2.mpg -c:v rawvideo -pix_fmt yuv420p files/test_decoded.yuv

if [ -f files/test_decoded.yuv ]; then
    echo "PASS: MPEG-2 decoded to YUV successfully."
else
    echo "FAIL: Failed to decode MPEG-2 to YUV."
    exit 1
fi