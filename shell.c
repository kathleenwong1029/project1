#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char * readline(){
  char * str = malloc(100);
  //printf("$");
  scanf(str);

  return str;
}

char ** run(char * line){
    char * arg = malloc(sizeof(line));
    strcpy(arg,line);
    char ** args = calloc(10, sizeof(line));
    int i = 0;
    while(i<10){
      printf("%s\n",args[i]);
      i++;
    }
    return args;
    //return 0;
}

int main(){
  char ** args = run(readline());

  int a = fork();
  if(!a){
    execvp(args[0],args);
  }
  else{

  }
  return 0;
}
