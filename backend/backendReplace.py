"""
Authors: Sammak Ahmed, Fahad Fauzan, and Ammar Hatiya
Date: 2024-03-15
Title: Backend for XP Course Project

Description: This file contains the code relating to the backend of this project. It's intended purpose is to read through 
several files, collect that information, and process the transactions. The transactions range from creating users, deleting users,
selling games, buying games, refunding, and adding credit. The file paths are currently hardcoded. Once, the transactions are processed,
the backend will either update the appropriate files or create new files in their place. 

Input: Files for User Accounts, Game Collection, and Available Games
Output: Updates the text files for User Accounts, Game Collection, and Available Games
"""
import os

# Class to replace the files with the updated information
class replaceFiles:
    # Constructor to initialize the file paths
    def __init__(self, userPath, availableGamesPath, gameCollectionPath,):
        self.userPath = userPath
        self.availableGamesPath = availableGamesPath
        self.gameCollectionPath = gameCollectionPath

    # Function to replace the user file with the updated information
    def writeToUser(self, allUsers):
        if not os.path.exists(self.userPath): # If the file does not exist, raise an error
            raise FileNotFoundError(f"Error: File does not exist: {self.userPath}")
        with open(self.userPath, 'w') as file: # opens the file
            for user in allUsers: # loops through the list of users
                formatted_credit = '{:0>9.2f}'.format(user[2]) # Formats the credit to have 2 decimal places, and to have the leadings 0s
                # Write the user information to the file with the specified format
                file.write(user[0].replace(" ", "_").ljust(16, "_") + user[1].replace(" ", "_").ljust(3, "_") + formatted_credit + "\n")
            file.write("END________________{:0>9.2f}\n".format(0)) # Write the end of the file
    
    # Function to replace the available games file with the updated information
    def writeToAvailableGames(self, allAvailableGames):
        if not os.path.exists(self.availableGamesPath): # If the file does not exist, raise an error
            raise FileNotFoundError(f"Error: File does not exist: {self.availableGamesPath}")
        with open(self.availableGamesPath, 'w') as file:
            for game in allAvailableGames:
                formatted_price = '{:0>6.2f}'.format(game[2])
                file.write(game[0].replace(" ", "_").ljust(26, "_") + game[1].replace(" ", "_").ljust(16, "_") + formatted_price + "\n")
            file.write("END_______________________________________{:0>6.2f}\n".format(0))

    # Function to replace the game collection file with the updated information
    def writeToGameCollection(self, allGameCollection):
        if not os.path.exists(self.gameCollectionPath): # If the file does not exist, raise an error
            raise FileNotFoundError(f"Error: File does not exist: {self.gameCollectionPath}")
        with open(self.gameCollectionPath, 'w') as file:
            for game in allGameCollection:
                file.write(game[0].replace(" ", "_").ljust(26, "_") + game[1].replace(" ", "_").ljust(16, "_") + "\n")
            file.write("END_".ljust(42, "_") + "\n")