#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//Arguments: no arguments
//Function: reads from standard in sets it equal to str
//Return value : returns str
char * readline(){
  char * str = malloc(100);
  fgets(str, 100, stdin);
  str[strlen(str)-1]=0;
  return str;
}

//Arguments: line is equal to stdin
//Function: seperates line by spaces
//Return value : returns array of strings containing each command
char ** parse_args(char * line){

    char * arg = malloc(sizeof(char *));

    char ** args = calloc(10, sizeof(char*));
    int i = 0;

    while(line){
      arg = strsep(&line, " ");
      args[i]= arg;
      i ++;
    }
    return args;
}

//Arguments: takes char pointer to requested directory change
//Function: changes directory to pointer given
//Return value : void
void change_d ( char * dir){
    chdir(dir);
}

//Arguments: array of strings containing commands
//Function: checks for exit or cd, forks and execute commands
//Return value : void
void run (char ** args){
  if(strcmp(args[0], "exit")==0){
    exit(0);
  }

  int a = fork();
  if(!a){
    if(strcmp(args[0], "cd")==0){
      change_d(args[1]);
    }
    else{
    execvp(args[0],args);
  }}
  else{
    int status;
    wait(&status);
  }
}

// void pipey(char * readend,char * writeend){
//   int pipe1[2];
//   read(pipe1[0],readend,sizeof(readend));
//   write(pipe1[1],writeend,sizeof(writeend));
//   close(fd[0]);
//   close(fd[1]);
//
// }

//Arguments: nada
//Function: if there is a semicolon, splits args into two different
//string arrays to execute
//Return value : void
int main(){
  while(1){
  char * cdir = malloc(100);
  printf("%s:$",getcwd(cdir,100));

   char ** args = parse_args(readline());
   int i =0;
   int j =0;
   int semis=0;

   char ** c1 = calloc(10, sizeof(char*));
   char ** c2 = calloc(10, sizeof(char*));

   while(args[i]){
     if (semis == 0) {
				if (strcmp(args[i], ";") == 0) {
					semis = 1;
				}
				else {
					c1[i] = args[i];
				}
			}
			if (semis == 1 && strcmp(args[i], ";") != 0) {
				c2[j] = args[i];
				j++;
			}
			i++;
   }
   run(c1);

   if(semis==1){
     run(c2);
   }

   free(args);

}
}
