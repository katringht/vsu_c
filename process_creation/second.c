//создаёт копии самой себя и выводит идентификатор текущего и родительского процесса (видно, что идентификаторы меняются)

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // создаем новый процесс с помощью системного вызова fork()
    if (fork() == 0) {// если код потомка
        printf("PID_child: %d\n", getpid());
    } else { // иначе код родителя
        printf("PID_parent: %d\n", getpid());
    }
	return 0;
}