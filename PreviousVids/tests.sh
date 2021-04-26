#!/bin/bash

echo "Checking file input.txt."
expec="$(sha256sum input.txt)"
myout="$(./sha256 input.txt)  input.txt"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "Pass"
else
    echo "Fail"
fi

echo "Checking file empty.txt."
expec="$(sha256sum empty.txt)"
myout="$(./sha256 empty.txt)  empty.txt"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "Pass"
else
    echo "Fail"
fi