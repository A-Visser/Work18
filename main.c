#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define READ 0
#define WRITE 1
int main(){
  int strsize = 50;
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    int f = fork();
    while(1){
      if(f){
        //parent
        char line[strsize];
        printf("input string: \n");
        fgets(line, strsize, stdin);
        close(pipe1[READ]);
        write(pipe1[WRITE], line, strsize);
        close(pipe2[WRITE]);
        read(pipe2[READ], line, strsize);
        printf("output: %s\n", line);

      } else {
        //child
        char line[strsize];
        close(pipe1[WRITE]);
        read(pipe1[READ], line, strsize);
        int i;
        for(i = 0; i < strlen(line); i++){
          line[i] = toupper(line[i]);
        }
        close(pipe2[READ]);
        write(pipe2[WRITE], line, strsize);
      }
    }
  return 0;
}
