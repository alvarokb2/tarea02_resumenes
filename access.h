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

int contarLineas() {
    ifstream flujo("access.log");
    string str;
    int count = 0;
    char c = flujo.get();
    while (flujo.good()) {
        if (c == '\n') {
            count++;
        }
        str.append(&c);
        c = flujo.get();
    }
    flujo.close();
    return count;
}

void leerLinea2() {
    FILE * files = fopen("access.log", "r");
    booTokenPtr d;
    if (files != NULL) {
        d = getTokens(files, -1);
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
}

void leerLinea() {
    ifstream flujo("access.log", ios::in);
    string linea;
    int lineasArchivo = contarLineas();
    int count = 0;
    if (flujo.fail()) {
        cout << "Error al abrir archivo" << endl;
    } else {
        while (flujo.good() && count < lineasArchivo) {
            count++;

            getline(flujo, linea);
            Peticion *actual = new Peticion(linea);

            if (count % 1000 == 0) {
                cout << "ip: " << actual->getIp() << "/ fecha: " << actual->getFecha();
                cout << "/ estado: " << actual->getEstado() << endl;
                cout << "count: " << count << endl << "so: " << actual->getSo() << endl;
            }
        }
        flujo.close();
    }
}



#endif	/* ACCESS_H */

