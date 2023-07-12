#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int city1;
    int city2;

    double distance;
} Edge;

typedef struct {
    char** cities;
    int no_of_cities;
    int cities_capacity;

    Edge* edges;
    int no_of_edges;
    int edges_capacity;
} Map;

void init_map(Map* map){
    map->cities_capacity = 10;
    map->cities = malloc(sizeof(char*)*map->cities_capacity);
    map->no_of_cities = 0;

    map->edges_capacity = 10;
    map->edges = malloc(sizeof(Edge)*map->edges_capacity);
    map->no_of_edges = 0;
}

void free_map(Map* map){
    free(map->edges);
    for(int i = 0; i < map->no_of_cities; i++)
        free(map->cities[i]);

    free(map->cities);

    map->cities_capacity = 0;
    map->no_of_cities = 0;

    map->edges_capacity = 0;
    map->no_of_edges = 0;

    map->cities = NULL;
    map->edges = NULL;
}

int add_city(Map* map, const char* name){
    if(map->cities_capacity == map->no_of_cities){
        map->cities_capacity *= 2;
        map->cities = realloc(map->cities, map->cities_capacity);
    }

    for(int i = 0; i < map->no_of_cities; i++){
        if(strcmp(name, map->cities[i]) == 0)
            return -1;
    }

    map->cities[map->no_of_cities] = strdup(name);
    if(map->cities[map->no_of_cities] == NULL)
        return -1;

    map->no_of_cities++;
    return map->no_of_cities - 1;
}

int is_edge(const Map* map, int city_1, int city_2){
    for(int i = 0; i < map->no_of_edges; i++){
        if((map->edges[i].city1 == city_1 && map->edges[i].city2 == city_2) ||
           (map->edges[i].city2 == city_1 && map->edges[i].city1 == city_2))
            return 1;
    }

    return 0;
}

int add_edge(Map* map, int city_1, int city_2, int distance){
    if(map->no_of_edges == map->edges_capacity){
        map->edges_capacity *= 2;
        map->edges = realloc(map->edges, map->edges_capacity);
        if(map->edges == NULL)
            return -1;
    }

    if(is_edge(map, city_1, city_2))
        return -1;

    if(city_1 < 0 || city_1 >= map->no_of_cities ||
       city_2 < 0 || city_2 >= map->no_of_cities)
        return -1;

    map->edges[map->no_of_edges] = (Edge){
            .city1 = city_1,
            .city2 = city_2,
            .distance = distance
    };
    map->no_of_edges++;

    return 0;
}

int is_route(const Map* map, const int* route, int size){
    for(int i = 1; i < size; i++){
        if(is_edge(map, route[i - 1], route[i]) != 1)
            return 0;
    }

    return 1;
}