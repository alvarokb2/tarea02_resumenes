/* 
 * File:   access.h
 * Author: alvarokb2
 *
 * Created on 16 de abril de 2015, 12:14
 */

#ifndef ACCESS_H
#define	ACCESS_H

#include "boo.h"
using namespace std;

booTokenPtr leerAccess(char * fecha_i, char * fecha_f, char * archivo) {
    FILE * files = fopen(archivo, "r");
    booTokenPtr d;
    if (files != NULL) {
        d = getTokensAccess(files,fecha_i, fecha_f, -1);
        if (d != NULL) {
            int i = 0;
            do {
                imprimir(d);
                d = d->next;
            } while (d != NULL);
        }
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return d;
}

booTokenPtr leerCsvLocations() {
    FILE * files = fopen("GeoLite2-City-Locations-es.csv", "r");
    booTokenPtr d;
    if (files != NULL) {
        d = getTokensLocations(files, -1);
        if (d != NULL) {
            int i = 0;
            do {
                d = d->next;
            } while (d != NULL);
        }
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return d;
}

booTokenPtr leerCsvBlock() {
    FILE * files = fopen("GeoLite2-City-Blocks-IPv4.csv", "r");
    booTokenPtr d;
    if (files != NULL) {
        d = getTokensBlock(files, -1);
        if (d != NULL) {
            int i = 0;
            do {
                d = d->next;
            } while (d != NULL);

        }
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return d;
}



#endif	/* ACCESS_H */

