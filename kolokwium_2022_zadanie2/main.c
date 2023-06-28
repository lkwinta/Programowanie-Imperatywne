#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double* results;
    int len;
} Data;

typedef struct tagQueueElement{
    Data data;
    struct tagQueueElement* next;
} QueueElement;

typedef struct tagQueue {
    QueueElement* head;
    QueueElement* tail;
} Queue;

void free_queue(Queue* pqueue){
    QueueElement* ptr = pqueue->head;

    while(ptr != NULL){
        QueueElement* h = ptr;
        ptr = ptr->next;

        free(h);
    }

    pqueue->head = NULL;
    pqueue->tail = NULL;
}

void push_copy(Queue* pqueue, const Data* pdata){
    QueueElement* element = malloc(sizeof(QueueElement));
    element->next = NULL;
    element->data.len = pdata->len;
    element->data.results = pdata->results;

    if(pqueue->head == NULL){
        pqueue->head = element;
        pqueue->tail = element;
    } else {
        pqueue->tail->next = element;
        pqueue->tail = element;
    }
}

int peek(const Queue* pqueue, Data* pdata) {
    if(pqueue->head == NULL)
        return 1;

    pdata->len = pqueue->head->data.len;
    pdata->results = pqueue->head->data.results;

    return 0;
}

int pop(Queue* pqueue, Data* pdata){
    if(pqueue->head == NULL)
        return -1;

    pdata->len = pqueue->head->data.len;
    pdata->results = pqueue->head->data.results;

    QueueElement* el = pqueue->head;
    pqueue->head = pqueue->head->next;
    free(el);

    if(pqueue->head == NULL){
        pqueue->tail = NULL;
        return 0;
    }

    return 1;
}

int get_total_count(const Queue* pqueue){
    int count = 0;

    QueueElement* ptr = pqueue->head;
    while(ptr != NULL){
        count += ptr->data.len;
        ptr = ptr->next;
    }

    return count;
}

int main(void) {

    return 0;
}