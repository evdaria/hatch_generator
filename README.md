# Hatch Generator

C++ command-line application for generating hatch fill patterns in rectangular polygons.

## Features
- Configurable hatch angle (0-180°) and line spacing
- SVG output format
- CMake build system
- Command-line interface

## Build
```bash
mkdir build && cd build
cmake .. && make
```


## Usage
```bash
./hatch_generator --angle <angle> --step <step>
```

### Examples:
```bash
./hatch_generator --angle 45 --step 2.0
./hatch_generator --angle 90 --step 1.5
```
