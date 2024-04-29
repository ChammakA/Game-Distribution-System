#!/bin/bash


# The compare_results.sh script begins by locating all subdirectories under the testing/tests/<category_name> directory. 
# If several category names are inputted, it searches through each specified testing category. 
# Once each category is identified, the script iterates over the discovered test cases. 
# For each case, it validates the content of output.txt against results.txt within the test case directory. 
# It also checks for the presence and accuracy of a daily transaction file by comparing a generated dtf_test_<test_name> 
# file against an expected daily_transaction.txt file. The script concludes by summarizing the results, detailing the pass or 
# fail status for each test case and providing a cumulative report of all tests, distinguishing between passed and failed ones.

# Define colors
YELLOW='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Function to list the directory with the most recent date for each primary directory name
list_subdirs() {
    primary_dir="$1"
    declare -A latest_dirs # Associative array to hold the latest directory for each test case

    for dir in "$primary_dir"/*/; do
        dir=${dir%*/} # Strip the trailing slash
        base_name=$(basename "$dir")
        # Extract the test case name more robustly
        test_case_name="${base_name%_*}" # Get everything before the last underscore
        dir_date=$(echo "$base_name" | grep -oE '[0-9]{14}$') # Extract the date

        # Check if this test case has a more recent directory
        if [[ -z ${latest_dirs[$test_case_name]} || $dir_date > ${latest_dirs[$test_case_name]} ]]; then
            latest_dirs[$test_case_name]="$dir"
        fi
    done

    # Return the latest directories for each test case
    for i in "${!latest_dirs[@]}"; do
        echo "${latest_dirs[$i]}"
    done
}

# Array to hold the directories
declare -a dirs

# Counters for statistics
total_tests=0
passed_tests=0
failed_tests=0

# If 'all' is provided as an argument, list all subdirectories in each parent directory
if [ "$1" == "all" ]; then
    for primary_dir in ./testing/tests/*/
    do
        while read -r latest; do
            dirs+=("$latest")
        done < <(list_subdirs "$primary_dir")
    done
else
    # Otherwise, list subdirectories for each provided argument
    for arg in "$@"
    do
        while read -r latest; do
            dirs+=("$latest")
        done < <(list_subdirs "./testing/tests/$arg")
    done
fi

# Check if there are directories to test
if [ ${#dirs[@]} -eq 0 ]; then
    echo "No directories to test."
    exit 1
fi

# Print header
printf "%-70s %-20s %-30s\n" "Test Name" "Terminal Result" "Daily Transaction Result"

# For each directory, run the tests
for dir in "${dirs[@]}"
do
    ((total_tests++)) # Increment total tests counter
    result_dir="$dir"

    # Check if each line of output.txt is found in the results.txt file
    pass=true
    transaction_pass=true
    if [[ -f "$dir/output.txt" ]]; then
        while IFS= read -r line
        do
            if ! grep -Fq "$line" "$result_dir/results.txt"; then
                pass=false
                break
            fi
        done < "$dir/output.txt"
    else
        printf "${RED}output.txt not found in $dir${NC}" # Improved error message
        pass=false
    fi

    # Find the generated daily transaction file. This should already be in the directory.
    daily_transaction_file=$(ls "$dir"/dtf_test_* 2>/dev/null | head -1)
    daily_transaction_expected=$(ls "$dir"/daily_transaction.txt 2>/dev/null | head -1)

    # If there is an expected dtf and no generated one, print error message
    if [[ -z "$daily_transaction_file" && -n "$daily_transaction_expected" ]]; then
        printf "${RED}ERROR: Found expected daily transaction file but no actual daily_transaction_file in $dir.${YELLOW} Ensure it matches the pattern dtf_test_* in input.txt.${NC}\n" # Improved error message
        transaction_pass=false
    elif [[ -z "$daily_transaction_expected" ]]; then   # If there is no expected dtf file, add a warning and pass the test.
        printf "${YELLOW}WARNING: Expected daily transaction file not found in $dir. If this test does not require a daily transaction file comparison ignore this message.${NC}\n" # Improved error message
        transaction_pass=true
    else
        # Check if daily_transaction file is identical to daily_transaction_(date) file
        if [[ -f "$daily_transaction_expected" && -f "$daily_transaction_file" ]]; then
            # If found, compare the files
            if ! diff -q "$daily_transaction_expected" "$daily_transaction_file" > /dev/null; then
                transaction_pass=false
            fi
        else
            # If not found, print an error.
            printf "${RED}daily_transaction.txt or daily_transaction_{date} not found in $dir${NC}\n" # Improved error message
            transaction_pass=false
        fi
    fi

    # Print result and update counters
    pass_str="${RED}FAIL\t\t${NC}"
    transaction_pass_str="${RED}FAIL\t\t${NC}"
    if $pass; then
        pass_str="${GREEN}PASS\t\t${NC}"
    fi
    if $transaction_pass; then
        transaction_pass_str="${GREEN}PASS\t\t${NC}"
    fi

    printf "%-70s %-20s %-30s\n" "${dir}" "$(echo -e $pass_str)" "$(echo -e $transaction_pass_str)"

    if $pass && $transaction_pass; then
        ((passed_tests++))
    else
        ((failed_tests++))
    fi
done

# Display summary
echo "Summary:"
echo "Total Tests Processed: $total_tests"
echo -e "${GREEN}Passed Tests: $passed_tests${NC}"
echo -e "${RED}Failed Tests: $failed_tests${NC}"

