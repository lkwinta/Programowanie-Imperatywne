#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// list node
typedef struct Node {
    int *data;
    size_t array_size;
    struct Node* next;
    struct Node* prev;
} Node;

// doubly linked list
typedef struct List {
    Node *head;
    Node *tail;
} List;

// iterator
typedef struct iterator {
    struct Node* node_ptr;
    size_t position;
} iterator;

// forward initialization
iterator begin(Node* head) {
    iterator it = { head, 0 };
    return it;
}

// backward initialization;
// points to the element following the last one
iterator end(Node* tail) {
    iterator it = { tail, tail->array_size };
    return it;
}

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr) return ptr;
    exit(EXIT_FAILURE);
}

void *safe_realloc(void *old_ptr, size_t size) {
    void *ptr = realloc(old_ptr, size);
    if (ptr) return ptr;
    free(old_ptr);
    exit(EXIT_FAILURE);
}

Node *create_node(int *data, size_t array_size, Node *next, Node *prev) {
    Node *node = safe_malloc(sizeof(Node));
    node->data = data;
    node->array_size = array_size;
    node->next = next;
    node->prev = prev;
    return node;
}

// initialize list
// creates the front and back sentinels
void init(List *list) {
    list->head = create_node(NULL, 0, NULL, NULL);
    list->tail = create_node(NULL, 0, NULL, list->head);
    list->head->next = list->tail;
}

// to implement ...

// append node to the list
void push_back(List *list, int *data, size_t array_size) {
    Node* node = create_node(data, array_size, list->tail, list->tail->prev);
    list->tail->prev->next = node;
    list->tail->prev = node;
}

// set iterator to move n elements forward from its current position
void skip_forward(iterator* itr, size_t n) {
    while (n != 0 && itr->node_ptr != NULL){
        if (itr->node_ptr->array_size != 0 &&
            itr->position < itr->node_ptr->array_size - 1)

            itr->position++;
        else {
            itr->node_ptr = itr->node_ptr->next;
            itr->position = 0;
        }
        n--;
    }
}

// forward iteration - get n-th element in the list
int get_forward(List *list, size_t n) {
    iterator itr = begin(list->head);
    skip_forward(&itr, n);
    return itr.node_ptr->data[itr.position];
}

// set iterator to move n elements backward from its current position
void skip_backward(iterator* itr, size_t n) {
    while (n != 0 && itr->node_ptr != NULL){
        if (itr->node_ptr->array_size != 0 && itr->position > 0)

            itr->position--;
        else {
            itr->node_ptr = itr->node_ptr->prev;
            itr->position = itr->node_ptr->array_size - 1;
        }

        n--;
    }
}

// backward iteration - get n-th element from the end of the list
int get_backward(List *list, size_t n) {
    iterator itr = end(list->tail);
    skip_backward(&itr, n);
    return itr.node_ptr->data[itr.position];
}

void remove_node(Node *node_ptr) {
    node_ptr->prev->next = node_ptr->next;
    node_ptr->next->prev = node_ptr->prev;
    free(node_ptr);
}

// remove n-th element; if array empty remove node
void remove_at(List *list, size_t n) {
    iterator itr = begin(list->head);
    skip_forward(&itr, n);
    if (itr.node_ptr->array_size == 1)
        remove_node(itr.node_ptr);
    else {
        for(size_t i = itr.position + 1; i < itr.node_ptr->array_size; i++){
            itr.node_ptr->data[i - 1] = itr.node_ptr->data[i];
        }
        itr.node_ptr->array_size--;
    }
}

// return the number of digits of number n
size_t digits(int n) {
    if (n == 0)
        return 1;
    return (size_t)(log10(abs(n)) + 1);
}

/**
 *
5
12
623 -14 733 29 22222 334 0 -12 -856 12345 1 -1
 * */

// inserts 'value' to the node with the same digits' count
// otherwise insert new node
void put_in_order(List *list, int value) {
    Node* node = list->head->next;
    size_t d = digits(value);

    while(node->next != NULL && digits(node->data[0]) < d)
        node = node->next;

    if(node->next == NULL) {
        int *data = safe_malloc(sizeof(int));
        data[0] = value;

        push_back(list, data, 1);
    }
    else if(digits(node->data[0]) > d){
        int *data = safe_malloc(sizeof(int));
        data[0] = value;

        Node* temp = create_node(data, 1, node, node->prev);
        node->prev->next = temp;
        node->prev = temp;
    } else {
        size_t pos = 0;
        while(node->data[pos] < value)
            pos++;

        node->data = realloc(node->data, sizeof(int) * (node->array_size + 1));
        node->array_size++;

        for(size_t i = node->array_size - 1; i > pos; i--)
            node->data[i] = node->data[i - 1];

        node->data[pos] = value;

    }
}

// -------------------------------------------------------------
// helper functions

// print list
void dumpList(const List *list) {
    for(Node *node = list->head->next; node != list->tail; node = node->next) {
        printf("-> ");
        for (int k = 0; k < node->array_size; k++) {
            printf("%d ", node->data[k]);
        }
        printf("\n");
    }
}

// free list
void freeList(List *list) {
    Node *to_delete = list->head->next, *next;
    while(to_delete != list->tail) {
        next = to_delete->next;
        remove_node(to_delete);
        to_delete = next;
    }
}

// read int vector
void read_vector(int tab[], size_t n) {
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", tab + i);
    }
}

// initialize the list and push data
void read_list(List *list) {
    int n;
    size_t size;
    scanf("%d", &n); // number of nodes
    for (int i = 0; i < n; i++) {
        scanf("%zu", &size); // length of the array in i-th node
        int *tab = (int*) safe_malloc(size * sizeof(int));
        read_vector(tab, size);
        push_back(list, tab, size);
    }
}

int main() {
    int to_do, value;
    size_t size, m;
    List list;
    init(&list);

    scanf("%d", &to_do);
    switch (to_do) {
        case 1:
            read_list(&list);
            dumpList(&list);
            break;
        case 2:
            read_list(&list);
            scanf("%zu", &size);
            for (int i = 0; i < size; i++) {
                scanf("%zu", &m);
                printf("%d ", get_forward(&list, m));
            }
            printf("\n");
            break;
        case 3:
            read_list(&list);
            scanf("%zu", &size);
            for (int i = 0; i < size; i++) {
                scanf("%zu", &m);
                printf("%d ", get_backward(&list, m));
            }
            printf("\n");
            break;
        case 4:
            read_list(&list);
            scanf("%zu", &size);
            for (int i = 0; i < size; i++) {
                scanf("%zu", &m);
                remove_at(&list, m);
            }
            dumpList(&list);
            break;
        case 5:
            scanf("%zu", &size);
            for (int i = 0; i < size; i++) {
                scanf("%d", &value);
                put_in_order(&list, value);
            }
            dumpList(&list);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    freeList(&list);

    return 0;
}