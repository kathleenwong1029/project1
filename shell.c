#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int semi = 0;

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
      arg = strsep(&line, ";");
      args[i]= arg;
    //  printf("%s\n",args[i]);
    //  printf("%d\n",i);
      i ++;
    }
    //i = 0;
    // printf("%s\n",args[0]);
    // printf("%s\n",args[1]);

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
   int i= 0;

   char * line1 = malloc(100);
   char * line2 = malloc(100);
   strcpy(line1,args[0]);
   strcpy(line2,args[1]);

   char ** c1 = malloc(10 * sizeof(char*));
   char ** c2 = malloc(10 * sizeof(char*));

   printf("%s\n",args[0]);
   printf("%s\n",args[1]);
   while(line1){
    c1[i]= strsep(&line1, " ");
    i++;
  }
    c1[i-1]= NULL;
    // printf("%s\n",c1[0]);
    // printf("%s\n",c1[1]);
    // printf("%s\n",c1[2]);
    i =0;
    while(line2){
     c2[i-1]= strsep(&line2, " ");
     i++;
   }
   printf("%s\n",c2[0]);
   printf("%s\n",c2[1]);
   printf("%s\n",c2[2]);


  // if(semi){
     run(c1);
     run(c2);
     free(c1);
     free(c2);
     free(args);
  // }
  // else{
  //   run(args);
  // }

}
}
