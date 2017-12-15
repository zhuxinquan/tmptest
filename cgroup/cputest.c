/*************************************************************************
> File Name: cputest.c
> Author: zhuxinquan
> Mail: zhuxinquan61@gmail.com
> Created Time: 2017年12月07日 星期四 20时10分16秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define NUM 48
#define START 100010001
#define END 100020000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int count = 0;

void *prime(void *p)
{
    int n, i, flag;

    while (1) {
        if (pthread_mutex_lock(&mutex) != 0) {
            perror("pthread_mutex_lock()");
            pthread_exit(NULL);

        }
        while (count == 0) {
            if (pthread_cond_wait(&cond, &mutex) != 0) {
                perror("pthread_cond_wait()");
                pthread_exit(NULL);

            }

        }
        if (count == -1) {
            if (pthread_mutex_unlock(&mutex) != 0) {
                perror("pthread_mutex_unlock()");
                pthread_exit(NULL);
            }
            break;
        }
        n = count;
        count = 0;
        if (pthread_cond_broadcast(&cond) != 0) {
            perror("pthread_cond_broadcast()");
            pthread_exit(NULL);
        }
        if (pthread_mutex_unlock(&mutex) != 0) {
            perror("pthread_mutex_unlock()");
            pthread_exit(NULL);
        }
        flag = 1;
        for (i=2;i<n/2;i++) {
            if (n%i == 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            printf("%d is a prime form %d!\n", n, pthread_self());
        }
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid[NUM];
    int ret, i;

    for (i=0;i<NUM;i++) {
        ret = pthread_create(&tid[i], NULL, prime, NULL);
        if (ret != 0) {
            perror("pthread_create()");
            exit(1);
        }
    }

    for (i=START;i<END;i+=2) {
        if (pthread_mutex_lock(&mutex) != 0) {
            perror("pthread_mutex_lock()");
            pthread_exit(NULL);
        }
        while (count != 0) {
            if (pthread_cond_wait(&cond, &mutex) != 0) {
                perror("pthread_cond_wait()");
                pthread_exit(NULL);
            }
        }
        count = i;
        if (pthread_cond_broadcast(&cond) != 0) {
            perror("pthread_cond_broadcast()");
            pthread_exit(NULL);
        }
        if (pthread_mutex_unlock(&mutex) != 0) {
            perror("pthread_mutex_unlock()");
            pthread_exit(NULL);
        }
    }

    if (pthread_mutex_lock(&mutex) != 0) {
        perror("pthread_mutex_lock()");
        pthread_exit(NULL);
    }
    while (count != 0) {
        if (pthread_cond_wait(&cond, &mutex) != 0) {
            perror("pthread_cond_wait()");
            pthread_exit(NULL);
        }
    }
    count = -1;
    if (pthread_cond_broadcast(&cond) != 0) {
        perror("pthread_cond_broadcast()");
        pthread_exit(NULL);
    }
    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("pthread_mutex_unlock()");
        pthread_exit(NULL);
    }
for (i=0;i<NUM;i++) {
    ret = pthread_join(tid[i], NULL);
    if (ret != 0) {
        perror("pthread_join()");
        exit(1);
    }
}
exit(0);
}
