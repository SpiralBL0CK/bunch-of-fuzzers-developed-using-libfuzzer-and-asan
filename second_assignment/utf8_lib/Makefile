clang -fsanitize=fuzzer -fprofile-instr-generate -fcoverage-mappingfuzzer.c fuzzer.c 
LLVM_PROFILE_FILE=cov_parse.profraw ./fuzzer -dump_coverage=1 -max_total_time=2 -timeout=100 -close_fd_mask=3 
llvm-profdata merge -sparse cov_parse.profraw -o cov_parse.profdata
llvm-cov show -instr-profile=cov_parse.profdata -format=html \
    -output-dir ./coverage_report fuzz_parse 