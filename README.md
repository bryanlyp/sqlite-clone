# sqlite-clone
This is a database written in C++, intended to be a simplified SQLite clone to consolidate learnings from UCB's CS W186 course which I have been following online. 
SQL commands are keyed in to the program and processed in a REPL, which uses a query parser to interpret user input. 
The parsed input is then fed into the execution phase of the REPL, where the parsed SQL query is compacted/serialized into a byte string to be stored in a Table object. 
The output of the command (if any) is then fed back into the output buffer and completes an iteration of the Read-Execute-Print Loop.

This DBMS currently supports 3 commands:
- create
- select
- insert

It also supports 2 data types:
- int
- varchar (of user-specified length)

This project takes reference from [this tutorial](https://cstack.github.io/db_tutorial/). However, it does endeavour to deviate from the tutorial in the following ways (non-exhaustive):
- The database is written in C++ rather than C.
- This thus enables use of OOP principles to organize code instead of the functional programming approach used in the original project.
- The database allows a custom schema to be entered as opposed to the original project. Note that a schema is currently hard-coded for ease of testing, but all downstream operations are designed with the objective of enabling the aforementioned functionality.
- The use of C++ also enables the use of the STL and therefore greater flexibility in terms of the auxiliiry data structures used.
- As much as possible, the C++ equivalents of the various C functions are used, although for lower-level operations such as those used in the Pager object (currently not pushed to main), a more C-style approach is taken as I find them to be more intuitive at that level.


This project is currently incomplete. Specifically:
- It performs all operations in memory. A Pager object to convert data to and from the disk is in the works to rectify this and enable some data permanence.
- A B Tree is to be implemented.
- A "sort" function is to be implemented (another deviation from the original tutorial).
- Tidying up/refactoring of code is pending :)
