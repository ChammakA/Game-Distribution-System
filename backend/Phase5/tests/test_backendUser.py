
import unittest
import os
from backend.backendUser import UserController
# TEST CASES FOR CLASS UserController IN BACKEND.PY
class TestUserController(unittest.TestCase):
    # test for Valid Input
    def test_getUserAccounts_Valid(self):
        with open('testUserAccounts.txt', 'w') as file: #creates a temp file with the following information recorded in
            file.write("SellStandard____SS_000100.00\n")
            file.write("Admin___________AA_000000.00\n")
            file.write("END_________________________\n")

        controller = UserController("testUserAccounts.txt") # creates a user controller object
        userAccounts = controller.getUserAccounts() # gets the user accounts from the file

        self.assertEqual(userAccounts, [['SellStandard', 'SS', 100.0], ['Admin', 'AA', 0.0]]) # checks if the user accounts are correct
        os.remove('testUserAccounts.txt') # removes the temp file

    # test for NonExistent File
    def test_NonExistent_File(self):
        controller = UserController("Random.txt") # creates a controller but the file does not exist
        with self.assertRaises(FileNotFoundError) as message: # checks for file not found error and records the error message
            controller.getUserAccounts()
        self.assertEqual(str(message.exception), "[Errno 2] No such file or directory: 'Random.txt'") # checks if the error message is correct

    # test for Invalid File Format
    def test_Invalid_File_Format(self):
        with open('testUserAccounts.txt', 'w') as file:
            file.write("SellStandard____SS_000100\n") #invalid format as the line is not the required amount of characters
            file.write("Admin___________AA_000000.00\n")
            file.write("END_________________________")

        controller = UserController("testUserAccounts.txt") # creates a controller with the file
        with self.assertRaises(ValueError) as message: # checks for value error and records the error message
            controller.getUserAccounts()
        self.assertTrue("Error: Incorrect format in file" in str(message.exception)) # checks if the error message is correct

        os.remove('testUserAccounts.txt') # removes the temp file
    
    # test for Invalid credit value
    def test_Invalid_Credit(self):
        with open('testUserAccounts.txt', 'w') as file:
            file.write("Admin___________AA_ab0000.00\n") #invalid format as the credits are not a valid number (ab0000.00)
            file.write("END_________________________\n")

        controller = UserController("testUserAccounts.txt") # creates a controller with the file
        with self.assertRaises(ValueError) as message: # checks for value error and records the error message
            controller.getUserAccounts()
        self.assertTrue("Error: Credits are not a valid number." in str(message.exception)) # checks if the error message is correct

        os.remove("testUserAccounts.txt") # removes the temp file