#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    unsigned int day:5;
    unsigned int month:4;
    unsigned int year:12;
} Date;

typedef struct{
    char name[32];
    char address[64];
    int  reg_no;
    Date reg_date;
} Institution;

Institution* create_inst(const char* name, const char* address, int reg_no, Date reg_date){
    Institution* institution = malloc(sizeof(Institution));
    if(institution == NULL)
        return NULL;

    memset(institution->name, 0, 32);
    memset(institution->address, 0, 32);

    if(strlen(name) >= 32)
        memcpy(institution->name,name, 32 - 1);
    else
        strcpy(institution->name, name);

    if(strlen(name) >= 64)
        memcpy(institution->address,address, 64 - 1);
    else
        strcpy(institution->address, address);

    institution->reg_date = reg_date;
    institution->reg_no = reg_no;

    return institution;
}

Institution* clone_inst(const Institution *src){
    Institution* copy = malloc(sizeof(Institution));
    if(copy == NULL)
        return NULL;
    memcpy(copy, src, sizeof(Institution));
    return copy;
}

void print_inst(const Institution* inst){
    if(inst == NULL)
        return;

    printf("Name: %s\n", inst->name);
    printf("Address: %s\n", inst->address);
    printf("Reg no: %i\n", inst->reg_no);
    printf("Reg date: %i.%i.%i\n", inst->reg_date.day, inst->reg_date.month, inst->reg_date.year);
}

void name_to_upper(Institution* inst){
    if(inst == NULL)
        return;

    for(size_t i = 0; i < strlen(inst->name); i++){
        inst->name[i] = toupper(inst->name[i]);
    }
}

typedef struct tagListElement {
    struct tagListElement *next;
    Institution *data;
} ListElement;

typedef struct tagList {
    ListElement *head;
    ListElement *tail;
} InstList;

void instlst_init(InstList* list){
    list->head = NULL;
    list->tail = NULL;
}

void instlst_push_back(InstList* list, Institution* data){
    ListElement* listElement = malloc(sizeof(listElement));
    listElement->data = data;
    listElement->next = NULL;

    if(list->head == NULL){
        list->head = listElement;
        list->tail = listElement;
    } else {
        list->tail->next = listElement;
        list->tail = listElement;
    }
}

void instlst_for_each(const InstList* list, void (*f)(Institution* data)){
    if(f == NULL)
        return;

    ListElement* ptr = list->head;

    while (ptr != NULL){
        f(ptr->data);
        ptr = ptr->next;
    }
}

int main(void) {
    InstList list;
    instlst_init(&list);
    Date date = {30,10,1951};
    Institution* insti1 ;     // definicje zmiennej / zmiennych
    insti1 = create_inst("Polska Akademia Nauk","Al. Defilad 1, 00-901 Warszawa",251575083,date);
    print_inst( insti1 );  // drukuje pola utworzonej struktury
    Institution* insti2 ;   // definicje zmiennej / zmiennych
    insti2 = clone_inst( insti1 );
    print_inst( insti2 );  // drukuje pola utworzonej kopii

// Definicja i inicjalizacja tablicy instytucji:
    InstList instList;
    instlst_init(&instList);
    Institution tab[]={
            {"Teatr Ateneum","ul. Jaracza 2, 00-378 Warszawa",35325,{5,10,1928}},
            {"Kopalnia Soli Wieliczka","Park Kingi 1, 32-020 Wieliczka",685675,{5,6,1368}},
            {"Hotel Bachleda Kasprowy","ul. Szymaszkowa, 34-500 Zakopane",5355,{15,12,2001}},
            {"NIK","ul. Filtrowa 57,02-056 Warszawa",456,{5,6,1953}},
            {"PGE Narodowy","Al. Ks. J. Poniatowskiego 1, 03-901 Warszawa",77557,{30,4,2012}},
            {"Kopalnia Piasku Jan","ul. Zapolskiej 25, 41-218 Sosnowiec",89698,{5,6,1968}}
    };
// Pętla dodająca do listy list elementy z danymi powyższych instytucji.
    for(int i = 0; i < sizeof(tab)/sizeof(Institution); i++){
        instlst_push_back(&instList, &tab[i]);
    }
// Należy wykorzystać wcześniej zdefiniowane funkcje.
    instlst_for_each(&instList, name_to_upper);

    for(int i = 0; i < sizeof(tab)/sizeof(Institution); i++){
        print_inst(&tab[i]);
    }
    return 0;
}