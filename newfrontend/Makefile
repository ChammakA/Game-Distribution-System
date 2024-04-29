#########################
# List of header paths 
#########################

# User paths
USER_HEADER_PATH = ./include/user/
ADMIN_HEADER_PATH = $(USER_HEADER_PATH)admin/
BUYSTANDARD_HEADER_PATH = $(USER_HEADER_PATH)buystandard/
FULLSTANDARD_HEADER_PATH = $(USER_HEADER_PATH)fullstandard/
SELLSTANDARD_HEADER_PATH = $(USER_HEADER_PATH)sellstandard/
ACCOUNTMANAGER_HEADER_PATH = $(USER_HEADER_PATH)accountmanager/

# Session paths
SESSION_HEADER_PATH = ./include/session/

# File paths
FILE_HEADER_PATH = ./include/file/
USER_ACCOUNTS_FILE_HEADER_PATH = $(FILE_HEADER_PATH)user_accounts/
AVAILABLE_GAMES_FILE_HEADER_PATH = $(FILE_HEADER_PATH)available_games/
GAME_COLLECTION_FILE_HEADER_PATH = $(FILE_HEADER_PATH)game_collection/
DAILY_TRANSACTION_FILE_HEADER_PATH = $(FILE_HEADER_PATH)daily_transaction/

# Game paths
GAME_HEADER_PATH = ./include/game/

# Collection paths
COLLECTION_HEADER_PATH = ./include/collection/

# Transaction paths
TRANSACTION_HEADER_PATH = ./include/transaction/

#########################
# List of header files 
#########################

# User files
HEADERS = $(USER_HEADER_PATH)user.h \
          $(ADMIN_HEADER_PATH)admin.h \
          $(BUYSTANDARD_HEADER_PATH)buy_standard.h \
          $(FULLSTANDARD_HEADER_PATH)full_standard.h \
          $(SELLSTANDARD_HEADER_PATH)sell_standard.h \
		  $(ACCOUNTMANAGER_HEADER_PATH)accountmanager.h \
		  $(SESSION_HEADER_PATH)session.h \
		  $(FILE_HEADER_PATH)file.h \
		  $(USER_ACCOUNTS_FILE_HEADER_PATH)user_accounts_file_manager.h \
		  $(AVAILABLE_GAMES_FILE_HEADER_PATH)available_games_file_manager.h \
		  $(GAME_COLLECTION_FILE_HEADER_PATH)game_collection_file_manager.h \
		  $(DAILY_TRANSACTION_FILE_HEADER_PATH)daily_transaction_file_manager.h \
		  $(GAME_HEADER_PATH)game.h \
		  $(COLLECTION_HEADER_PATH)collection.h \
		  $(TRANSACTION_HEADER_PATH)transaction.h

# List of source paths
SOURCE_PATH = ./src/

# User paths
USER_SOURCE_PATH = $(SOURCE_PATH)user/
ADMIN_SOURCE_PATH = $(USER_SOURCE_PATH)admin/
BUYSTANDARD_SOURCE_PATH = $(USER_SOURCE_PATH)buystandard/
FULLSTANDARD_SOURCE_PATH = $(USER_SOURCE_PATH)fullstandard/
SELLSTANDARD_SOURCE_PATH = $(USER_SOURCE_PATH)sellstandard/
ACCOUNTMANAGER_SOURCE_PATH = $(USER_SOURCE_PATH)accountmanager/

# Session paths
SESSION_SOURCE_PATH = $(SOURCE_PATH)session/

# File paths
FILE_SOURCE_PATH = $(SOURCE_PATH)file/
USER_ACCOUNTS_FILE_SOURCE_PATH = $(FILE_SOURCE_PATH)user_accounts/
AVAILABLE_GAMES_FILE_SOURCE_PATH = $(FILE_SOURCE_PATH)available_games/
GAME_COLLECTION_FILE_SOURCE_PATH = $(FILE_SOURCE_PATH)game_collection/
DAILY_TRANSACTION_FILE_SOURCE_PATH = $(FILE_SOURCE_PATH)daily_transaction/

# Game paths
GAME_SOURCE_PATH = $(SOURCE_PATH)game/

# Collections paths
COLLECTION_SOURCE_PATH = $(SOURCE_PATH)collection/

# Transaction paths
TRANSACTION_SOURCE_PATH = $(SOURCE_PATH)transaction/

# List of source files
SOURCE_FILES = $(USER_SOURCE_PATH)user.cpp \
			$(ADMIN_SOURCE_PATH)admin.cpp \
			$(ACCOUNTMANAGER_SOURCE_PATH)account_manager.cpp \
			$(BUYSTANDARD_SOURCE_PATH)buy_standard.cpp \
			$(FULLSTANDARD_SOURCE_PATH)full_standard.cpp \
			$(SELLSTANDARD_SOURCE_PATH)sell_standard.cpp \
			$(SESSION_SOURCE_PATH)session.cpp \
			$(USER_ACCOUNTS_FILE_SOURCE_PATH)user_accounts.cpp \
			$(AVAILABLE_GAMES_FILE_SOURCE_PATH)available_games.cpp \
			$(GAME_COLLECTION_FILE_SOURCE_PATH)game_collection.cpp \
			$(DAILY_TRANSACTION_FILE_SOURCE_PATH)daily_transaction.cpp \
			$(GAME_SOURCE_PATH)game.cpp \
			$(COLLECTION_SOURCE_PATH)collection.cpp \
			$(SOURCE_PATH)main.cpp \
			$(TRANSACTION_SOURCE_PATH)transaction.cpp
			

# List of object files
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

# List of header files
HEADER_FILES = $(HEADERS:.h=.h.gch)

# Rule to compile each source file
%.o: %.cpp
#	g++ -c $< -o $@
	g++ $(INCLUDE_PATHS) -c $< -o $@
# Rule to compile all source files
build: $(OBJECT_FILES)
	g++ $^ -o distribution-system.exe

# Rule to clean the directory
clean:
	rm -f $(OBJECT_FILES) $(HEADER_FILES) main.o distribution-system.exe

# Rule to clean and then build the program.
rebuild: clean build

.PHONY: test

test:
	chmod +x run_tests.sh
	 bash run_tests.sh $(filter-out $@,$(MAKECMDGOALS))
%:
	@:

compare:
	chmod +x compare_results.sh
	 bash compare_results.sh $(filter-out $@,$(MAKECMDGOALS))
%:
	@:

# Rule to run tests then compare the results.
run_tests:
	chmod +x run_tests.sh
	chmod +x compare_results.sh
	 bash run_tests.sh $(filter-out $@,$(MAKECMDGOALS))
	 bash compare_results.sh $(filter-out $@,$(MAKECMDGOALS))

cleaner:
	rm -fr ./testing/tests
	rm -f ./storage/daily_transactions/*
	rm -rf ./phase6_scripts/Weekly/Day1/DTFs
	rm -rf ./phase6_scripts/Weekly/Day2/DTFs
	rm -rf ./phase6_scripts/Weekly/Day3/DTFs
	rm -rf ./phase6_scripts/Weekly/Day4/DTFs
	rm -rf ./phase6_scripts/Weekly/Day5/DTFs
	rm -rf ./phase6_scripts/Weekly/week

clean_tests:
	rm -fr ./testing/tests
	rm -f ./storage/daily_transactions/*

run_script:
	chmod +x Daily.sh
	bash Daily.sh $(filter-out $@,$(MAKECMDGOALS))

