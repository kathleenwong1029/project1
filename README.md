# PROJECT1
By Kathleen Wong and Tiffany Zhong

## Features:
* Able to fork and execute basic commands like ls, echo, cd and exit.
* Can run and execute lines with semicolons. 
	
## Attempted:

* The following did not end up working, but have been left in the code, commented out:
* Could not get redirection to work.
* Attempted to write the code for piping, but kept on recieving "ls: wc: No such file or directory
ls: |: No such file or directory".
## Bugs:
* On occasion the exit command will act a bit wonky, but for a majority of the time it works fine. 
* When typing in one word commands, such as ls, the program will not run if you add a space to ls before you press enter. Very white space sensitive! 
	
## Files & Function Headers:

File shell.c
	
	Contains the main function and handles executing commands from the terminal line.
  
    /*======== char * readline() ==========
	  Inputs:  N/A
	  Returns: returns str
    Function: reads from standard in sets it equal to str
    ====================*/
  
    /*======== char ** parse_args() ==========
	  Inputs:  char * line
	  Returns: returns array of strings containing each command
    Function: seperates line by spaces
	  ====================*/
  
    /*======== void change_d () ==========
	  Inputs:  char * dir
	  Returns: void
    Function: changes directory to pointer given
	  ====================*/
  
    /*======== void run () ==========
	  Inputs:  char ** args
	  Returns: void
    Function: checks for exit or cd, forks and execute commands
	  ====================*/
  
    /*======== void pipey() ==========
	  Inputs: char * readend,char * writeend
	  Returns: void
    Function: redirects the output of the readend into that of the writeend and then executes the writeend
	  ====================*/
