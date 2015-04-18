/* 
 * File:   main.cpp
 * Author: alvarokb2
 *
 * Created on 9 de abril de 2015, 15:44
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "validar.h"
#include "access.h"

using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {
    if (argc == 2) {

        /*
         * Si el programa se ejecuta con la opci ́on -v Debe mostrar los integrantes del
         * grupo y la fecha de compilacion.
         */

        if (strcmp(*(argv + 1), "-v") == 0) {
            cout << " 1.- Alvaro Cabedo Vasquez" << endl;
            cout << " 2.- Fabian Castillo Salgado" << endl;
            cout << " 3.- Alexis Muñoz Acuña" << endl;
            cout << "Fecha de compilacion: ";
            puts(__DATE__); //Fecha de compilacion.
        } else {
            cout << "Error: Si ingresa 1 argumento debe ser -v" << endl;
        }
    } else if (argc == 5) {

        /*
         * Si el programa se ejecuta con la opci ́on -so desde hasta archivo (donde 
         * “desde” y “hasta” son fechas en formato ISO YYYY-mm-dd y “archivo” corre-
         * sponde al fichero access.log que tiene la informaci ́on) debe entregar el resumen
         * de la cantidad de peticiones por estado, agrupado por Sistema Operativo. Para
         * esto deben apoyarse en el archivo browscap.xml que contiene la informaci ́on
         * asociada al “user agent” de cada petici ́on.F
         */

        if (strcmp(*(argv + 1), "-so") == 0 &&
                ValidarArgumentos(*(argv + 2), *(argv + 3), *(argv + 4))) {
            cout << "Opcion so" << endl;

        }/*
             * Si el programa se ejecuta con la opci ́on -geo desde hasta archivo (donde
             * “desde” y “hasta” son fechas en formato ISO YYYY-mm-dd y “archivo” corre-
             * sponde al fichero access.log que tiene la informaci ́on) debe entregar el resumen
             * de la cantidad de peticiones por estado, agrupados por Pa ́ıs. Para esto deben
             * apoyarse en los archivos GeoLite2-City-Blocks-IPv4.csv y GeoLite2-City-
             * Locations-es.csv que poseen la informaci ́on geogr ́afica.
             */
        else if (strcmp(*(argv + 1), "-geo") == 0 &&
                ValidarArgumentos(*(argv + 2), *(argv + 3), *(argv + 4))) {

            leerLinea();
            
            ifstream flujo(*(argv + 4));
            string str;
            int count = 0;
            char c = flujo.get();
            while (flujo.good()) {
                if (c == '\n'){
                    count++;
                }
                str.append(&c);
                c = flujo.get();
                
            }
            
            cout << "Archivo: " << *(argv + 4) << endl;
            cout << "  - Size  : " << str.size() << endl;
            cout << "  - Lines : " << count << endl;
            flujo.close();




            cout << "Opcion geo" << endl;
        } else {
            cout << "La opcion " << *(argv + 1) << " no existe o los argumentos no son validos" << endl;
        }

    }
    return 0;
}
