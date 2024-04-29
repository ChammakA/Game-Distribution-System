"""
Authors: Sammak Ahmed, Fahad Fauzan, and Ammar Hatiya
Date: 2024-03-15
Title: Backend for XP Course Project

Description: This file contains the code relating to the backend of this project. It's intended purpose is to read through 
several files, collect that information, and process the transactions. The transactions range from creating users, deleting users,
selling games, buying games, refunding, and adding credit. The file paths are currently hardcoded. Once, the transactions are processed,
the backend will either update the appropriate files or create new files in their place. 

Input: Files for Available Games
Output: Returns a list of all the available games
"""

import os

# Class to control available games, will read through the text file and store it in list. In the format: [game, seller, price]
class availableGamesController:
    def __init__(self, availableGamesPath):
        self.filePath = availableGamesPath

    def getAvailableGames(self):
        availableGamesList = [] # List to store available games
        try:

            with open(self.filePath, 'r') as file:
                for line in file:
                    line = line.strip()
                    if line.split('_')[0] == "END":
                        break
                    if len(line) != 48:
                        raise ValueError("Error: Incorrect format in file.")
                    game = line[:26].replace("_", " ").strip() # Extract game name
                    seller = line[26:42].replace("_", " ").strip() # Extract seller
                    priceString = line[42:].strip() # Extract price (remove non-numeric characters)
                    try: 
                        price = float(priceString) # Extract price
                    except ValueError:
                        raise ValueError("Error: Price is not a valid number.")
                    availableGamesList.append([game, seller, price]) # Append to the list
        except FileNotFoundError:
            raise
        return availableGamesList