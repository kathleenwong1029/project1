#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char * readline(){
  char * str = malloc(100);
  fgets(str, 100, stdin);
  str[strlen(str)-1]=0;
  return str;
}

char ** run(char * line){
  //printf("%s\n", line);
    char * arg = malloc(sizeof(char *));
    //strcpy(arg , line);

    char ** args = calloc(10, sizeof(char*));
    int i = 0;
    while(line){
      arg = strsep(&line, " ");
      args[i]= arg;

      //printf("%s\n",args[i]);
      i++;
    }
    return args;
}

void change_d ( char * dir){
    chdir(dir);
}


int main(){
  int i =1;
  while(i){
  char * cdir = malloc(100);
  printf("%s:$",getcwd(cdir,100));

  char ** args = run(readline());

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
}
