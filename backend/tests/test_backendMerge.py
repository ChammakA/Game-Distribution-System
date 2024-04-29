import unittest
import os
from backend.backendMerge import dailyTransactionController

# TEST CASES FOR CLASS dailyTransactionController IN BACKEND.PY
class TestDailyTransactionController(unittest.TestCase):
    # test for valid input
    def test_mergeTransaction_Valid(self):

        with open('testDailyTransaction.txt', 'w') as file: # creates a temp file as a sample transaction file
            file.write("04_Valid_Game_1______________SellStandard____BuyStandard_____000100.00\n")
            file.write("00\n")
        with open('testDailyTransaction2.txt', 'w') as file: # creates a temp file as a sample transaction file
            file.write("06_BuyStandard_____BS_000100.00\n")
            file.write("00\n")

        controller = dailyTransactionController(".") # creates a controller object with the directory
        merged = controller.mergeDailyTransaction() # merges the daily transaction files and stores the path to it
        self.assertTrue(os.path.exists(merged)) # checks if that merged file exists

        with open(merged, 'r') as file: # opens the merged file and stores the contents into a variable
            actual_output = file.read()
        # this is the expected output of the merged file
        expected_output = "04_Valid_Game_1______________SellStandard____BuyStandard_____000100.00\n00\n06_BuyStandard_____BS_000100.00\n00\n"
        self.assertEqual(actual_output, expected_output) # checks to see if the actual output is the same as the expected output

        # removes the temp files and the merged file
        os.remove(merged)
        os.remove("testDailyTransaction.txt")
        os.remove("testDailyTransaction2.txt")
    
    # test for if there are no transaction files in the directory
    def test_mergeTransaction_NoFiles(self):
        controller = dailyTransactionController(".") # creates a controller object with the directory
        merged = controller.mergeDailyTransaction()

        self.assertTrue(os.path.exists(merged)) # checks if the merged file exists
        self.assertEqual(os.path.getsize(merged), 0) # checks if the merged file is empty since size is 0

    # test for if the directory does not exist or is wrong
    def test_WrongDirectory(self):
        controller = dailyTransactionController("fakeTransaction") # creates a controller object with a wrong directory
        with self.assertRaises(FileNotFoundError) as message: # checks for file not found error and records the error message
            controller.mergeDailyTransaction()
        self.assertEqual(str(message.exception), "Error: Directory does not exist: fakeTransaction") # checks if the error message is correct