# Native release regression checks

Configure a clean build with `-DBUILD_TESTING=ON`, build it, and run CTest:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

The checks call the built SDK version API and link the ESC/PPS exports, then
parse the official MID-360 and MID-360S sample configurations through the SDK
parser. They need no sensor or network access. The MID-360S fixture asserts
device type 35 and its fixed sensor and host ports; the ordinary MID-360
fixture keeps type 9 as a regression check.
