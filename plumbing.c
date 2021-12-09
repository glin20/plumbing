#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main(){
  int piper[2];
  pipe(piper);
  int pipen[2];
  pipe(pipen);
  int test = fork();
  while(1){
    if (test){
      char buffer[512];
      fgets(buffer, sizeof(buffer), stdin);
      int i = 0;
      buffer[strlen(buffer) - 1] = '\0';
      write(piper[WRITE], buffer, strlen(buffer));
      read(pipen[READ], buffer, sizeof(buffer));
      printf("%s\n", buffer);
    }
    else{
      char buffer[512] = {'\0'};
      read(piper[READ], buffer, sizeof(buffer));
      buffer[strlen(buffer) - 1] = '\0';
      // changes all vowels into l, n, or z.
      for (int i = 0; i < strlen(buffer); i++){
        if (buffer[i] == 'a' | buffer[i] == 'i'){
          buffer[i] = 'l';
        }
        if (buffer[i] == 'e' | buffer[i] == 'u'){
          buffer[i] = 'n';
        }
        if (buffer[i] == 'u'){
          buffer[i] = 'z';
        }
      }
      write(pipen[WRITE], buffer, strlen(buffer));
    }
  }
}
