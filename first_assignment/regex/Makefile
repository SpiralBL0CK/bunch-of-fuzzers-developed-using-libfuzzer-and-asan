clang -fsanitize=fuzzer-no-link -c re.c -o target.o
clang -fsanitize=fuzzer,address fuzzer.c target.o -o fuzzer
