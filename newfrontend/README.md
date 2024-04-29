# csci3060

Ontario Tech University Software Quality Assurance course project.

## Dev

Below are instructions for development. Such as compiling and running the system.

### Compiling and running the system

The environment is compiled with makefile. If not using a system that supports makefile please switch to a system that does support makefile.

To compile code run `make build`. Then to run the code use `./main.o` (temporary) to run the executable. `make clean` will clear out all output files from the system. Please be cautious when running this. If changes were made and cause issues the makefile might fail to rebuild.

To ensure code in the `main` branch of the repository always runs, run a `make clean` and `make build` **PRIOR** to every commit. You can also do `make rebuild` to do both of these actions in one command.

Note: g++ **must** be installed on the host machine for compilation and running the system.

### Testing

**NOTE**: Make sure to do a `make build` before your first time running the test scripts and a `make rebuild` anytime a change is made to the code.

Testing is done using the shell scripts [run_tests.sh](run_tests.sh) and [compare_results.sh](compare_results.sh). The `run_tests` script generates the folders and files in `testing/tests` and the `compare_results` script actually compares the expected results to the actual ones.

Though the script files can be used directly, it is recommended to use the rules that are implemented in the makefile as follows:

`make test <transaction>`: Tests all cases for a single transaction. `all` can be used to do all test cases at once. `make compare <transaction>`: After running `make test`, use this with the same argument to check the results of the test.

**RECOMMENDED**: You can do both of these at once by doing `make run_tests <transaction>` to generate the test files and do the comparison.

Use `make clean_tests` to remove all test-generated files, including daily transaction files, if the directory becomes bigger than you want it to.

### Creating classes

When a class is created the header file will need to be added in `/include/<directory_name>/<header_file>`. And the .cpp file will be required to be added in the `/src/<base_class_name>/<class_name>.cpp`.

Once the files are added they will need to be referenced in the Makefile for compilation. The structure goes as follows:

- First, the header path will be needed. Add the path to the header file and name it `<CLASSNAME_HEADER_PATH>`.
- Next, the `HEADERS` variables will need to be updated to include the new header files. This can be done with `$(HEADER_PATH)filename.h`.
- Moving on, the source path for the cpp file will need to be created. Add a source path such as the following `<CLASSNAME_SOURCE_PATH>`.
- Finally, the `SOURCE_FILES` variable will need to be updated. This can be done with `$(SOURCE_PATH)classname.cpp`.

Use `make clean` to clear out the old files and `make build` to compile the new additions. If there is an error in compilation ensure the syntax is all properly defined.

### Naming Conventions

Please adhere to the standard programming practices for naming conventions.

- Snake Case when creating functions and methods. e.g. `my_function`.
- Pascal for class names. e.g. `MyClass`.
- Camel case for variable names. e.g. `myVariable`.

### Adding a Transaction

Take the following steps to add a new type of transaction to the system:

- Add a new member to the `TransactionCode` enum in [transaction.h](include/transaction/transaction.h)
- Add a new private static function declaration inside `Transaction` class in [transaction.h](include/transaction/transaction.h)
- Add an entry to the `transactionCodeMap` for the transaction in [transaction.cpp](src/transaction/transaction.cpp)
- Add an entry to the `transactionFunctions` map for the transaction in [transaction.cpp](src/transaction/transaction.cpp)
- Implement the function in [transaction.cpp](src/transaction/transaction.cpp)

## System

Below are high level details of the system for dev and client reference.

### Creating Users

Creating users is a privileged transaction, therefore, only admins can create users. For the purpose of the dev process there is an initial admin account created with just the plain username `admin`. Please use this account to create subsequent users, admin or otherwise, to test functionality.
