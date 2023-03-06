# System-Wide-FD-Tables 📁

NOTE: The actual function descriptions are provided within the source code.

## GENERAL OVERVIEW:

This project was approached in a very modular structure where smaller functions serve as building blocks for bigger ones.
I was able to break things down into two classes of functions, low-level and high-level. Note that these functions are
split into two files (DataCollection.c, Output.c) where the first takes care of collecting all the processes and the second
deals with outputting the desired information. Note that we also have a datacollection.h file that defines the process struct as
well as provides function signatures.

Below is a list of each category and how the pieces interconnect.

## datacollection.h:

1. typedef struct process // provides the definiton of the process data structure(low-level)
2. size_t getProcesses(process \*\*processes) // defines the function signature(low-level)

## DataCollection.c:

1. getProcesses(process \*\*processes) // implements this function defined in datacollection.h which is responsible for gathering all the process info(low-level)

## Output.c:

1. pidExists(process \*\*processes, size_t count, long int pid) // checks if pid is an existing pid(low-level)
2. getCompositeTable(process \*\*processes, size_t count, long int pid) // prints composite table(low-level)
3. getPerProcess(process \*\*processes, size_t count, long int pid) // prints per-process table(low-level)
4. getSystemWide(process \*\*processes, size_t count, long int pid) // prints system wide FD table(low-level)
5. getVnodes(process \*\*processes, size_t count, long int pid) // prints vnodes table(low-level)
6. pidAccounted(long int pids[], size_t count, long int pid) // helper function to check if pid exists in given array(low-level)
7. getOffending(process \*\*processes, size_t count, long int threshhold) // prints offending processes(low-level)
8. outputText(process \*\*processes, size_t count, long int pid) // prints composite table in text file(low-level)
9. outputBinary(process \*\*processes, size_t count, long int pid) //prints composite table in binary file(low-level)
10. parseArguments(int argc, char *argv[], bool *system, bool *user, bool *sequential, int *samples, int *tdelay) // parses command line arguments passed
11. validateArguments(int argc, char \*argv[]) // validates the command line arguments passed

Notice that all these functions are responsible for getting the information and each has a singular responsibility.

10. navigate(int argc, char \*argv[]) //navigates to needed output given the command line arguments(high-level)

## HOW TO RUN

The program also provides a makefile titles 'makefile' which provides the necessary rules to compile the program

RUN THE FOLLOWING COMMANDS IN SEQUENCE:
<br /> `make`
<br /> `./fdTables [insert flags or positional args here]`

Note: You can run "make clean" to erase all the .o files produced from the compilation process or use "make cleanText" or "make cleanBinary" to delete the text and binary files produced.

THE ARGUMENT OPTIONS INCLUDE:

1. --composite (prints composite table)
2. --per-process (prints per-process table)
3. --systemWide (prints system wide FD table)
4. --Vnodes (prints vnodes table)
5. --threshold=X (prints offending processes)
6. You can also print the tables for a particular pid by inputting it as an arguments (ex ./fdTables 12345)

NOTE: Calling the program with no arguments will deafult to printing the per-process, system wide, vnodes, and composite table for all the user owned processes. Additionally we assume that threshold operates independantly from the pid positional flag (this means that threshold will search all processes even if a particular process is inputted as a CLA).

FOR FURTHER INFORMATION ON EACH FUNCTION'S ROLE AND DESCRIPTION PLEASE REFER TO THE SOURCE CODE FILES.
