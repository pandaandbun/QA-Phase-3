#!/bin/bash
# Run All Test Scripts

# Loop through all test folders
for folder_name in */; do
    cd $folder_name
    bash Test.sh
    cd ..
done