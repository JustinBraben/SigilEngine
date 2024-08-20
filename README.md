[![ci](https://github.com/JustinBraben/SigilEngine/actions/workflows/ci.yml/badge.svg)](https://github.com/JustinBraben/SigilEngine/actions/workflows/ci.yml)

# SigilEngine
Basic 2D Game Engine using SDL libraries and EnTT 

## Build examples
```
cmake --preset=Build-Examples
cmake --build out/build/Build-Examples
```

## Build tests
```
cmake --preset=Build-Tests
cmake --build out/build/Build-Tests
ctest --test-dir out/build/Build-Tests -C Debug -j4
```