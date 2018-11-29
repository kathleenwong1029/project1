#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char * readline(){
  char * str = malloc(100);
  fgets(str, 100, stdin);
  str[strlen(str)-1]=0;
  printf("%s", str);
  return str;
}

char ** run(char * line){
  printf("%s", line);
    char * arg = malloc(sizeof(char *));
    //strcpy(arg , line);

    char ** args = calloc(10, sizeof(char*));
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

void change_d ( char * dir){
  int b = fork();
  if (!b){
    chdir(dir);
  }
  else{
    int status;
    wait(&status);
  }
  return;
}


int main(){
  while(1){
  char * cdir = malloc(100);
  printf("%s:$",getcwd(cdir,100));

  char ** args = run(readline());

  if(strcmp(args[0], "cd")){
    change_d(args[1]);
  }

  int a = fork();
  if(!a){
    execvp(args[0],args);
    }
  else{
    int status;
    wait(&status);
  }

}
}
