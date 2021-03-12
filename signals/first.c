// бесконечно выводит заранее заданную строку на экран и ожидает сигналов SIGUSR1 и SIGUSR2. При получении каждого из сигналов она меняет выводимую строку.

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

char str[50] = "Z Z Z...\n"; 

// SIGUSR1 and SIGUSR2 signal handler
void sigprocess (int sign){
 switch (sign)
  {
  case SIGUSR1:
    printf("SIGUSR1 processed\n");
    break;
  case SIGUSR2:
    printf("SIGUSR2 processed\n");
    break;
  }
}

int main(){
    // register signal handler
    // the signal() will call the sigprocess() function if the process receives a signal num. 
    signal (SIGUSR1, sigprocess);
    signal (SIGUSR2, sigprocess);
    printf("PID: %d\nWait signal:\n", getpid());
    for(int i=1;;i++){ // infinite loop
    printf("%s", str);
    sleep(1);
  }
}

//gcc first.c -o r && ./r