//отправляет другому процессу сигнал SIGUSR1 или SIGUSR2 (в зависимости от параметра в командной строке). Процесс, которому нужно отправить сигнал выбирается по его идентификатору.

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int id;

int main(int argc, char *argv[])
{
  if (argc !=2){
    if ((strcmp(argv[2], "SIGUSR1") == 0) || (strcmp(argv[2], "SIGUSR2") == 0)){ // check signal
      int pid = atoi(argv[1]);
      if ((strcmp(argv[2], "SIGUSR1") == 0)){
        id = 30; //User-defined signal 1
      }
      else{
        id = 31;//User-defined signal 2
      }
      // sending a signal. it is necessary that the uid of the current process be 0 or the same as the uid of the recipient process.
      kill(pid, id); printf("Signal sended.\n");
    }
    else{
      printf("Error.\n");
    }
  }
}

//gcc second.c -o e && ./e <PID> <SIGNAL>