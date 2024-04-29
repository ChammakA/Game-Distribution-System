#!/bin/bash

# The run_tests.sh script first finds all the subdirectories under the testing/cases/<category_name> directory.
# If multiple category names are provided then it will search for each of those testing categories.
# After finding each category it will run through all the test cases it found, performing the input from input.txt,
# saving the commands run to test.txt, saving the terminal output to results.txt and copying over the output.txt,
# daily_transaction.txt and newly created daily transaction file in the format dtf_test_<test_name>_<date/time>
# to the testing/tests/<category>/<case_name>/ directory.

# Define Colours
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Check if distribution-system.exe exists in the current directory
if [ ! -f "distribution-system.exe" ]; then
    echo -e "${RED}Error: distribution-system.exe not found in the current directory. Make sure to do ${GREEN}make build${NC} before running tests"
    exit 1
fi

# Function to list all subdirectories in a directory
list_subdirs() {
    for dir in "$1"/*/
    do
        dir=${dir%*/}
        echo "${dir}"
    done
}

# Arrays to hold the directories
declare -a dirs

# Check if the daily_transactions directory exists and if it doesn't, create it
if [ ! -d "storage/daily_transactions" ]; then
    mkdir "storage/daily_transactions"
fi

# Remove existing daily transaction files
rm -f storage/daily_transactions/dtf_test_*

# Parse all arguments
for arg in "$@"
do
    # If 'all' is provided as argument, list all subdirectories in each parent directory
    if [ "$arg" == "all" ]; then
        for dir in testing/cases/*/
        do
            dirs+=($(list_subdirs "$dir"))
        done
    else
        if [ ! -d "testing/cases/$arg" ]; then
            echo -e "${RED}testing/cases/$arg was not found.${NC} Did you enter the wrong test target?"
            exit 2
        fi
        # Otherwise, list subdirectories for the provided argument
        dirs+=($(list_subdirs "testing/cases/$arg"))
    fi
done

# For each directory, run the tests
for dir in "${dirs[@]}"
do
    result_dir="testing/tests/${dir#testing/cases/}_$(date +%Y%m%d%H%M%S)"
    mkdir -p "$result_dir"

    # Read the first line of the input file as the command
    cmd=$(head -n 1 "$dir/input.txt")

    # Create a named pipe
    mkfifo pipe

    # Start the system with all commands from the input file in the background
    sed '1d' "$dir/input.txt" | tee "$result_dir/test.txt" > pipe &

    # Run the command with the named pipe as input
    $cmd < pipe 2>&1 | tee -a "$result_dir/results.txt"

    # Remove the named pipe
    rm pipe

    latest_file=$(find storage/daily_transactions -maxdepth 1 -type f -printf '%T@ %p\n' | sort -n | tail -1 | cut -f2- -d' ')

    cp "$dir/output.txt" "$result_dir/"

    # copy the daily transaction file if it exists
    if [ -f "$dir/daily_transaction.txt" ]; then
        cp -p "$latest_file" "$result_dir/"
        cp "$dir/daily_transaction.txt" "$result_dir/"
    fi
done