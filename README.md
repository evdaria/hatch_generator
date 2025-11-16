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

### Example:
```bash
./hatch_generator --angle 45 --step 2.0
```
![test1](https://github.com/user-attachments/assets/5bd097c3-8240-4cd4-b2bf-fa3a021cc4e4)
<svg width="400" height="300" xmlns="http://www.w3.org/2000/svg">
  <rect width="100%" height="100%" fill="white"/>
  <g transform="translate(100 100) scale(10)">
    <polygon points="0,0 20,0 20,10 0,10 " fill="none" stroke="black" stroke-width="0.1"/>
    <line x1="17.1716" y1="0" x2="20" y2="2.82843" stroke="red" stroke-width="0.1"/>
    <line x1="14.3431" y1="0" x2="20" y2="5.65685" stroke="red" stroke-width="0.1"/>
    <line x1="11.5147" y1="0" x2="20" y2="8.48528" stroke="red" stroke-width="0.1"/>
    <line x1="8.68629" y1="0" x2="18.6863" y2="10" stroke="red" stroke-width="0.1"/>
    <line x1="5.85786" y1="0" x2="15.8579" y2="10" stroke="red" stroke-width="0.1"/>
    <line x1="3.02944" y1="0" x2="13.0294" y2="10" stroke="red" stroke-width="0.1"/>
    <line x1="0.20101" y1="0" x2="10.201" y2="10" stroke="red" stroke-width="0.1"/>
    <line x1="0" y1="2.62742" x2="7.37258" y2="10" stroke="red" stroke-width="0.1"/>
    <line x1="0" y1="5.45584" x2="4.54416" y2="10" stroke="red" stroke-width="0.1"/>
    <line x1="0" y1="8.28427" x2="1.71573" y2="10" stroke="red" stroke-width="0.1"/>
  </g>
</svg>
