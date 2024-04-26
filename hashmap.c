#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;


struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};


Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}


long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value){
  if (map == NULL || key == NULL){
    return;
  }
  long pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL && map->buckets[pos]->key != NULL){
    if (is_equal(map->buckets[pos]->key, key)){
      return;
    }
    pos = (pos + 1) % map->capacity;
  }
  char* nuevaKey = (char *)malloc(strlen(key)+1);
  strcpy(nuevaKey, key);
  map->buckets[pos] = createPair(nuevaKey, value);
  map->size++;
  map->current = pos; 
}


void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
  if (capacity <= 0){
    return NULL;
  }
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (Pair ** )calloc(capacity, sizeof(Pair *));
  for (int i = 0; i < capacity; i++){
    map->buckets[i] = NULL;
    }

  map->size = 0;
  map->capacity = capacity;
  map->current = -1; 
    return map;
}


void eraseMap(HashMap * map,  char * key) {    
}


Pair * searchMap(HashMap * map,  char * key) {   
  /* 3.- Implemente la función Pair * searchMap(HashMap * map, char * key), la cual retorna el Pair asociado a la clave ingresada. Recuerde que para buscar el par debe:

    a - Usar la función hash para obtener la posición donde puede encontrarse el par con la clave / LISTO 

    b - Si la clave no se encuentra avance hasta encontrarla (método de resolución de colisiones) 

    c - Si llega a una casilla nula, retorne NULL inmediatamente (no siga avanzando, la clave no está)

    Recuerde actualizar el índice current a la posición encontrada. Recuerde que el arreglo es circular. */
  if (map == NULL || key == NULL){
    return NULL;
  }
  long pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL){
    if (strcmp(map->buckets[pos] -> key, key) == 0){
      map->current = pos;
      return map->buckets[pos];
    }
    pos = (pos + 1) % map->capacity;
  }
    return NULL;
}


Pair * firstMap(HashMap * map) {
    return NULL;
}


Pair * nextMap(HashMap * map) {
    return NULL;
}

