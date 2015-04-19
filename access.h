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

int compararFecha(string fecha1, string fecha2) {
    if (fecha1.substr(0, 4) < fecha2.substr(0, 4)) {
        return -1;
    } else {
        if (fecha1.substr(6, 2) < fecha2.substr(6, 2)) {
            return -1;
        } else {
            if (fecha1.substr(8, 2) < fecha2.substr(8, 2)) {
                return -1;
            } else {
                return 1;
            }
        }
    }
}

booTokenPtr leerAccess(char * archivo) {
    FILE * files = fopen(archivo, "r");
    booTokenPtr d;
    if (files != NULL) {
        d = getTokensAccess(files, -1);
        if (d != NULL) {
            int i = 0;
            do {
                imprimir(d);
                d = d->next;
            } while (d != NULL && ++i < 80);
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
                imprimir(d);
            } while (d != NULL && ++i < 80);
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
                imprimir(d);
            } while (d != NULL && ++i < 80);

        }
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return d;
}

#endif	/* ACCESS_H */

