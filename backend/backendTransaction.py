"""
Authors: Sammak Ahmed, Fahad Fauzan, and Ammar Hatiya
Date: 2024-03-15
Title: Backend for XP Course Project

Description: This file contains the code relating to the backend of this project. It's intended purpose is to read through 
several files, collect that information, and process the transactions. The transactions range from creating users, deleting users,
selling games, buying games, refunding, and adding credit. The file paths are currently hardcoded. Once, the transactions are processed,
the backend will either update the appropriate files or create new files in their place. 

Input: Files for Current User Accounts, Available Games, Game Collection, and Daily Transactions
Output: Updated files for Current User Accounts, Available Games, and Game Collection (CURRENTLY IN PROGRESS)
"""

import os
import sys

from backendMerge import dailyTransactionController
from backendReplace import replaceFiles
from backendAvailable import availableGamesController
from backendUser import UserController
from backendGames import GameCollectionController

# Class to control transactions, will go through the merged transaction file and process the transactions
# Transactions range from creating users, deleting users, selling games, buying games, refunding, and adding credit
class TransactionController:
    def __init__(self, transactionPath):
        self.filePath = transactionPath

    # function to read through the merged transaction file and process the transactions, based on the transaction type
    def processTransactions(self, allUsers, allAvailableGames, allGameCollection):
        with open(self.filePath, 'r') as file: # Open the file
            for line in file: # Read line by line
                line = line.strip()  # Remove leading/trailing whitespaces

                # Extract the transaction type
                transactionType = line[:2].replace("_", " ").strip()
                if (transactionType == "00" or transactionType == "99" or transactionType == "07" or transactionType == "08"):
                    continue
                elif (transactionType == "01"):
                    print("Transaction Type: Create")
                    allUsers = self.processCreate(line, allUsers)
                elif (transactionType == "02"):
                    print("Transaction Type: Delete")
                    allUsers, allAvailableGames, allGameCollection = self.processDelete(line, allUsers, allAvailableGames, allGameCollection)
                elif (transactionType == "03"):
                    print("Transaction Type: Sell")
                    allAvailableGames, allGameCollection = self.processSell(line, allAvailableGames, allGameCollection)
                elif (transactionType == "04"):
                    print("Transaction Type: Buy")
                    allUsers, allGameCollection = self.processBuy(line, allUsers, allGameCollection) 
                elif (transactionType == "05"):
                    print("Transaction Type: Refund")
                    allUsers, allGameCollection = self.processRefund(line, allUsers, allGameCollection, allAvailableGames)
                elif (transactionType == "06"):
                    print("Transaction Type: Add Credit")
                    allUsers = self.processAddCredit(line, allUsers)
        return allUsers, allAvailableGames, allGameCollection
    
    # function to process buy transaction by adjusting the buyer's and seller's credit, and adding the game to the buyer's game collection
    def processBuy(self, line, allUsers, allGameCollection):
        game = line[3:29].replace("_", " ").strip() # Extract game name
        seller = line[29:45].replace("_", " ").strip() # Extract seller
        buyer = line[45:61].replace("_", " ").strip() # Extract buyer
        priceString = line[61:].strip()
        price = float(priceString) # Extract price
        for user in allUsers:
            if (user[0] == buyer):
                if (user[2] < price):
                    print("Error: User does not have enough credit to buy the game.")
                    return allUsers, allGameCollection
                else:
                    user[2] -= price
            elif (user[0] == seller):
                if (user[2] + price > 999.99):
                    user[2] = 999.99
                else:
                    user[2] += price
        
        allGameCollection.append([game, buyer])
        return allUsers, allGameCollection

    # function to process add credit transaction by adjusting the user's credit
    def processAddCredit(self, line, allUsers):
        username = line[3:19].replace("_", " ").strip() # Extract username
        type = line[19:35].replace("_", " ").strip() # Extract type
        creditString = line[35:].strip()
        try:
            credit = float(creditString) # Extract credit
        except ValueError:
            raise ValueError("Error: Credit is not a valid number.")
        for user in allUsers:
            if (user[0] == username):
                if (user[2] + credit > 999.99):
                    user[2] = 999.99
                else:
                    user[2] += credit
        return allUsers

    # function to process sell transaction by adding the game to the list of available games and the seller's game collection
    def processSell(self, line, allAvailableGames, allGameCollection):
        game = line[3:29].replace("_", " ").strip() # Extract game name
        seller = line[29:45].replace("_", " ").strip() # Extract seller
        priceString = line[45:].strip()
        price = float(priceString) # Extract price
        allAvailableGames.append([game, seller, price]) #add game to list of available games
        allGameCollection.append([game, seller]) # add game to list of owned games
        return allAvailableGames, allGameCollection

    # function to process refund transaction by adjusting the buyer's and seller's credit and removing the game from the buyer's game collection
    def processRefund(self, line, allUsers, allGameCollection, allAvailableGames): 
        buyer = line[3:19].replace("_", " ").strip() # Extract buyer
        seller = line[19:35].replace("_", " ").strip() # Extract seller
        priceString = line[35:].strip()
        price = float(priceString) # Extract price
        game = "" # sets a default value for the game
        gameExists = False # boolean to check if the game exists
        insufficient = False

        for user in allUsers: # loop to check if the buyer has enough credit to refund the seller
            if (user[0] == seller):
                if (user[2] < price):
                    print("Error: Seller does not have enough credit to refund the buyer.")
                    insufficient = True
                    return allUsers, allGameCollection
                else:
                    user[2] -= price
        if (insufficient == False):
            for user in allUsers: # loop to go through all users and update the buyer and seller's credit
                if (user[0] == buyer):
                    if (user[2] + price > 999.99):
                        user[2] = 999.99
                    else:
                        user[2] += price

        for game in allAvailableGames: # loop to go through all available games and find if there exists a game matching the seller
            if (game[1] == seller):
                for ownedGame in allGameCollection: # loop to then check if that game and buyer exists in the game collection
                    if (ownedGame[1] == buyer and ownedGame[0] == game[0]):
                        allGameCollection.remove(ownedGame) # if it does, remove the game from the buyer's game collection
                        break
                
        return allUsers, allGameCollection

    def processCreate(self, line, allUsers):
        username = line[3:19].replace("_", " ").strip() # Extract username
        type = line[19:22].replace("_", " ").strip() # Extract type
        creditString = line[22:].strip() 
        credit = float(creditString) # Extract credit
        for user in allUsers:
            if (user[0] == username):
                print("Error: Cannot process create transaction as user already exists.")
                return allUsers

        allUsers.append([username, type, credit]) # Append to the list
        return allUsers

    def processDelete(self, line, allUsers, allAvailableGames, allGameCollection):

        username = line[3:19].replace("_", " ").strip() # Extract username
        type = line[19:22].replace("_", " ").strip() # Extract type
        creditString = line[22:].strip()
        credit = float(creditString) # Extract credit

        #Create copies to use for iteration and deletion
        allUserCopy = allUsers.copy() 
        allAvailableGamesCopy = allAvailableGames.copy()
        allGameCollectionCopy = allGameCollection.copy()
        
        # loops that go through each list, and deletes any items that contain that username
        for user in allUserCopy:
            if (user[0] == username):
                allUsers.remove(user)
                break
        for game in allAvailableGamesCopy:
            if (game[1] == username):
                allAvailableGames.remove(game)

        for game in allGameCollectionCopy:
            if (game[1] == username):
                allGameCollection.remove(game)

        return allUsers, allAvailableGames, allGameCollection # Return the updated lists

