// выводит идентификатор текущего и родительского процесса

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    pid_t pid, ppid;
// вызов getpid() возвращает идентификатор текущего процесса (PID), а getppid() возвращает идентификатор родителя (PPID)
    pid = getpid ();
    ppid = getppid ();
//печатаем идентификаторы
    printf ("PID: %d\n", pid);
    printf ("PPID: %d\n", ppid);
    return 0; 
} 

