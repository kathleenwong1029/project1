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
    int semi = 0;
    while(line){
      // if(strstr(line,";")==0){
      //   semi +=1;
      // }
      args[i]= strsep(&line, ";");
    //  printf("%s\n",args[i]);
    //  printf("%d\n",i);
      i ++;
    }
    i = 0;
    printf("%s\n",args[0]);
    printf("%s\n",args[1]);

    //printf("%s\n",line1);
    // while(args[i]){
    //   arg = strsep(args, " ");
    //   args[i]= arg;
    //   //printf("%s\n",args[i]);
    //   i++;
    // }
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

// void pipey(char * readend,char * writeend){
//   int pipe1[2];
//   read(pipe1[0],readend,sizeof(readend));
//   write(pipe1[1],writeend,sizeof(writeend));
//   close(fd[0]);
//   close(fd[1]);
//
// }

int main(){
  while(1){
  char * cdir = malloc(100);
  printf("%s:$",getcwd(cdir,100));

  char ** args = parse_args(readline());
   int i,j, semi= 0;

   char ** c1 = malloc(10 * sizeof(char*));
   char ** c2 = calloc(10, sizeof(char*));

   while(args[i]){

    c1[i]= strsep(&args[i], " ");
    i++;
  }

  int copy ;
  for(copy = 0 ; copy < j ;copy ++){
    printf("%s\n", "b");
    strcpy(c1[copy],args[copy]);
    printf("%s\n",c1[copy]);
  }
  for(copy = j + 1 ; copy < sizeof(args) ;copy ++){
    strcpy(c2[copy],args[copy]);
  }
  if(semi){
    run(c1);
    run(c2);
  }

}
}
