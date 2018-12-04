#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define READ 0
#define WRITE 1
#include <fcntl.h>

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

//Arguments: two strings arrays containg args before and after >
//Function: redirects the output from char ** file 1 into newly created file
//Return value : void
void reout(char ** file1, char ** file2){
  int fd = open(file2[0], O_CREAT | O_WRONLY, 0666);
  int temp = dup(1);
  dup2(fd, WRITE);
  run(file1);
  dup2(temp, WRITE);
}

//Arguments: two strings arrays containg args before and after >
//Function: redirects the contents from char ** file 2 into commands
//Return value : void
void rein(char ** file1, char ** file2){
  int fd = open(file2[0], O_RDONLY, 0666);
  int temp = dup(0);
  dup2(fd, READ);
  run(file1);
  dup2(temp, READ);
}

//Arguments: readend(left end of pipe), writeend(right end of pipe)
//Function: redirects the output of the readend into that of the writeend
//and then executes the writeend
//Return value : void
void pipey(char * readend,char * writeend){
  char ** exe = malloc(sizeof(char*));
  exe[0] = writeend;
  int fd[2];
  pipe(fd);
  //FILE* p = popen(readend,"r");
  int out = dup(STDOUT_FILENO);
  int in = dup(STDIN_FILENO);
  int uno = fork();
  if(!uno){
    int dos = fork();
    if(!dos){
        dup2(fd[1],STDOUT_FILENO);
        close(fd[0]);
        execvp(&readend[0],&readend);
        dup2(out,STDOUT_FILENO);
    }
    else{
      wait(NULL);
      dup2(fd[0],STDIN_FILENO);
      close(fd[1]);
      execvp(&writeend[0],&writeend);
      dup2(in,STDIN_FILENO);
    }
}
  else{//parent
    wait(NULL);
  }
}

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
   int in =0;
   int out =0;
   int s =0;
   int counter = 0;
   //find size of args
   // while(args[counter]){
   //   counter ++;
   // }
   char ** c1 = calloc(10, sizeof(char*));
   char ** c2 = calloc(10, sizeof(char*));

      while(args[i]){
        if (semis == 0) {
   				if (strcmp(args[i], ";") == 0) {
   					semis = 1;
   				}
          else if (strcmp(args[i], ">") == 0) {
   				   out = 1;
             s=1;
   				}
          else if (strcmp(args[i], "<") == 0) {
   				     in= 1;
               s=1;
   				}
   				else {
   					c1[i] = args[i];
   				}
   			}
   			if ((semis == 1 && strcmp(args[i], ";") != 0) | (in == 1 && strcmp(args[i], "<") != 0) | (out == 1 && strcmp(args[i], ">") != 0)){
   				c2[j] = args[i];
   				j++;
   			}
   			i++;
      }

    // printf("%s\n",c1[0]);
    // printf("%s\n",c1[1]);
    // printf("%s\n",c1[2]);
    // printf("%s\n",c2[0]);
    // printf("%s\n",c2[1]);
    // printf("%s\n",c2[2]);

    if(out==1){
      reout(c1,c2);
    }
    else if (in==1){
      rein(c1,c2);
    }
    else{
      run(c1);
    }

    if(semis==1){
        run(c2);
    }

      free(args);

   }
   }
 //   //check for vertical bar
 // CODE DOESNT WORK OVER HERE :(
 //   char * checkpipe;
 //   const char bar = '|';
 //   for(int w = 0;w < counter; w++){
 //     checkpipe = strchr(args[w],bar);
 //     printf("%s\n",args[0]);
 //     printf("%s\n",args[1]);
 //     printf("%s\n",args[2]);
 //     printf("%d\n",counter);
 //     if (checkpipe != NULL){
 //
 //       char * left = malloc(25*sizeof(char));
 //       strcpy(left,args[0]);
 //       int q = 2;
 //
 //       while(strcmp(args[q],"|") != 0){
 //         strcat(left,args[q]);
 //         printf("%s", args[q]);
 //         q ++;
 //       }
 //       strcat(left,'\0');
 //
 //     char * right = malloc(15*sizeof(char));
 //     q++;
 //     printf("hello\n");
 //     printf("%d",q);
 //     strcpy(right,args[q]);
 //     while(args[q]){
 //       strcat(right,args[q]);
 //     }
 //     strcat(right,'\0');
 //     pipey(left,right);
 //     return 0;
 //   }
 // }
