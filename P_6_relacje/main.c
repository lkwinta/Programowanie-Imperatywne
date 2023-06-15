#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
    int first;
    int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair*, int, pair);

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair*, int);

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair*, int);

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair*, int);

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair*, int);

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair*, int);

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair*, int);

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair*, int);

// A total order relation is a partial order relation that is connected
int is_total_order(pair*, int);

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair*, int);

int find_max_elements(pair*, int, int*);
int find_min_elements(pair*, int, int*);
int get_domain(pair*, int, int*);

// Case 3:

int composition (pair*, int, pair*, int, pair*);

// Comparator for pair
int cmp_pair (const void *a, const void *b) {
    pair x = *((pair*)a);
    pair y = *((pair*)b);

    if(x.first > y.first){
        return 1;
    } else if(x.first == y.first){
        if(x.second > y.second)
            return 1;
        else
            return -1;
    } else {
        return -1;
    }
}

int cmp_int (const void *a, const void *b) {
    int x = *((int*)a);
    int y = *((int*)b);

    return x > y;
}

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
    if(n == MAX_REL_SIZE)
        return n;

    for(int i = 0; i < n; i++){
        if(tab[i].first == new_pair.first && tab[i].second == new_pair.second)
            return n;
    }

    tab[n] = new_pair;

    return n + 1;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
    int n;
    scanf("%i", &n);
    int a, b;
    for(int i = 0; i < n; i++){
        scanf("%i", &a);
        scanf("%i", &b);
        add_relation(relation, i, (pair){a, b});
    }

    return n;
}

void print_int_array(int *array, int n) {
    printf("%i \n", n);
    for(int i = 0; i < n; i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int to_do;
    pair relation[MAX_REL_SIZE];
    pair relation_2[MAX_REL_SIZE];
    pair comp_relation[MAX_REL_SIZE];
    int domain[MAX_REL_SIZE];
    int max_elements[MAX_REL_SIZE];
    int min_elements[MAX_REL_SIZE];

    scanf("%d",&to_do);
    int size = read_relation(relation);
    int ordered, size_2, n_domain;

    switch (to_do) {
        case 1:
            printf("%d ", is_reflexive(relation, size));
            printf("%d ", is_irreflexive(relation, size));
            printf("%d ", is_symmetric(relation, size));
            printf("%d ", is_antisymmetric(relation, size));
            printf("%d ", is_asymmetric(relation, size));
            printf("%d\n", is_transitive(relation, size));
            break;
        case 2:
            ordered = is_partial_order(relation, size);
            n_domain = get_domain(relation, size, domain);
            printf("%d %d\n", ordered, is_total_order(relation, size));
            print_int_array(domain, n_domain);
            if (!ordered) break;
            int no_max_elements = find_max_elements(relation, size, max_elements);
            int no_min_elements = find_min_elements(relation, size, min_elements);
            print_int_array(max_elements, no_max_elements);
            print_int_array(min_elements, no_min_elements);
            break;
        case 3:
            size_2 = read_relation(relation_2);
            printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair* relation, int n){
    int domain[MAX_REL_SIZE];
    int n_domain = get_domain(relation, n, domain);


    for(int i = 0; i < n_domain; i++){
        int znaleziono = 0;

        for(int j = 0; j < n; j++){
            if(relation[j].first == domain[i] && relation[j].second == domain[i])
                znaleziono = 1;
        }

        if (znaleziono == 0)
            return 0;
    }

    return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair* relation, int n){
    for(int i = 0; i < n; i++){
        if(relation[i].first == relation[i].second)
            return 0;
    }

    return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* relation, int n){
    for(int i = 0; i < n; i++){
        int znaleziono = 0;
        for(int j = 0; j < n; j++){
            //if(i != j) ?????
            if(relation[j].first == relation[i].second && relation[j].second == relation[i].first)
                znaleziono = 1;
        }

        if(znaleziono == 0)
            return 0;
    }

    return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* relation, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            //if(i != j) ?????
            if(relation[j].first == relation[i].second && relation[j].second == relation[i].first){
                if(relation[j].first != relation[i].first)
                    return 0;
            }
        }
    }

    return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair* relation, int n){
    for(int i = 0; i < n; i++){
        int znaleziono = 1;
        for(int j = 0; j < n; j++){
            //if(i != j) ?????
            if(relation[j].first == relation[i].second && relation[j].second == relation[i].first)
                znaleziono = 0;
        }

        if(znaleziono == 0)
            return 0;
    }

    return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair* relation, int n){
    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){
            //if(i != j) ?????
            if(relation[j].first == relation[i].second){
                int znaleziono = 0;

                for(int k = 0; k < n; k++){
                    if(relation[k].first == relation[i].first && relation[k].second == relation[j].second)
                        znaleziono = 1;
                }

                if(znaleziono == 0)
                    return 0;
            }
        }
    }

    return 1;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair* relation, int n){
    int a = is_reflexive(relation, n);
    int b = is_transitive(relation, n);
    int c = is_antisymmetric(relation, n);

    return (a && b && c);
}

