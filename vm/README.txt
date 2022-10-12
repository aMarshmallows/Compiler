Amasha Rajaguru
COP 3402, Fall 2022
HW1


To Compile and Run:
1. In a command line or Bash terminal, go to the directory holding the file.
2. Type "gcc vm.c" to compile.
3. Type "./a.out {input}" and replace {input} with the name of the desired input file eg : "./a.out mult.txt"
4. You may be prompted for input, in which case type a single number into the command line    following the prompt and press enter.
5. The output of the file should be printed to the terminal.

To print output to a file:
write "./a.out {input} > {output}" after compiling which will write the output to the file with the given name, else it will create a new file if that file does not exist.
eg:  "/a.out mult.txt > myoutput.txt" will create a file called myoutput.txt if it does not already exist in the directory and store the output generated from using mult.txt as an input file.
