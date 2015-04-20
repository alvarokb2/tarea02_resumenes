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
    booTokenPtr response = NULL;
    if (files != NULL) {
        response = getTokensAccess(files, fecha_i, fecha_f, -1);
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return response;
}

booTokenPtr leerCsvLocations() {
    FILE * files = fopen("GeoLite2-City-Locations-es.csv", "r");
    booTokenPtr response = NULL;
    if (files != NULL) {
        response = getTokensLocations(files, -1);
        
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return response;
}

booTokenPtr leerCsvBlocks() {
    FILE * files = fopen("GeoLite2-City-Blocks-IPv4.csv", "r");
    booTokenPtr response = NULL;
    if (files != NULL) {
        response = getTokensBlock(files, -1);
        
    } else {
        cout << "No se puede abrir el archivo." << endl;
    }
    fclose(files);
    return response;
}

#endif	/* ACCESS_H */

