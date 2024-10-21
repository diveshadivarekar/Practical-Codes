#!/bin/bash

# Prompt the user for the filename
echo "Enter the filename to search in: "
read filename

# Check if the file exists
if [ ! -f "$filename" ]; then
    echo "File not found!"
    exit 1
fi

# Prompt the user for the string to search
echo "Enter the string to search for: "
read searchString

# Use grep to search for the string in the file
grep -n "$searchString" "$filename"

# Check if the grep command found anything
if [ $? -eq 0 ]; then
    echo "Search completed successfully."
else
    echo "String not found in the file."
fi
