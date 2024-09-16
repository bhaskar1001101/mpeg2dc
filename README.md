# MPEG-2 Decoder

This project implements an MPEG-2 video decoder in C. It includes a set of unit tests and FFmpeg-based integration tests to ensure correct functionality.

## Prerequisites

- CMake (version 3.10 or higher)
- A C compiler (gcc or clang)
- FFmpeg (for integration tests)
- Ninja (optional, for faster builds)

## Building the Project

1. Clone the repository:
```bash
git clone https://github.com/yourusername/mpeg2-decoder.git
cd mpeg2-decoder
```

2. Create a build directory and navigate to it:
```bash
mkdir build && cd build
```

3. Configure the project with CMake:
```bash
cmake ..
```
Or, if you prefer to use Ninja:
```bash
cmake -G Ninja ..
```

4. Build the project:
```bash
cmake --build .
```
Or, with Ninja:
```bash
ninja
```

## Running Tests

### Unit Tests

To run all unit tests:
```bash
cmake --build . --target unit_test
```
Or with Ninja:
ninja unit_test

To run a specific unit test:
```bash
./tests/test_bitstream  # Replace with the name of the test you want to run
```

### FFmpeg Benchmark Tests

To run all FFmpeg benchmark tests:
```bash
cmake --build . --target ffmpeg_test
```
Or with Ninja:
```bash
ninja ffmpeg_test
```

To run a specific FFmpeg test:
```bash
ctest -R ffmpeg_test_1_generate  # Replace with the name of the test you want to run
```

### Running All Tests

To run all tests (both unit tests and FFmpeg tests):
```bash
cmake --build . --target test
```
Or with Ninja:
```bash
ninja test
```

## Project Structure

- `src/`: Contains the source files for the MPEG-2 decoder
- `include/`: Contains the header files
- `tests/`: Contains all test-related files
  - `ffmpeg/`: FFmpeg-based integration tests
  - `test_*.c`: Unit test files

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/XYZ`)
3. Commit your changes (`git commit -m 'Add XYZ'`)
4. Push to the branch (`git push origin feature/XYZ`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Resources.

- FFmpeg project for providing a reference implementation.
- MPEG-2 standard (ISO/IEC 13818-2) for the detailed specification.