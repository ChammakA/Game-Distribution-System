"""
Authors: Sammak Ahmed, Fahad Fauzan, and Ammar Hatiya
Date: 2024-03-15
Title: Backend for XP Course Project

Description: This file contains the code relating to the backend of this project. It's intended purpose is to read through 
several files, collect that information, and process the transactions. The transactions range from creating users, deleting users,
selling games, buying games, refunding, and adding credit. The file paths are currently hardcoded. Once, the transactions are processed,
the backend will either update the appropriate files or create new files in their place. 

Input: Files Daily Transactions
Output: Creates a new merged file with all information from the daily transactions
"""

import os
import sys

# class to control daily transactions, will read through the daily transaction files and merge them into one file
class dailyTransactionController:
    def __init__(self, transactionPath):
        self.filePath = transactionPath
    #reads the daily transaction files and merges them into one file
    def mergeDailyTransaction(self):
        if not os.path.exists(self.filePath): # If the directory does not exist, raise an error
            raise FileNotFoundError(f"Error: Directory does not exist: {self.filePath}")
        merged = os.path.join(self.filePath, "mergedTransactionFile.txt") # Path to the merged file
        with open(merged, 'w') as mergedFile: # Open the merged file, if it doesn't exist then creates it
            files = sorted(os.listdir(self.filePath), reverse=False)
            for filename in files: # Loop through the files in the directory
                if filename.endswith(".txt"): # If the file is a .txt file
                    filePath = os.path.join(self.filePath, filename) # combines the directory and the file name

                    with open(filePath, 'r') as file: # Open the file
                        for line in file:
                            mergedFile.write(line.rstrip("\n") + "\n") # Write the line to the merged file, strips everything, then adds new line
        return merged
if __name__ == "__main__":
    if (len(sys.argv) != 2):
        print("Usage: python3 backendMerge.py <path to daily transactions>")
        sys.exit(1)
    transaction_directory = sys.argv[1]
    controller = dailyTransactionController(transaction_directory)
    controller.mergeDailyTransaction()