if __name__ == "__main__":

    if (len(sys.argv) != 2):
        print("Usage: python3 backendTransaction.py")
        sys.exit(1)
    mergedPath = sys.argv[1]
    
    # File paths for the appropiate files [CURRENTLY EDITING COPIES]
    currentAccountsFile= "../newfrontend/storage/current_user_accounts.txt"  
    availableGamesFile = "../newfrontend/storage/available_games.txt" 
    gameCollectionFile = "../newfrontend/storage/game_collection.txt"
    #dailyTransactionFilePath = "../newfrontend/storage/daily_transactions"

    userM = UserController(currentAccountsFile) # Create an instance of the user controller
    allGM = availableGamesController(availableGamesFile) # Create an instance of the available games controller
    gameCM = GameCollectionController(gameCollectionFile) # Create an instance of the game collection controller
    #mergeM = dailyTransactionController(dailyTransactionFilePath) # Create an instance of the daily transaction controller


    allUsers = userM.getUserAccounts() # Get all user accounts
    allAvailableGames = allGM.getAvailableGames() # Get all available games
    allGameCollection = gameCM.getOwnedGames() # Get all owned games
    #mergedPath = mergeM.mergeDailyTransaction() # Merge the daily transaction files

    taskM = TransactionController(mergedPath) # Create an instance of the transaction controller
    
    # FOR TESTING PURPOSES
    # print("************************************")
    # for user in allUsers:
    #     print("Username:",user[0], "\nType:", user[1], "\nCredit:", user[2], "\n")
    # print("************************************")    
    # for game in allAvailableGames:
    #     print("Game Name:",game[0], "\nSeller:", game[1], "\nPrice:", game[2], "\n")
    # print("************************************")
    # for game in allGameCollection:
    #     print("Game Name:",game[0], "\nOwner:", game[1], "\n")
    
    # Process the transactions
    allUsers, allAvailableGames, allGameCollection = taskM.processTransactions(allUsers, allAvailableGames, allGameCollection) 



    replaceM = replaceFiles(currentAccountsFile, availableGamesFile, gameCollectionFile)
    replaceM.writeToUser(allUsers) # Write to the user file
    replaceM.writeToAvailableGames(allAvailableGames) # Write to the available games file
    replaceM.writeToGameCollection(allGameCollection) # Write to the game collection file

# FOR TESTING PURPOSES
    # print("************************************")
    # for user in allUsers:
    #     print("Username:",user[0], "\nType:", user[1], "\nCredit:", user[2], "\n")
    # print("************************************")    
    # for game in allAvailableGames:
    #     print("Game Name:",game[0], "\nSeller:", game[1], "\nPrice:", game[2], "\n")
    # print("************************************")
    # for game in allGameCollection:
    #     print("Game Name:",game[0], "\nOwner:", game[1], "\n")
