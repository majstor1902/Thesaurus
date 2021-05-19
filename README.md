# Thesaurus

Simple thesaurus solution

Goal of this small project is to implement simple thesaurus solution according to the given API.
Created modules are:
- Database module
- Thesaurus interface module
- User application

Database module was created to split different concepts, in this case concept of storing data versus data processing and validation.
That actually means decoupling thesaurus API from database implementation.
Decoupling different concepts is based on SOLID principles, that means that each class need to have single responsibility.
For database module, adding database interface class was the first step.
In order to create interface class all possible inputs/outputs in the interface class need to be thoroughly described.
This is important because this interface will be instrumental for all possible database implementations in the future.
That should bring much faster and cleaner development.

Thesaurus interface module is the one who is publicly exposing the API towards user.
On the other hand it also communicates with the database module.

Before any implementation could be done, use cases were defined and analysed offline as the given requirements were investigated.
Based on analysis results, basic implementation was done and in parallel the tests were added.
Those tests were later used in googletest environment.
This environment later added database mock class in unit tests
Existing implementation of unit tests should alow verification of any other database implementation, separately from the API.
Modern CMake is used for much easier project creation and easier maintenance.

Limitations:
- Supported English language only
- Numeric characters used for testing purpose only
- Word size should be between MIN_WORD_LENGTH and MAX_WORD_LENGTH (currently that is between 1 and 42 characters)

Build steps:
- Go to Thesaurus root directory.
- cmake -S. -Bbuild
- cmake --build build

Built binaries are located in build/bin/ directory.
This directory contains:
- ThesaurusApp (small console application)
- ThesaurusUnitTests (unit tests)
Thesaurus core was built as a static library.
Built libraries are located in build/lib/ directory.
This directory contains:
- libThesaurusLib.a
- libgtest.a
- libgtest_main.a
- libgmock.a
- libgmock_main.a

Scripts:
Inside thesaurus root directory there is also scripts directory.
Scripts directory contains bash scripts for additional code validation.
Script for static code analysis called cppcheck.sh, it uses cppcheck.
Script for checking memory leaks called valgrind.sh.
Output from this script is file called valgrind-out.txt.
Both scripts should be called from scripts directory.

Improvements:
- Adding multi language support
- Better database implementation
- Complete unit test coverage
- Improved error handling
- Additional checks for input data validation
- Automation of unit testing (eg. using CI)
- Move to C++11 and newer versions of C++, like smart pointers...
- Consider creating dynamic library for Thesaurus, if there is a need for that
