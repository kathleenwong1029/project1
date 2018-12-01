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

char ** parse_args(char * line){
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


int main(){
  while(1){
  char * cdir = malloc(100);
  printf("%s:$",getcwd(cdir,100));

  char ** args = parse_args(readline());
   int i,j, semi= 0;

   char ** c1 = (char **)calloc(10, sizeof(char*));
   char ** c2 = (char **)calloc(10, sizeof(char*));

   while(args[i]){
    if(strstr(args[i],";")){
      semi +=1;
      j = i;
      printf("%d\n",j);
    }
    i++;
  }
  int copy ;
  for(copy = 0 ; copy < j ;copy ++){
    printf("%s\n", args[copy]);
    strcpy(c1[copy],args[copy]);
    printf("%s\n",c1[copy]);
  }
  // for(copy = j + 1 ; copy < sizeof(args) ;copy ++){
  //   strcpy(c2[copy],args[copy]);
  // }
  // if(semi){
  //   run(c1);
  //   run(c2);
  // }
  // else{
  //   run(args);
  // }
  run(args);
}
}
