#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
pthread_t main_tid;
pthread_t main_tid1;
pthread_t main_tid2;
pthread_t main_tid3;

void *func(void *arg)
{
    while(1){
      printf("1");
    }
    return ((void *)0);
}
int main()
{
    int err;
    err = pthread_create(&main_tid, NULL, func, NULL); //创建线程
    err = pthread_create(&main_tid1, NULL, func, NULL); //创建线程
    err = pthread_create(&main_tid2, NULL, func, NULL); //创建线程
    err = pthread_create(&main_tid3, NULL, func, NULL); //创建线程
    while(1);
    return 0;
}
