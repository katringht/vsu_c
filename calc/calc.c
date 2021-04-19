// Взаимодействие процессов (очередь сообщений)

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

//функция с операциями
double operations(double x, double y, char operation)
{
  double res;
  switch (operation)
  {
  case '+':
  {
    res = x + y;
    break;
  }
  case '-':
  {
    res = x - y;
    break;
  }
  case '/':
  {
    if (y != 0)
      res = x / y;
    else
      res = 0;
    break;
  }
  case '*':
  {
    res = x * y;
    break;
  }
  }
  return res;
}

struct message
{
  long mtype;
  double x, y;
  char operation;
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
    double x, y;
    char operation;
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
    (void)strcpy(&(msg.operation), &operation);

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

    printf("%.2lf %c %.2lf = %.2lf\n", msg.x, msg.operation, msg.y, operations(msg.x, msg.y, msg.operation));
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
      perror("msgctl");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}