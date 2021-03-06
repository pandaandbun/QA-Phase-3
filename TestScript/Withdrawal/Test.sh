#!/bin/bash
#Test script iterating over withdrawal test cases

#Clear results
> Test_Result.txt

#Remake changes
find ../../ -type f -name Makefile -execdir make \;

# Copying the master bank account file
master="../../currentbankaccountfile.txt"
copy="./currentbankaccountfile.txt"
cp -r $master $copy

#Iterate over withdrawal test cases by number
for test_number in */; do
    #Test name
    name=withdrawal${test_number%/}

    input_file=$name.inp
    output_file=$name.bto
    etf_file=$name.etf
    
    # Print test name
    echo "Running Test "$name" (Actual Output | Expected Output)"
    echo ""

    # Run test
    ../../bank $copy $test_number/Ran/$etf_file < $test_number/Expected/$input_file > $test_number/Ran/$output_file

    # Compare results
    etf_result=${test_number}Ran/$etf_file
    output_result=${test_number}Ran/$output_file
    # Expected Outputs
    expected_etf=${test_number}Expected/$etf_file
    expected_output=${test_number}Expected/$output_file

    echo $test_number >> Test_Result.txt

    #ETF Diff check
    echo "ETF Diff Check" 
    echo ""
    diff -ysZ --suppress-common-lines $etf_result $expected_etf

    echo "ETF Diff Check" >> Test_Result.txt
    diff -ysZ --suppress-common-lines $etf_result $expected_etf >> Test_Result.txt
    
    echo "---------"
    echo ""

    #Output Diff check
    echo "Output Diff Check" 
    echo ""
    diff -ysZ --suppress-common-lines $output_result $expected_output

    echo "ETF Diff Check" >> Test_Result.txt
    diff -ysZ --suppress-common-lines $output_result $expected_output >> Test_Result.txt

    echo "---------"
done