// A total order relation is a partial order relation that is connected
int is_total_order(pair* relation, int n){
    return (is_partial_order(relation, n) && is_connected(relation, n));
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair* relation, int n){
    int domain[MAX_REL_SIZE];
    int n_domain = get_domain(relation, n, domain);

    for(int i = 0; i < n_domain; i++){
        for(int j = 0; j < n_domain; j++){
            int x = domain[i];
            int y = domain[j];

            int znaleziono = 0;

            for(int k = 0; k < n; k++){
                if((relation[k].first == x && relation[k].second == y) || (relation[k].first == y && relation[k].second == x))
                    znaleziono = 1;
            }

            if(znaleziono == 0)
                return 0;
        }
    }

    return 1;
}

int find_max_elements(pair* relation, int n, int* max_elements){
    int counter = 0;

    int domain[MAX_REL_SIZE];
    int n_domain = get_domain(relation, n, domain);

    for(int i = 0; i < n_domain; i++){
        int is_max = 1;
        for(int j = 0; j < n; j++){
            if(domain[i] == relation[j].first && domain[i] != relation[j].second){
                is_max = 0;
            }
        }

        if(is_max == 1){
            max_elements[counter] = domain[i];
            counter++;
        }
    }

    qsort(max_elements, counter, sizeof(int), cmp_int);

    return counter;
}

int find_min_elements(pair* relation, int n, int* min_elements){
    int counter = 0;

    int domain[MAX_REL_SIZE];
    int n_domain = get_domain(relation, n, domain);

    for(int i = 0; i < n_domain; i++){
        int is_min = 1;
        for(int j = 0; j < n; j++){
            if(domain[i] == relation[j].second && domain[i] != relation[j].first){
                is_min = 0;
            }
        }

        if(is_min == 1){
            min_elements[counter] = domain[i];
            counter++;
        }
    }

    qsort(min_elements, counter, sizeof(int), cmp_int);

    return counter;
}

int get_domain(pair* relation, int n, int* domain){
    int counter = 0;
    for(int i = 0; i < n; i++){
        int if_first = 1;
        int if_second = 1;
        for(int j = 0; j < counter; j++){
            if(domain[j] == relation[i].first)
                if_first = 0;
            if(domain[j] == relation[i].second)
                if_second = 0;
        }

        if(if_first){
            domain[counter] = relation[i].first;
            counter++;
        }

        if(if_second && relation[i].first != relation[i].second){
            domain[counter] = relation[i].second;
            counter++;
        }
    }

    qsort(domain, counter, sizeof(int), cmp_int);

    return counter;
}

// Case 3:

int composition (pair* relation1, int n1, pair* relation2, int n2, pair* relation_composition){
    int counter = 0;

    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            if(relation1[i].second == relation2[j].first){
                pair p = {relation1[i].first, relation2[j].second};

                int found = 0;

                for(int k = 0; k < counter; k++){
                    if(relation_composition[k].first == p.first && relation_composition[k].second == p.second)
                        found = 1;
                }

                if(found == 0){
                    relation_composition[counter] = p;
                    counter++;
                }
            }
        }
    }

    return counter;
}