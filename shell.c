#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char * readline(){
  char * str = malloc(100);
  fgets(str, sizeof(str), stdin);
  str[strlen(str)-1]=0;
  //printf("%s", str);
  return str;
}

char ** run(char * line){
    char * arg = malloc(sizeof(line));
    //strcpy(arg , line);

    char ** args = calloc(10, sizeof(line));
    int i = 0;
    while(line){
      arg = strsep(&line, " ");
      args[i]= arg;

      printf("%s\n",args[i]);
      i++;
    }
    return args;
    //return 0;
}

void cd( char * dir){
  int d = chdir(dir);
}

int main(){
  char ** args = run(readline());

  int a = fork();
  if(!a){
    if(!strcmp(args[0], "cd")){
      chdir(args[1]);
    }
    execvp(args[0],args);
    }
  else{
    int status;
    wait(&status);
  }

  return 0;
}
