set -e
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
./build/kvs_cli
