# CS 149 - Assignment 2
 
## Students
 
- Ebsan Iqbal
- Raymond Okolo
## Description
 
This assignment extends our Assignment 1 `countnames` program to use multiple processes.
 
The `shell` program is an interactive, prompt-based shell. It prints the prompt `% ` and reads a command line typed by the user, such as:
 
```text
% ./countnames test/names1.txt test/names2.txt
```
 
The first token is the program to run (`./countnames`) and every token after it is an input file. The shell creates one child process for each input file using `fork()`. Each child process then runs `countnames` on its file using `exec()`. The child processes execute independently and in parallel. After creating the children, the parent process waits for all of them to finish, reports whether each child terminated normally or by a signal, and then prints the prompt again. The shell ends when the user types `exit` or presses Ctrl+D (end of input).
 
Each `countnames` process counts the names in one input file and writes the results to a file named:
 
```text
PID.out
```
 
where `PID` is that child process's process ID.
 
If an input file contains an empty line, the warning is written to:
 
```text
PID.err
```
 
If no filename is typed after `./countnames`, the child reads names from standard input instead.
 
---
 
## Compilation
 
Compile both programs from the project directory:
 
```bash
gcc -o countnames countnames.c -Wall -Werror
gcc -o shell shell.c -Wall -Werror
```
 
Both commands should compile without errors or warnings.
 
---
 
## Running the Program
 
Start the shell:
 
```bash
./shell
```
 
Then type commands at the `%` prompt. Type `exit` (or press Ctrl+D) to leave the shell.
 
### One input file
 
```text
% ./countnames test/names1.txt
```
 
The parent prints a message similar to:
 
```text
Child <PID> terminated normally with exit code: 0
```
 
The child creates:
 
```text
<PID>.out
<PID>.err
```
 
The exact PID changes each time the program is run.
 
### Multiple input files
 
```text
% ./countnames test/names1.txt test/names2.txt
```
 
Two child processes are created. The terminal should show two successful child termination messages, and two separate sets of PID output/error files should be created.
 
### Standard input
 
```text
% ./countnames
```
 
One child process reads names from standard input. Type the names, one per line, then press Ctrl+D on an empty line to end that child's input. The child creates its own `PID.out` and `PID.err` files, and the shell prompt returns.
 
Because the shell reads its own commands from standard input, piping a file into `./shell` would make the shell treat each name as a command. To test piped input, use `countnames` directly (see Additional Validation).
 
---
 
# Provided Test Cases
 
Start the shell with `./shell` and run each command at the `%` prompt.
 
## Test 1 - names1.txt
 
Run:
 
```text
% ./countnames test/names1.txt
```
 
Expected `PID.out`:
 
```text
Tom Wu: 3
```
 
Expected `PID.err`:
 
```text
Warning - file test/names1.txt line 3 is empty.
```
 
Purpose:
 
This test checks repeated names and verifies that an empty line is ignored for counting and written as a warning to the error file.
 
---
 
## Test 2 - names2.txt
 
Run:
 
```text
% ./countnames test/names2.txt
```
 
Expected `PID.out`:
 
```text
Jenn Xu: 2
Tom Wu: 1
```
 
Expected `PID.err`:
 
```text
(empty)
```
 
Purpose:
 
This test checks that multiple different names are counted correctly and that repeated names receive the correct count.
 
---
 
## Test 3 - names.txt
 
Run:
 
```text
% ./countnames test/names.txt
```
 
Expected `PID.out`:
 
```text
Nicky: 1
Dave Joe: 2
Yuan Cheng Chang: 3
John Smith: 1
```
 
Expected `PID.err`:
 
```text
Warning - file test/names.txt line 2 is empty.
Warning - file test/names.txt line 5 is empty.
```
 
Purpose:
 
This test checks names containing spaces, repeated names, multiple empty lines, and correct empty-line numbers.
 
---
 
## Test 4 - namesB.txt
 
Run:
 
```text
% ./countnames test/namesB.txt
```
 
Expected `PID.out`:
 
```text
Nicky: 1
Dave Joe: 2
Yuan Cheng Chang: 3
John Smith: 1
```
 
Expected `PID.err`:
 
```text
Warning - file test/namesB.txt line 2 is empty.
Warning - file test/namesB.txt line 5 is empty.
```
 
Purpose:
 
This test provides another supplied input containing duplicate names, names with spaces, and empty lines.
 
---
 
## Test 5 - names_long.txt
 
Run:
 
```text
% ./countnames test/names_long.txt
```
 
Expected behavior:
 
- The child should terminate normally with exit code `0`.
- A `PID.out` file should be created containing all name counts.
- No empty-line warnings are expected in `PID.err`.
- The program must successfully process the entire file rather than being limited by the total number of input lines.
Important checks from `PID.out` include:
 
```text
MARY SMITH: 1
 : 99
PATRICIA JOHNSON: 1
...
ROBIN HAYES: 1
```
 
Purpose:
 
This test checks processing of a large input file and verifies that the program is not limited by the total number of lines.
 
---
 
## Test 6 - names_long_redundant.txt
 
Run:
 
```text
% ./countnames test/names_long_redundant.txt
```
 
Expected behavior:
 
- The child should terminate normally with exit code `0`.
- `PID.out` should contain the name counts for the complete file.
- Repeated names should have counts greater than 1 where appropriate.
Examples include:
 
```text
Avery Taylor: 2
Andrew Lee: 2
Nathan Davis: 2
Jonathan Lee: 2
Avery Adams: 2
```
 
Expected `PID.err`:
 
```text
Warning - file test/names_long_redundant.txt line 97 is empty.
```
 
Purpose:
 
This test checks a larger input with many names, duplicate names, and an empty line.
 
---
 
