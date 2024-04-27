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


/*a - Cree una variable auxiliar de tipo Pair** para matener el arreglo map->buckets (old_buckets); LISTO

  b - Duplique el valor de la variable capacity. LISTO

  c - Asigne a map->buckets un nuevo arreglo con la nueva capacidad. LISTO

  d - Inicialice size a 0. LISTO

  e - Inserte los elementos del arreglo old_buckets en el mapa (use la función insertMap que ya implementó) */

void enlarge(HashMap * map) {
  if (map == NULL){
    return;
  }

  Pair ** arregloAntiguo = map->buckets;
  map->capacity = map->capacity * 2;
  map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));
  if (map->buckets == NULL){
    return;
  }
  map->size = 0;

  for (int i = 0; i < map->capacity; i++){
    if (arregloAntiguo[i] != NULL && arregloAntiguo[i]->key != NULL){
      int pos = hash(arregloAntiguo[i]->key, map->capacity);
      while (map->buckets[pos] != NULL){
        pos = (pos + 1) % map->capacity;
      }
      map->buckets[pos] = arregloAntiguo[i];
      map->size++;
    }
  }
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
  if (map == NULL || key == NULL){
    return;
  }
  long pos = hash(key, map->capacity);
  while (map->buckets[pos] != NULL){
    if (strcmp(map->buckets[pos]->key, key) == 0){
      map->buckets[pos]->key = NULL;
      map->size = map->size - 1;
      return;
    }
    pos = (pos + 1) % map->capacity;
  }
}


Pair * searchMap(HashMap * map,  char * key) {   
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
  if (map == NULL || map->size == 0){
    return NULL;
  }
for (int i = 0; i < map->capacity; i++){
  if (map->buckets[i] != NULL && map->buckets[i]->key != NULL){
    map->current = i;
    return map->buckets[i];
  }
}
  return NULL;
}


Pair * nextMap(HashMap * map) {
  if (map == NULL || map->size == 0){
    return NULL;
  }
  for (int i = map->current + 1; i < map->capacity; i++){
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL){
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

