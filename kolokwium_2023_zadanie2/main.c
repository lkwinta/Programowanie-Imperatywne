#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Drive_type { combustion, electric, d_ndef };
enum Fuel_type { gasoline, diesel, gas, hydrogen, f_d_ndef };
enum Battery_type { Li_Ion, Na_Ion, NiMH, b_d_ndef};

typedef struct {
    int d; int m; int y;
} Date;

typedef struct {
    enum Fuel_type fuel_t;
    char emmision[15];
} Comb_data;

typedef struct {
    enum Battery_type bat_t;
    float capacity;
} El_data;

typedef struct {
    char owner[30];
    Date valid_date;
    enum Drive_type d_type;

    union {
        Comb_data cs;
        El_data es;
    } drv_union;
} Vehicle;

int compare_date(const void* _a, const void* _b){
    Date a = *(Date*)_a;
    Date b = *(Date*)_b;

    if (a.y < b.y)
        return -1;
    if (a.y > b.y)
        return 1;

    if (a.m < b.m)
        return -1;
    if (a.m > b.m)
        return 1;

    if (a.d < b.d)
        return -1;
    if (a.d > b.d)
        return 1;

    return 0;
}

int delayed(const Vehicle* tv, int size, const Date* base_date, char*** pdelayed_owners){
    int delayed_count = 0;
    char** owners = malloc(sizeof(char*)*size);

    for(int i = 0; i < size; i++){
        if(compare_date(&tv[i].valid_date, base_date) > 0){
            delayed_count++;
            owners[delayed_count - 1] = strdup(tv[i].owner);
        }
    }
    if(delayed_count == 0){
        free(owners);
        *pdelayed_owners = NULL;
    } else {
        owners = realloc(owners, delayed_count*sizeof(char*));
        *pdelayed_owners = owners;
    }

    return delayed_count;
}

void print_owners(const char** t_owners, size_t size){
    for(size_t i = 0; i < size; i++){
        printf("%s \n", t_owners[i]);
    }
    printf("\n");
}

void init_vehicle(Vehicle* v){
    memset(v->owner, 0, 30);
    v->valid_date = (Date){
        .d = 1,
        .m = 1,
        .y = 1970
    };

    v->d_type = d_ndef;
}

void print_drive_data(const Vehicle* v){
    switch(v->d_type){
        case combustion:
            printf("Naped: comb, paliwo: ");
            switch(v->drv_union.cs.fuel_t){
                case gasoline:
                    printf("gasoline");
                    break;
                case diesel:
                    printf("diesel");
                    break;
                case gas:
                    printf("gas");
                    break;
                case hydrogen:
                    printf("hydrogen");
                    break;
                case f_d_ndef:
                    break;
            }
            printf(", emisja: %s \n", v->drv_union.cs.emmision);
            break;
        case electric:
            printf("Naped: el, bateria: ");
            switch(v->drv_union.es.bat_t){
                case Li_Ion:
                    printf("Li_Ion");
                    break;
                case Na_Ion:
                    printf("Na_Ion");
                    break;
                case NiMH:
                    printf("NiMH");
                    break;
                case b_d_ndef:
                    break;
            }
            printf(", pojemnosc: %fkWh \n", v->drv_union.es.capacity);
            break;
        case d_ndef:
            break;
    }
}

void new_owner(Vehicle* v, const char* str){
    memset(v->owner, 0, 30);

    //kopiuję maksymalnie 29 znaków aby zachować miejsce na znak \0 na koncu stringa
    strcpy_s(v->owner, 29, str);
   // free(str); w poleceniu było napisane że zwalnia łańcuch ale jest const ?
}

int main(void) {
    const char *name = "owner1";
    Vehicle v1 = {
            .valid_date = (Date){
                .d = 1,
                .m = 1,
                .y = 2003
            },
            .d_type = combustion,
            .drv_union.cs.fuel_t = gasoline,
            .drv_union.cs.emmision = "sdfsfsf"
    };
    new_owner(&v1, name);

    const char *name2 = "owner2";
    Vehicle v2 = {
            .valid_date = (Date){
                    .d = 1,
                    .m = 1,
                    .y = 2007
            },
            .d_type = electric,
            .drv_union.es.bat_t = Li_Ion,
            .drv_union.es.capacity = 60
    };
    new_owner(&v2, name2);

    const char *name3 = "owner3";
    Vehicle v3 = {
            .valid_date = (Date){
                    .d = 1,
                    .m = 1,
                    .y = 2007
            }
    };
    new_owner(&v3, name3);

    Vehicle vl[3] = {v1, v2, v3};
    print_drive_data(&v1);
    print_drive_data(&v2);

    char **array;
    Date base_date = {25, 1, 2004};
    int size = delayed(vl, 3, &base_date, &array);

    print_owners(array, size);

    return 0;
}