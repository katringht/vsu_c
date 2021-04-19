#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h>

#define SUCCESS 0

int var = 0;
void *sum(void *args) {
    for (int i = 0; i < 10000; i++){
        var++;
    }
    pthread_exit(0);
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    pthread_t threads[x];
    for (int i = 0; i < x; i++) {      
        pthread_create(&threads[i], NULL, sum, NULL); 
    }
    for (int i = 0; i < x; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Result: %d\n", var);
    return SUCCESS;
}

// int var = 0;
// pthread_mutex_t lock;

// void *sum(void *args) {
//    pthread_mutex_lock(&lock); 
//     for (int i = 0; i < 10; i++){
//         printf("%li ", *((long*)args));
//         for (int j = 0; j < 10000; j++){
            
//             var++;
            
//         }
//     }
//     pthread_mutex_unlock(&lock);
// }

// int main(int argc, char *argv[]) {
//     int x = atoi(argv[1]);
//     pthread_t threads[x];

//     if (pthread_mutex_init(&lock, NULL) != 0) {
//         printf("\n mutex init failed\n");
//         return 1;
//         }

//     for (int i = 0; i < x; i++) {
//         long *k = malloc(sizeof(k));
//         *k = i;
//         pthread_create(&threads[i], NULL, sum, k); 
//     }

//     for(int i = 0; i < x; i++) { 
//         pthread_join(threads[i], NULL);
//     }   

//     pthread_mutex_destroy(&lock);

//     printf("Result: %d\n", var);
//     return SUCCESS;

// }