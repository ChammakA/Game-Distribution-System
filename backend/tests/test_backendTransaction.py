
import unittest
import os
from backend.backendTransaction import TransactionController

class TestTransactionController(unittest.TestCase):
    # test for valid input on processTransactions
    def test_processTransactions_Valid(self):
        with open("testTransactions.txt", 'w') as file:
            file.write("04_Valid_Game_1______________SellStandard____BuyStandard_____000100.00\n")
            file.write("00\n")
            file.write("06_BuyStandard_____BS_000100.00\n")
            file.write("03_Valid Game 3______________Admin___________000055.50\n")
            file.write("05_BuyStandard_____SellStandard____000100.00\n")
            file.write("01_tempA___________AA_000.00\n")
            file.write("02_SellStandard____SS_000100.00\n")

        allUsers = [['SellStandard', 'SS', 100.0], ['Admin', 'AA', 0.0], ['BuyStandard', 'BS', 100.0]]
        allAvailable = [['Valid Game 1', 'SellStandard', 100.0], ['Valid Game 2', 'SellStandard', 0.0]]
        allGames = [['Owned Game', 'Admin'], ['Valid Game 1', 'SellStandard'], ['Valid Game 2', 'SellStandard']]  

        controller = TransactionController("testTransactions.txt")
        expectedUser, expectedAvailable, expectedGames = controller.processTransactions(allUsers, allAvailable, allGames)

        actualUser = [['Admin', 'AA', 0.0], ['BuyStandard', 'BS', 200.0], ['tempA', 'AA', 0.0]]
        actualAvailable = [['Valid Game 3', 'Admin', 55.5]]
        actualGames = [['Owned Game', 'Admin'], ['Valid Game 3', 'Admin']]

        self.assertEqual(expectedUser, actualUser)
        self.assertEqual(expectedAvailable, actualAvailable)
        self.assertEqual(expectedGames, actualGames)

        os.remove("testTransactions.txt")

    # test for if sellers credit goes above max during buy
    def test_processBuy_Max(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "04_Valid_Game_1______________SellStandard____BuyStandard_____000100.00\n"

        allUsers = [['BuyStandard', 'BS', 100.0], ['SellStandard', 'SS', 900.0]]
        allGames = [['Valid Game 1', 'SellStandard']]

        controller = TransactionController("testTransactions.txt")
        expectedUser, expectedGames = controller.processBuy(line, allUsers, allGames)

        actualUser = [['BuyStandard', 'BS', 0.0], ['SellStandard', 'SS', 999.99]]
        actualGames = [['Valid Game 1', 'SellStandard'], ['Valid Game 1', 'BuyStandard']]

        self.assertEqual(expectedUser, actualUser)
        self.assertEqual(expectedGames, actualGames)
        os.remove("testTransactions.txt")

    # test for if buyers credit goes below 0 during buy
    def test_processBuy_Insufficient(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "04_Valid_Game_1______________SellStandard____BuyStandard_____000100.00\n"

        allUsers = [['BuyStandard', 'BS', 0.0], ['SellStandard', 'SS', 0.0]]
        allGames = [['Valid Game 1', 'SellStandard']]

        controller = TransactionController("testTransactions.txt")
        expectedUser, expectedGames = controller.processBuy(line, allUsers, allGames)

        actualUser = [['BuyStandard', 'BS', 0.0], ['SellStandard', 'SS', 0.0]]
        actualGames = [['Valid Game 1', 'SellStandard']]

        self.assertEqual(expectedUser, actualUser)
        self.assertEqual(expectedGames, actualGames)

        os.remove("testTransactions.txt")

    # test for if the users already exists when creating a new user
    def test_processCreate_Existing(self):
        with open("testTransactions.txt", 'w') as file:
            pass

        line = "01_tempA___________AA_000.00\n"

        allUsers = [['tempA', 'AA', 0.0]]

        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processCreate(line, allUsers)

        actualUsers = [['tempA', 'AA', 0.0]]
        self.assertEqual(expectedUser, actualUsers)
        os.remove("testTransactions.txt")
    
    # test for if buyers credit will go above max during refund
    def test_processRefund_Max(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "05_BuyStandard_____SellStandard____000100.00"

        allUsers = [['BuyStandard', 'BS', 900.0], ['SellStandard', 'SS', 100.0]]
        allAvailable = [['Valid Game 1', 'SellStandard', 100.0], ['Valid Game 1', 'BuyStandard', 100.0]]
        allGames = [['Valid Game 1', 'SellStandard']]

        controller = TransactionController("testTransactions.txt")
        expectedUser, expectedGames = controller.processRefund(line, allUsers, allGames, allAvailable)

        actualUser = [['BuyStandard', 'BS', 999.99], ['SellStandard', 'SS', 0.0]]
        actualGames = [['Valid Game 1', 'SellStandard']]

        self.assertEqual(expectedUser, actualUser)
        self.assertEqual(expectedGames, actualGames)

        os.remove("testTransactions.txt")

    #test for if sellers credit will go below 0 during refund
    def test_processRefund_Insufficient(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "05_BuyStandard_____SellStandard____000100.00"

        allUsers = [['BuyStandard', 'BS', 0.0], ['SellStandard', 'SS', 0.0]]
        allAvailable = [['Valid Game 1', 'SellStandard', 0.0]]
        allGames = [['Valid Game 1', 'SellStandard']]

        controller = TransactionController("testTransactions.txt")
        expectedUser, expectedGames = controller.processRefund(line, allUsers, allGames, allAvailable)

        actualUser = [['BuyStandard', 'BS', 0.0], ['SellStandard', 'SS', 0.0]]
        actualGames = [['Valid Game 1', 'SellStandard']]

        self.assertEqual(expectedUser, actualUser)
        self.assertEqual(expectedGames, actualGames)

        os.remove("testTransactions.txt")


    # User exists, and their current credit plus the provided credit exceeds 999.99 (edge case).
    def test_processAddCredit_Max(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_BuyStandard_____BS_000100.00\n"

        allUsers = [['BuyStandard', 'BS', 900.0]]

        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processAddCredit(line, allUsers)

        actualUser = [['BuyStandard', 'BS', 999.99]]

        self.assertEqual(expectedUser, actualUser)
        os.remove("testTransactions.txt")
    # User exists, and their current credit plus the provided credit is less than or equal to 999.99.
    def test_processAddCredit_Valid(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_BuyStandard_____BS_000100.00\n"

        allUsers = [['BuyStandard', 'BS', 0.0]]

        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processAddCredit(line, allUsers)

        actualUser = [['BuyStandard', 'BS', 100.0]]

        self.assertEqual(expectedUser, actualUser)
        os.remove("testTransactions.txt")

    # User exists, and the provided credit is negative or invalid
    def test_processAddCredit_Invalid(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_BuyStandard_____BS_00-100.00\n"

        allUsers = [['BuyStandard', 'BS', 0.0]]

        controller = TransactionController("testTransactions.txt")
        with self.assertRaises(ValueError) as message:
            controller.processAddCredit(line, allUsers)
        self.assertEqual(str(message.exception), "Error: Credit is not a valid number.")

    # User exists, and the provided credit is zero.
    def test_processAddCredit_Zero(self):
        
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_BuyStandard_____BS_000000.00"

        allUsers = [['BuyStandard', 'BS', 0.0]]
        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processAddCredit(line, allUsers)

        actualUser = [['BuyStandard', 'BS', 0.0]]
        self.assertEqual(expectedUser, actualUser)

    # The user does not exist, and the provided credit is any positive value
    def test_processAddCredit_Fake_User_Valid(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_FakeUser________BS_000100.00\n"

        allUsers = [['SellStandard', 'SS', 100.0]]

        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processAddCredit(line, allUsers)

        actualUser = [['SellStandard', 'SS', 100.0]]

        self.assertEqual(expectedUser, actualUser)
        os.remove("testTransactions.txt")
    
    # The user does not exist, and the provided credit is zero.
    def test_processAddCredit_Fake_User_Zero(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_FakeUser________BS_000000.00\n"

        allUsers = [['SellStandard', 'SS', 100.0]]

        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processAddCredit(line, allUsers)

        actualUser = [['SellStandard', 'SS', 100.0]]

        self.assertEqual(expectedUser, actualUser)
        os.remove("testTransactions.txt")

    # The user does not exist, and the provided credit is negative
    def test_processAddCredit_Fake_User_Invalid(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_FakeUser________BS_00-100.00\n"

        allUsers = [['SellStandard', 'SS', 100.0]]

        controller = TransactionController("testTransactions.txt")
        with self.assertRaises(ValueError) as message:
            controller.processAddCredit(line, allUsers)
        self.assertEqual(str(message.exception), "Error: Credit is not a valid number.")

    # The user does not exist, and the provided credit is above 999.99
    def test_processAddCredit_Fake_User_Max(self):
        with open("testTransactions.txt", 'w') as file:
            pass
        line = "06_FakeUser________BS_999999.00\n"

        allUsers = [['SellStandard', 'SS', 100.0]]

        controller = TransactionController("testTransactions.txt")
        expectedUser = controller.processAddCredit(line, allUsers)
        
        actualUser = [['SellStandard', 'SS', 100.0]]

        self.assertEqual(expectedUser, actualUser)

        os.remove("testTransactions.txt")

        