#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_CAPACITY 5

typedef struct {
    char* name;
    char* surname;
    char pesel[12];
} Person;

typedef struct {
    Person** data;

    size_t size;
    size_t capacity;
} PersonList;

void init_pl(PersonList* p_pl){
    p_pl->data = malloc(sizeof(Person*)*BASE_CAPACITY);
    p_pl->capacity = BASE_CAPACITY;
    p_pl->size = 0;
}

void free_p(Person* p_p){
    free(p_p->name);
    free(p_p->surname);
    free(p_p);
}

void free_pl(PersonList* p_pl){
    for(int i = 0; i < p_pl->size; i++){
        free_p(p_pl->data[i]);
    }
    free(p_pl->data);
}

void fill_person_data(Person* p_p, const char* pesel, const char* name, const char* surname){
    p_p->name = strdup(name);
    p_p->surname = strdup(surname);

    memcpy(p_p->pesel, pesel, 12*sizeof(char));
}

Person* find(const PersonList* p_pl, const char* pesel){
    for(int i = 0; i < p_pl->size; i++){
        if(memcmp(p_pl->data[i]->pesel, pesel, 12) == 0)
            return p_pl->data[i];
    }

    return NULL;
}

int add(PersonList* p_pl, const char* pesel, const char* name, const char* surname){
    Person* found_person = find(p_pl, pesel);
    if(found_person != NULL){
        free(found_person->name);
        free(found_person->surname);

        found_person->name = strdup(name);
        found_person->surname = strdup(surname);

        return 1;
    }

    if(p_pl->size == p_pl->capacity){
        p_pl->data = realloc(p_pl->data, p_pl->capacity*2);
        p_pl->capacity *= 2;
    }

    Person* person = malloc(sizeof(Person));
    fill_person_data(person, pesel, name, surname);

    p_pl->data[p_pl->size] = person;
    p_pl->size++;

    return 0;
}

void merge(PersonList* p_target, const PersonList* p_src){
    for(int i = 0; i < p_src->size; i++){
        add(p_target, p_src->data[i]->pesel, p_src->data[i]->name, p_src->data[i]->surname);
    }
}

int main(){

}