## Test 7 - names_long_redundant1.txt
 
Run:
 
```text
% ./countnames test/names_long_redundant1.txt
```
 
Expected behavior:
 
- The child should terminate normally with exit code `0`.
- The valid names should appear in `PID.out`.
Expected `PID.err`:
 
```text
Warning - file test/names_long_redundant1.txt line 2 is empty.
Warning - file test/names_long_redundant1.txt line 4 is empty.
Warning - file test/names_long_redundant1.txt line 6 is empty.
Warning - file test/names_long_redundant1.txt line 8 is empty.
```
 
Purpose:
 
This test checks correct handling and reporting of several empty lines within a larger file.
 
---
 
## Test 8 - names_long_redundant2.txt
 
Run:
 
```text
% ./countnames test/names_long_redundant2.txt
```
 
Expected behavior:
 
- The child should terminate normally with exit code `0`.
- A `PID.out` file should contain the counts from the entire input.
- No empty-line warnings are expected.
Example output includes:
 
```text
STEPHANIE MITCHELL: 1
CAROLYN PEREZ: 1
...
SARA A PERRY: 1
```
 
Purpose:
 
This test checks another larger set of valid names and confirms that normal files without empty lines produce no warning messages.
 
---
 
## Test 9 - names_long_redundant3.txt
 
Run:
 
```text
% ./countnames test/names_long_redundant3.txt
```
 
Expected behavior:
 
- The child should terminate normally with exit code `0`.
- Repeated names should have the correct counts.
Examples include:
 
```text
MARY SMITH: 2
PATRICIA JOHNSON: 2
LINDA WILLIAMS: 2
BARBARA JONES: 2
ELIZABETH BROWN: 2
```
 
No empty-line warnings are expected.
 
Purpose:
 
This test checks correct counting when several names are repeated in a larger file.
 
---
 
# Our Test Case
 
Create the file:
 
```text
test/mytestA2.txt
```
 
with:
 
```text
Alice
Bob
Alice
Charlie
Bob
Alice
```
 
Run the same file twice in one command:
 
```text
% ./countnames test/mytestA2.txt test/mytestA2.txt
```
 
Expected terminal behavior:
 
```text
Child <PID1> terminated normally with exit code: 0
Child <PID2> terminated normally with exit code: 0
```
 
The order of the child messages and the PID values may vary.
 
Two different `PID.out` files should be created. Each should contain:
 
```text
Alice: 3
Bob: 2
Charlie: 1
```
 
Purpose:
 
This test checks the Assignment 2 requirement that if the same filename appears multiple times on the command line, it is processed multiple times by separate child processes. It also verifies that the child processes produce separate output files.
 
---
 
# Additional Validation
 
## Multiple different files at the same time
 
Run:
 
```text
% ./countnames test/names1.txt test/names2.txt
```
 
Expected behavior:
 
Two child processes should terminate normally with exit code `0`. Each child should have a different PID and should create its own `PID.out` and `PID.err` files.
 
Purpose:
 
This verifies that the shell creates separate child processes for multiple input files before waiting for the children to finish.
 
---
 
## Standard input
 
Run:
 
```text
% ./countnames
```
 
Then type the following lines and press Ctrl+D on an empty line:
 
```text
Jenn Xu
Tom Wu
Jenn Xu
```
 
Expected output file contents:
 
```text
Jenn Xu: 2
Tom Wu: 1
```
 
Purpose:
 
This verifies that the child process reads standard input when no filename is given after `./countnames`.
 
We also tested `countnames` directly with piped standard input, outside the shell:
 
```bash
cat test/names2.txt | ./countnames
```
 
The program should create a PID-based output file containing:
 
```text
Jenn Xu: 2
Tom Wu: 1
```
 
Purpose:
 
This verifies the required no-filename behavior for `countnames`.
 
---
 
## Invalid filename
 
Run:
 
```text
% ./countnames test/does_not_exist.txt
```
 
Expected error:
 
```text
error: cannot open file test/does_not_exist.txt
```
 
The parent should report that the child terminated with exit code `1`.
 
Purpose:
 
This test checks file-open error handling and verifies that a failed child returns the required error status.
 
---
 
## Exiting the shell
 
At the prompt, type:
 
```text
% exit
```
 
or press Ctrl+D on an empty line. The shell should end without errors. A blank line should simply print the prompt again.
 
Purpose:
 
This verifies that the shell loops until the user ends it.
 
---
 
# Lessons learned
 
In this assignment, we learned how multiple processes can be created with `fork()` and how each child process receives its own process ID. We also learned how `exec()` can replace a child process with another program and how a parent process can use `wait()` to collect completed children.
 
We learned how to build a simple interactive shell: print a prompt, read a line, split it into a command and its arguments, and loop until the user exits. We also learned why all child processes should be created before the parent begins waiting, so that a slower input file does not prevent other children from starting. This demonstrated how independent processes can execute in parallel.
 
We also learned how exit codes and signals can be inspected after a child terminated. In addition, we practiced writing results to separate files based on each process ID and handling standard input and file-open errors.
 
---
 
# References
 
1. SJSU CS 149 Assignment 2 instructions and course process/system-call materials.
2. zyBooks CS 149 C programming exercises and zyLabs.
3. Course examples and slides covering `fork()`, `wait()`, `exec()`, process IDs, exit codes, and signals.
4. OpenAI ChatGPT - used for clarification, debugging, final code review, testing guidance, and README preparation.  
   Public chat link: **https://chatgpt.com/share/6ab4654f-f544-83ed-8f2e-651e83d9a1ee**
---
 
# Acknowledgements
 
We would like to acknowledge the CS 149 course materials, lectures, slides, zyBooks exercises, and provided sample programs for helping us understand processes and system calls.
