#!/bin/bash
printf "TEST1 .. "
./btcscript tests/test.hex > tests/_test_output.asm
echo -e "\n" >> tests/_test_output.asm

if ! diff -e tests/_test_output.asm tests/test.asm; then
    printf "FAIL\n"
    exit 1
fi

printf "OK\n"

printf "TEST2 .. "
rm tests/_test_output.asm
./btcscript tests/test2.hex > tests/_test_output.asm
echo -e "\n" >> tests/_test_output.asm

if ! diff -e tests/_test_output.asm tests/test2.asm; then
    printf "FAIL\n"
    exit 1
fi

rm tests/_test_output.asm
printf "OK\n"
exit 0
