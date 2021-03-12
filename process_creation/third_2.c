//Функция exec() (execute) загружает и запускает другую программу.

#include <unistd.h>
#include <stdio.h>

int main (void)
{
    printf("pid: %d\n", getpid());
    execve("/bin/third_1", NULL, NULL); // загружаем и запускаем другую программу

    return 0;
}