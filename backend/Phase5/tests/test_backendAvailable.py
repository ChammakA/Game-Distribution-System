
import unittest
import os
from backend.backendAvailable import availableGamesController

# TEST CASES FOR CLASS availableGamesController IN BACKEND.PY
class TestAvailableGamesController(unittest.TestCase):
    def test_getAvailableGames_Valid(self):
        with open('testAvailableGames.txt', 'w') as file: #creates a temp file with the following information recorded in
            file.write("Valid_Game_1______________SellStandard____100.00\n")
            file.write("Valid_Game_2______________SellStandard____000.00\n")
            file.write("END_________________________\n")

        controller = availableGamesController("testAvailableGames.txt") # creates a user controller object
        avGames = controller.getAvailableGames() # gets the user accounts from the file

        self.assertEqual(avGames, [['Valid Game 1', 'SellStandard', 100.0], ['Valid Game 2', 'SellStandard', 0.0]]) # checks if the user accounts are correct
        os.remove('testAvailableGames.txt') # removes the temp file

    # test for NonExistent File
    def test_NonExistent_File(self):
        controller = availableGamesController("Random.txt") # creates a controller but the file does not exist
        with self.assertRaises(FileNotFoundError) as message: # checks for file not found error and records the error message
            controller.getAvailableGames()
        self.assertEqual(str(message.exception), "[Errno 2] No such file or directory: 'Random.txt'") # checks if the error message is correct

    # test for Invalid File Format
    def test_Invalid_File_Format(self):
        with open('testAvailableGames.txt', 'w') as file:
            file.write("Valid_Game_1______________SellStandard____100\n") #invalid format as the line is not the required amount of characters
            file.write("Valid_Game_2______________SellStandard____000.00\n")
            file.write("END_________________________")

        controller = availableGamesController("testAvailableGames.txt") # creates a controller with the file
        with self.assertRaises(ValueError) as message: # checks for value error and records the error message
            controller.getAvailableGames()
        self.assertTrue("Error: Incorrect format in file" in str(message.exception)) # checks if the error message is correct

        os.remove('testAvailableGames.txt') # removes the temp file
    
    # test for Invalid credit value
    def test_Invalid_Credit(self):
        with open('testAvailableGames.txt', 'w') as file:
            file.write("Valid_Game_2______________SellStandard____0ab.00\n") #invalid format as the credits are not a valid number (ab0000.00)
            file.write("END_________________________\n")

        controller = availableGamesController("testAvailableGames.txt") # creates a controller with the file
        with self.assertRaises(ValueError) as message: # checks for value error and records the error message
            controller.getAvailableGames()
        self.assertTrue("Error: Price is not a valid number." in str(message.exception)) # checks if the error message is correct

        os.remove("testAvailableGames.txt") # removes the temp file