#!/bin/bash
# Run Change Plan Test Scripts

# Clear the log
> Test_Result.txt

# Run make
# make -f ../../Makefile || exit
find ../../ -type f -name Makefile -execdir make \;

# Loop through all test folders
for folder_name in */; do
    # Test number and name
    test_number=${folder_name%/}
    test_name=changeplan$test_number

    # Input, Output, Transaction
    inp=$test_name.inp
    bto=$test_name.bto
    etf=$test_name.etf

    # Print test name
    echo "Run test " $test_number

    # Run test
    ../../bank ../../currentbankaccountfile.txt $test_number/Ran/$etf < $test_number/Expected/$inp > $test_number/Ran/$bto

    # Compare results
    # Actual outputs
    actual_etf=$test_number/Ran/$etf
    actual_bto=$test_number/Ran/$bto
    # Expected Outputs
    expected_etf=$test_number/Expected/$etf
    expected_bto=$test_number/Expected/$bto

    echo "Run test " ${folder_name}test_number >> Test_Result.txt

    # ETF differences
    echo "ETF"
    diff $actual_etf $expected_etf

    echo "ETF" >> Test_Result.txt
    diff $actual_etf $expected_etf >> Test_Result.txt

    # BTO differences
    echo "BTO"
    diff $actual_bto $expected_bto

    echo "BTO" >> Test_Result.txt
    diff $actual_bto $expected_bto >> Test_Result.txt

    echo ""  >> Test_Result.txt
done