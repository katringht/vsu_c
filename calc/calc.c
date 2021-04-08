// Взаимодействие процессов (очередь сообщений)

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

//функция с операциями 
float operations(float x, float y, char operation)
{
  float res;
  switch (operation) {
  case '+': {
    res = x + y;
    break;
  }
  case '-': {
    res = x - y;
    break;
  }
  case '/': {
    if (y != 0)
      res = x / y;
    else
      res = 0;
    break;
  }
  case '*': {
    res = x * y;
    break;
  }
  case '^': {
    res = 1;
    for (int i = 0; i < y; i++)
      res = res * x; 
    break;
  }
  case '!': {
    res = 1;
    if (y >= 0)
      for (int i = y; i != 1; i--)
        res = res * i;
    else
      res = 0;
    break;
  }
  }
  return res;
}

struct message{
  long mtype;
  float x, y;
  char oper;
};

int main(void)
{
  //создание очереди
  int msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
  if (msqid == -1)
  {
    perror("msgget");

    return EXIT_FAILURE;
  }
//создание процесса
  pid_t pid = fork();
  if (pid == 0)
  {
    float x, y;
    char oper
    struct msg msg;
    msg.mtype = 23;
    memset(&(msg.x), 0, sizeof(double));
    memset(&(msg.y), 0, sizeof(double));
    memset(&(msg.operation), 0, sizeof(char));

    printf("First number: ");
    scanf("%lf", &(msg.x));

    printf("Second number: ");
    scanf("%lf", &(msg.y));

    printf("Operation: ");
    scanf(" %c", &oper);
    (void)strcpy(&(msg.oper), &oper);

//отправка
    if (msgsnd(msqid, &msg, sizeof(struct msg), 0) == -1)
    {
      perror("msgsnd");

      return EXIT_FAILURE;
    }
  }
  else
  {
    (void)waitpid(pid, NULL, 0);
    //получаем сообщение из очереди 
    struct msg msg;
    if (msgrcv(msqid, &msg, sizeof(struct msg), 0, 0) == -1)
    {
      perror("msgrcv");

      return EXIT_FAILURE;
    }

    printf("%.2lf %c %.2lf = %.2lf\n", msg.x, msg.oper, msg.y, operations(msg.x, msg.y, msg.oper));
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
      perror("msgctl");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}