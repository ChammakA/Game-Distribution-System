
import unittest
import os
from backend.backendReplace import replaceFiles

# TEST CASES FOR CLASS replaceFiles IN BACKEND.PY
class TestReplaceFiles(unittest.TestCase):
    # test writing to user with valid input
    def test_writeToUser_Valid(self):
        # creating temps files to write into, (empty files)
        with open('tempUserAccounts.txt', 'w') as file:
            pass
        with open('tempAvailable.txt', 'w') as file:
            pass
        with open('tempGameCollection.txt', 'w') as file:
            pass
        
        # creating a controller object with the temp files
        controller = replaceFiles("tempUserAccounts.txt", "tempAvailable.txt", "tempGameCollection.txt")
        allUsers = [['SellStandard', 'SS', 100.0], ['Admin', 'AA', 0.0]] # sample user accounts information
        
        controller.writeToUser(allUsers) # writes the user accounts to the file
        self.assertTrue(os.path.exists("tempUserAccounts.txt")) # checks if the file exists
        with open("tempUserAccounts.txt", 'r') as file: # opens the file and stores the contents into a variable as actual output
            actual_output = file.read()
        # this is the expected output of the file
        expected_output = "SellStandard____SS_000100.00\nAdmin___________AA_000000.00\nEND_________________________\n"
        self.assertEqual(actual_output, expected_output) # checks if the actual output is the same as the expected output

        # removes the temp files
        os.remove("tempUserAccounts.txt")
        os.remove("tempAvailable.txt")
        os.remove("tempGameCollection.txt")
    
    def test_writeToAvailable_Valid(self):
        with open('tempUserAccounts.txt', 'w') as file:
            pass
        with open('tempAvailable.txt', 'w') as file:
            pass
        with open('tempGameCollection.txt', 'w') as file:
            pass

        controller = replaceFiles("tempUserAccounts.txt", "tempAvailable.txt", "tempGameCollection.txt")
        allAvailable = [['Valid Game 1', 'SellStandard', 100.0]]
        
        controller.writeToAvailableGames(allAvailable)
        self.assertTrue(os.path.exists("tempAvailable.txt"))
        with open("tempAvailable.txt", 'r') as file:
            actual_output = file.read()
        expected_output = "Valid_Game_1______________SellStandard____100.00\nEND_________________________\n"
        self.assertEqual(actual_output, expected_output)

        os.remove("tempUserAccounts.txt")
        os.remove("tempAvailable.txt")
        os.remove("tempGameCollection.txt")
    
    def test_writeToGameCollection_Valid(self):
        with open('tempUserAccounts.txt', 'w') as file:
            pass
        with open('tempAvailable.txt', 'w') as file:
            pass
        with open('tempGameCollection.txt', 'w') as file:
            pass

        controller = replaceFiles("tempUserAccounts.txt", "tempAvailable.txt", "tempGameCollection.txt")
        allGames = [['Owned Game', 'Admin']]
        
        controller.writeToGameCollection(allGames)
        self.assertTrue(os.path.exists("tempGameCollection.txt"))
        with open("tempGameCollection.txt", 'r') as file:
            actual_output = file.read()
        expected_output = "Owned_Game________________Admin__________\nEND_________________________\n"
        self.assertEqual(actual_output, expected_output)

        os.remove("tempUserAccounts.txt")
        os.remove("tempAvailable.txt")
        os.remove("tempGameCollection.txt")
    
    def test_writeToUser_InvalidFile(self):
        # attempts to create a controller object with non-existent files
        controller = replaceFiles("fakeUser.txt", "tempAvailable.txt", "tempGameCollection.txt")
        allUsers = [['SellStandard', 'SS', 100.0], ['Admin', 'AA', 0.0]] # sample user accounts information

        with self.assertRaises(FileNotFoundError) as message: # checks for file not found error and records the error message
            controller.writeToUser(allUsers)
        self.assertEqual(str(message.exception), "Error: File does not exist: fakeUser.txt") # checks if the error message is correct

    def test_writeToAvailable_InvalidFile(self):

        controller = replaceFiles("tempUserAccounts.txt", "fakeAvailable.txt", "tempGameCollection.txt")
        allAvailable = [['Valid Game 1', 'SellStandard', 100.0]]

        with self.assertRaises(FileNotFoundError) as message:
            controller.writeToAvailableGames(allAvailable)
        self.assertEqual(str(message.exception), "Error: File does not exist: fakeAvailable.txt")

    def test_writeToGameCollection_InvalidFile(self):

        controller = replaceFiles("tempUserAccounts.txt", "tempAvailable.txt", "fakeCollection.txt")
        allGames = [['Owned Game', 'Admin']]

        with self.assertRaises(FileNotFoundError) as message:
            controller.writeToGameCollection(allGames)
        self.assertEqual(str(message.exception), "Error: File does not exist: fakeCollection.txt")