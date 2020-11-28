clang -fsanitize=fuzzer-no-link -c hashmap.c -o target.o
clang -fsanitize=fuzzer,address fuzzer.c target.o 
