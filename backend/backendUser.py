"""
Authors: Sammak Ahmed, Fahad Fauzan, and Ammar Hatiya
Date: 2024-03-15
Title: Backend for XP Course Project

Description: This file contains the code relating to the backend of this project. It's intended purpose is to read through 
several files, collect that information, and process the transactions. The transactions range from creating users, deleting users,
selling games, buying games, refunding, and adding credit. The file paths are currently hardcoded. Once, the transactions are processed,
the backend will either update the appropriate files or create new files in their place. 

Input: Files for User Accounts
Output: Creates a list of all the information acquired from user accounts file
"""

import os

# Class to control user accounts, will read through the text file and store it in list. In the format [username, type, credits]
class UserController:
    def __init__ (self, userPath):
        self.filePath = userPath

    def getUserAccounts(self):
        allUsersList = [] # List to store user accounts
        try:
            with open(self.filePath, 'r') as file: # Open the file
                for line in file: # Read line by line
                    line = line.strip()  # Remove leading/trailing whitespaces

                    if line.split('_')[0] == "END":  # If the line is 'END', stop reading
                        break
                    if len(line) != 28: # If the line is less than 28 characters, it is invalid format
                        raise ValueError("Error: Incorrect format in file.")
                    
                    username = line[:16].replace("_", " ").strip() # Extract username
                    type = line[16:19].replace("_", " ").strip() # Extract type 
                    creditString = line[19:].strip() # Extract credits (remove non-numeric characters

                    try:
                        credits = float(creditString) # Convert credits to float (decimal number
                    except ValueError: # If the credits are not a valid number, raise an error
                        raise ValueError("Error: Credits are not a valid number.")
                    
                    allUsersList.append([username, type, credits])  # Append to the list
        except FileNotFoundError:
            raise #if the file name is invalid or not found raise an error
        return allUsersList