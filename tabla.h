/* 
 * File:   tablageo.h
 * Author: alvarokb2
 *
 * Created on 19 de abril de 2015, 13:20
 */

#ifndef TABLAGEO_H
#define	TABLAGEO_H

#include "boo.h"

struct _tabla {
    struct _tabla * previous;
    struct _tabla * next;
    string id;
    int estados[52];
};

typedef struct _tabla tabla;
typedef tabla * tablaPtr;

int indexEstado(string estado);


tablaPtr addFila(tablaPtr &_fila, string _id, string _estado) {
    tablaPtr fila = (tablaPtr) malloc(sizeof (tabla));
    fila->id = _id;
    fila->estados[indexEstado(_estado)]++;
    if(fila != NULL) _fila->next = fila;
    _fila = fila;
    return fila;
}

tablaPtr sumarEstado(tablaPtr _tabla,string _id, string _estado){
    tablaPtr actual = _tabla;
    int aux = 0;
    while(actual !=NULL && aux == 0){
        if(actual->id == _id){
            actual->estados[indexEstado(_estado)]++;
            aux = 1;
            while(actual->next!=NULL){
                actual = actual->next;
            }
        }
        else{
            if(actual->next != NULL){
                actual = actual->next;    
            }
        }
    }
    if(aux == 0){
        actual = addFila(_tabla,_id,_estado);
    }
    return actual;
}


tablaPtr getTabla(booTokenPtr _access, booTokenPtr _location, booTokenPtr _block) {
    tablaPtr response = NULL;
    tablaPtr aux = NULL;
    booTokenPtr access = _access;
    booTokenPtr location = _location;
    booTokenPtr block = _block;
    while (access->value!=NULL) {
        while(access->value != block->value && block->value!=NULL) {
            block = block->next->next;
        }
        block = block->next;
        while(block->value != location->value){
            location = location->next->next;
        }
        location = location->next;
        access = access->next->next;
        sumarEstado(aux,location->value, access->value);
        if(response == NULL){
            response = aux;
        }
    }
    return response;
}

int indexEstado(string estado) {
    if(estado == "101")return 0;
    else if(estado == "102")return 1;

    else if(estado == "200")return 2;
    else if(estado == "202")return 3;
    else if(estado == "203")return 4;
    else if(estado == "204")return 5;
    else if(estado == "205")return 6;
    else if(estado == "206")return 7;
    else if(estado == "207")return 8;
    
    else if(estado == "300")return 9;
    else if(estado == "301")return 10;
    else if(estado == "302")return 11;
    else if(estado == "303")return 12;
    else if(estado == "304")return 13;
    else if(estado == "305")return 14;
    else if(estado == "306")return 15;
    else if(estado == "307")return 16;
    
    else if(estado == "400")return 17;
    else if(estado == "401")return 18;
    else if(estado == "402")return 19;
    else if(estado == "403")return 20;
    else if(estado == "404")return 21;
    else if(estado == "405")return 22;
    else if(estado == "406")return 23;
    else if(estado == "407")return 24;
    else if(estado == "408")return 25;
    else if(estado == "409")return 26;    
    else if(estado == "410")return 27;    
    else if(estado == "411")return 28;    
    else if(estado == "412")return 29;    
    else if(estado == "413")return 30;    
    else if(estado == "414")return 31;    
    else if(estado == "415")return 32;    
    else if(estado == "416")return 33;    
    else if(estado == "417")return 34;    
    else if(estado == "418")return 35;

    else if(estado == "422")return 36;
    else if(estado == "423")return 37;
    else if(estado == "424")return 38;
    else if(estado == "425")return 39;
    else if(estado == "426")return 40;
    else if(estado == "429")return 41;
    else if(estado == "449")return 42;
    
    else if(estado == "500")return 43;
    else if(estado == "501")return 44;
    else if(estado == "502")return 45;
    else if(estado == "503")return 46;
    else if(estado == "504")return 47;
    else if(estado == "505")return 48;
    else if(estado == "506")return 49;
    else if(estado == "507")return 50;
    else if(estado == "509")return 51;
    else if(estado == "510")return 52;

}

#endif	/* TABLAGEO_H */

