#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include <stdbool.h>

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


void insertMap(HashMap * map, char * key, void * value) {
  long posicion=hash(key, map->capacity);
  Pair * par=createPair(key, value);
  
  if(map->buckets[posicion]!=NULL){
    if(is_equal(map->buckets[posicion]->key, key)==1){
      return;
    }
  }
  
  if(map->buckets[posicion]==NULL){
    map->buckets[posicion]=par;
  }
    
  else{
    
    for(long i=(posicion+1)%map->capacity; i!=posicion%map->capacity ; i=(i+1) % map->capacity)  {
      if(map->buckets[i]!=NULL){
        if(is_equal(map->buckets[i]->key, key)==1){
          return;
        }
      }
      
      if(map->buckets[i]==NULL){
        map->buckets[i]=par;  
      }

    }
  }
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->capacity = capacity;
    map->buckets = (Pair **) calloc (map->capacity,sizeof(Pair *));
    map->size = 0;
    map->current= -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
  Pair *par=searchMap(map, key);
  if(par!=NULL){
    par->key=NULL;
    map->size--;
  }
  
}

Pair * searchMap(HashMap * map,  char * key) {   
  long posicion=hash(key, map->capacity);
  
  if(map->buckets[posicion]!=NULL){
    if(is_equal(map->buckets[posicion]->key, key)==1){
      map->current=posicion;
      return map->buckets[posicion];
    }
    else{
      while(true){
        if(map->buckets[posicion]==NULL){
          return NULL;
        }
        if(is_equal(map->buckets[posicion]->key, key)==1){
          map->current=posicion;
          return map->buckets[posicion];
        }
        posicion=(posicion+1)%map->capacity;
      }
    }
  }
  else{
    return NULL;
  }
  
}

Pair * firstMap(HashMap * map) {
  
  for(long i=0; i<map->capacity; i++){
    Pair *par=map->buckets[i];
    if(par->key!=NULL){
      map->current=i;
      return par;
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
