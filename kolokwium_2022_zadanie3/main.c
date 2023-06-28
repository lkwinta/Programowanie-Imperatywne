#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

typedef enum {
    car,
    bus,
    truck
} VEHICLE_TYPE;

typedef enum {
    electric,
    hybrid,
    combustion
} PROPULSION_TYPE;

struct Car {
    int seats_number;
    float engine_power;
};

struct Bus {
    int sitting_places;
    int standing_places;
};

struct Truck {
    float engine_volume;
    float max_axle_load;
};

struct Vehicle {
    char* owner;
    int next_inspection[3]; // d/m/y
    VEHICLE_TYPE vehicle_type;
    PROPULSION_TYPE propulsion_type;

    union {
        struct Car car;
        struct Bus bus;
        struct Truck truck;
    } specific;
};

void new_owner(struct Vehicle* pvehicle) {
    free(pvehicle->owner); // sprawdzic czy jest zaalokowany na pewno ? zmienna stanu?
    char buffer[BUFFER_SIZE] = {0};
    scanf("%s", buffer);

    pvehicle->owner = calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(pvehicle->owner, buffer);
}

int compare_date(int* a, int* b){
    if (a[2] < b[2])
        return -1;
    if (a[2] > b[2])
        return 1;

    if (a[1] < b[1])
        return -1;
    if (a[1] > b[1])
        return 1;

    if (a[0] < b[0])
        return -1;
    if (a[0] > b[0])
        return 1;

    return 0;
}

int delayed(struct Vehicle* pvehicle, int size, int* base_date, char*** pdelayed_owners){
    int delayed_count = 0;
    char** owners = malloc(sizeof(char*)*size);

    for(int i = 0; i < size; i++){
        if(compare_date(pvehicle[i].next_inspection, base_date) < 0){

            delayed_count++;

            owners[delayed_count - 1] = strdup(pvehicle[i].owner);
        }
    }

    owners = realloc(owners, delayed_count*sizeof(char*));

    *pdelayed_owners = owners;

    return delayed_count;
}

void print_pojazd(struct Vehicle* pvehicle){
    printf("Owner: %s \n", pvehicle->owner);
    printf("Next inspection: %i.%i.%i \n", pvehicle->next_inspection[0], pvehicle->next_inspection[1], pvehicle->next_inspection[2]);
    printf("Vehicle type: %i \n", pvehicle->vehicle_type);
    printf("Propulsion type: %i \n", pvehicle->propulsion_type);

    switch(pvehicle->vehicle_type){
        case car:
            printf("Seats: %i \n", pvehicle->specific.car.seats_number);
            printf("Engine Power: %f \n", pvehicle->specific.car.engine_power);
            break;
        case bus:
            printf("Sitting Places: %i \n", pvehicle->specific.bus.sitting_places);
            printf("Standing Places: %i \n", pvehicle->specific.bus.standing_places);
            break;
        case truck:
            printf("Engine Volume: %f \n", pvehicle->specific.truck.engine_volume);
            printf("Max Axle Load: %f \n", pvehicle->specific.truck.max_axle_load);
            break;
    }
}

int main(void) {
    const char* name = "owner1";
    struct Vehicle v1 = {
            .owner = strdup(name),
            .next_inspection[0] = 24,
            .next_inspection[1] = 01,
            .next_inspection[2] = 2003,
            .vehicle_type = car,
            .propulsion_type = combustion,
            .specific.car = {
                    .engine_power = 105.0f,
                    .seats_number = 5
            }
    };

    const char* name3 = "owner3";
    struct Vehicle v2 = {
            .owner = strdup(name3),
            .next_inspection[0] = 24,
            .next_inspection[1] = 01,
            .next_inspection[2] = 2003,
            .vehicle_type = car,
            .propulsion_type = combustion,
            .specific.car = {
                    .engine_power = 105.0f,
                    .seats_number = 5
            }
    };

    const char* name2 = "owner2";
    struct Vehicle v3 = {
            .owner = strdup(name2),
            .next_inspection[0] = 24,
            .next_inspection[1] = 01,
            .next_inspection[2] = 2007,
            .vehicle_type = car,
            .propulsion_type = combustion,
            .specific.car = {
                    .engine_power = 105.0f,
                    .seats_number = 5
            }
    };


    struct Vehicle vl[3] = {v1, v2, v3};

    char** array;
    int base_date[3] = {25, 1, 2004};
    int size = delayed(vl, 3, base_date, &array);

    for(int i = 0; i < size; i++)
        printf("%s \n", array[i]);


    return 0;
}