"""
Authors: Sammak Ahmed, Fahad Fauzan, and Ammar Hatiya
Date: 2024-03-15
Title: Backend for XP Course Project

Description: This file contains the code relating to the backend of this project. It's intended purpose is to read through 
several files, collect that information, and process the transactions. The transactions range from creating users, deleting users,
selling games, buying games, refunding, and adding credit. The file paths are currently hardcoded. Once, the transactions are processed,
the backend will either update the appropriate files or create new files in their place. 

Input: Files for Game Collection
Output: Returns a list of all the owned games
"""

import os

# Class to control game collection, will read through the text file and store it in list. In the format: [game, owner]    
class GameCollectionController:
    def __init__(self, gameCollectionPath):
        self.filePath = gameCollectionPath
    def getOwnedGames(self):
        ownedGames = [] # List to store owned games
        try:
            with open(self.filePath, 'r') as file:
                for line in file:
                    line = line.strip()
                    if len(line) != 42:
                        raise ValueError("Error: Incorrect format in file.")
                    if line.split('_')[0] == "END":
                        break
                    game = line[:25].replace("_", " ").strip() # Extract game name
                    owner = line[25:].replace("_", " ").strip() # Extract owner
                    ownedGames.append([game, owner]) # Append to the list
        except FileNotFoundError:
            raise
        return ownedGames