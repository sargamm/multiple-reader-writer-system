#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 1

struct element{
    int data;
    struct element *link;
    pthread_mutex_t lock;
};
pthread_mutex_t writerLock;
// pthread_mutex_t DQueuelock;
struct element* QFront=NULL;
struct element* QRear=NULL;

void *insert(){
    pthread_mutex_lock(&(writerLock));
    sleep(3);
    struct element *newE=(struct element*)malloc(sizeof(struct element));
    newE->data=rand()%50;
    newE->link=NULL;
    pthread_mutex_init(&(newE->lock),NULL);
    if(QRear==NULL){
        QRear=newE;
        QFront=newE;
    }
    else{
        QRear->link=newE;
    }
    pthread_mutex_unlock(&(writerLock));
}
void *dequeue(){
    pthread_mutex_lock(&(QFront->lock));
    sleep(3);
    if(QFront==NULL){
        printf("%s\n","No element in queue");
    }
    else if(QFront==QRear){
        QFront=NULL;
        QRear=NULL;
    }
    else{
        QFront=QFront->link;
    }
    pthread_mutex_unlock(&(QFront->lock));
}
void *Read(){
    int k=rand()%5;
    struct element* ptr;
    ptr=QFront;
    int i=1;
    while(ptr!=NULL && i<k){
        ptr=ptr->link;
        i++;
    } 
    if(ptr!=NULL){
        pthread_mutex_lock(&(ptr->lock));
        sleep(5);
        printf("%d\n",ptr->data);
        pthread_mutex_unlock(&(ptr->lock));
    }
    else{
        printf("%s\n","this index is unavailable");
    }    
}
void *print(){
    struct element* ptr;
    ptr=QFront;
    while(ptr!=NULL){
        pthread_mutex_lock(&(ptr->lock));
        sleep(5);
        printf("%d ",ptr->data);
        ptr=ptr->link;
        pthread_mutex_unlock(&(ptr->lock));
    } 
    printf("\n");
}
void *update(){
    pthread_mutex_lock(&(writerLock));
    int k=rand()%50;
    struct element *ptr,*prev;
    ptr=QFront;
    int i=1;
    while(ptr!=NULL && i<k){
        prev=ptr;
        ptr=ptr->link;
        i++;
    } 
    int d=rand()%5+1;
    if(i==k){
        pthread_mutex_lock(&(ptr->lock));
        sleep(7);
        ptr->data=d;
        pthread_mutex_unlock(&(ptr->lock));
    }
    else
    {
       printf("%s\n","position does not exist");
    }
    pthread_mutex_unlock(&(writerLock));
}
void main(){
    printf("Hey");
    if (pthread_mutex_init(&(writerLock),NULL)!=0) {
        perror("pthread_mutext_init");
        exit(1);
    }
    //print();
    if(DEBUG)   printf("Init done (chaos)!!");
    for(int i=0;i<5;i++){
        insert();
    }
    if(DEBUG==0)
        print();
    if(DEBUG)   printf("Init done (lel)!!");
    pthread_t thread[11];
    for(int i=0;i<7;i+=2){
        pthread_create(&(thread[i]),NULL,(void*)Read,NULL);
        //pthread_create(&(thread[i+1]),NULL,(void*)print,NULL);
    }
    if(DEBUG)   printf("Init done (partial)!!");
    pthread_create(&(thread[8]),NULL,(void*)insert,NULL);
    pthread_create(&(thread[9]),NULL,(void*)update,NULL);
    pthread_create(&(thread[10]),NULL,(void*)dequeue,NULL);
    for(int i=0;i<11;i++){
        pthread_join((thread[i]),NULL);
    }
    if(DEBUG)   printf("Init done !!");
}