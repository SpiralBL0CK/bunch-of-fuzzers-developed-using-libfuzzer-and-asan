export CC=clang
export CXX=clang++
export CFLAGS="-fsanitize=fuzzer-no-link"
export CXXFLAGS="-fsanitize=fuzzer-no-link"
./configure
make
clang -fsanitize=fuzzer,address fuzzer.c json.o
