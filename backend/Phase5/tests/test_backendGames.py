
import unittest
import os
from backend.backendGames import GameCollectionController

class TestGameCollectionController(unittest.TestCase):
    def test_getOwnedGames_Valid(self):
        with open('testOwnedGames.txt', 'w') as file:
            file.write("Owned_Game________________Admin__________\n")
            file.write("END______________________________________\n")
            file.write("Owned_Game2_______________Admin__________\n")

        controller = GameCollectionController("testOwnedGames.txt")
        ownedGames = controller.getOwnedGames()

        self.assertEqual(ownedGames, [['Owned Game', 'Admin']])
        os.remove("testOwnedGames.txt")
    def test_NonExistent_File(self):
        controller = GameCollectionController("Random.txt")
        with self.assertRaises(FileNotFoundError) as message:
            controller.getOwnedGames()
        self.assertEqual(str(message.exception), "[Errno 2] No such file or directory: 'Random.txt'")
    
    def test_Invalid_File_Format(self):
        with open('testOwnedGames.txt', 'w') as file:
            file.write("Owned_Game________________Admin________33__\n")


        controller = GameCollectionController("testOwnedGames.txt")
        with self.assertRaises(ValueError) as message:
            controller.getOwnedGames()
        self.assertTrue("Error: Incorrect format in file." in str(message.exception))

        os.remove("testOwnedGames.txt")