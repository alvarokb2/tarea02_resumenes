/* 
 * File:   access.h
 * Author: alvarokb2
 *
 * Created on 16 de abril de 2015, 12:14
 */

#ifndef ACCESS_H
#define	ACCESS_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#include "access.h"
#include "Peticion.cpp"

void leerLinea() {
    ifstream flujo("access.log", ios::in);
    string linea;
    int count = 0;
    if (flujo.fail()) {
        cout << "Error al abrir archivo" << endl;
    } else {
        while (flujo.good()) {
            count++;

                getline(flujo, linea);
                Peticion *actual = new Peticion(linea);
                cout << "ip: " << actual->getIp() << "/ fecha: " << actual->getFecha() << "/ estado: " << actual->getEstado() << endl;
                cout << "count: " << count << endl <<"so: " << actual->getSo() << endl;
            
        }
        flujo.close();
    }
}



#endif	/* ACCESS_H */

