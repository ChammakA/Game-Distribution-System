#!/bin/bash

# Define Colours
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# ./distribution-system.exe current_user_accounts.txt available_games.txt game_collection.txt < ./phase6_scripts/Daily/day1_1.txt &
# ./distribution-system.exe current_user_accounts.txt available_games.txt game_collection.txt < ./phase6_scripts/Daily/day1_2.txt &
# ./distribution-system.exe current_user_accounts.txt available_games.txt game_collection.txt < ./phase6_scripts/Daily/day1_3.txt &

if [ ! -f "distribution-system.exe" ]; then
    echo -e "${RED}Error: distribution-system.exe not found in the current directory. Make sure to do ${GREEN}make build${NC} before running tests"
    exit 1
fi

list_subdirs() {
    for dir in "$1"/*/
    do
        dir=${dir%*/}
        echo "${dir}"
    done
}

declare -a dirs

if [ ! -d "storage/daily_transactions" ]; then
    mkdir "storage/daily_transactions"
fi

rm -f storage/daily_transactions/day*

for arg in "$@"
do
    if [ "$arg" == "week" ]; then
        for dir in phase6_scripts/Weekly/*/
        do
            dirs+=($(list_subdirs "$dir"))
        done
    else
        if [ ! -d "phase6_scripts/Weekly/$arg" ]; then
            echo -e "${RED}phase6_scripts/Weekly/$arg was not found.${NC} Did you enter the wrong day?"
            exit 2
        fi
        dirs+=($(list_subdirs "phase6_scripts/Weekly/$arg"))
    fi
done

result_dir="phase6_scripts/Weekly/$1/DTFs"
mkdir -p "$result_dir"

for dir in "${dirs[@]}"
do

    for input_file in "$dir"*
    do
        cmd=$(head -n 1 "$input_file")
        test_name=$(basename "$input_file" .txt)
        mkfifo pipe2
        sed '1d' "$input_file" > pipe2 &
        $cmd < pipe2 2>&1

        rm pipe2
    done

    cp -p storage/daily_transactions/day* "$result_dir/"

done

cd -
cd backend
python3 backendMerge.py "../newfrontend/$result_dir"

wait

python3 backendTransaction.py "../newfrontend/$result_dir/mergedTransactionFile.txt"

