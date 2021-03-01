#!/bin/bash
# Run Login Test Scripts

# Loop through all test folders
for folder_name in */; do
    # Test number and name
    test_number=${folder_name:0:1}
    test_name=login$test_number

    # Input, Output, Transaction
    inp=$test_name.inp
    bto=$test_name.bto
    etf=$test_name.etf

    # Print test name
    echo "Run test " ${folder_name:0:1}

    # Run test
    ../../bank < $folder_name/Expected/$inp > $folder_name/Ran/$bto
done