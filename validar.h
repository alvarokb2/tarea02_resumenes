/* 
 * File:   validar.h
 * Author: alvarokb2
 *
 * libreria con funciones utiles para la validacion de parametros
 * ingresados por linea de comandos
 * 
 *  
 * bool esBisiesto(int n) :
 * true si el año es bisiesto
 * 
 * bool ValidarFecha(char fecha[32]) :
 * true si la fecha es valida
 * 
 * bool ValidarArchivo(char archivo[64]) : 
 * true si el archivo es valido
 *
 * bool ValidarArgumentos(char f1[32], char f2[32], char archivo[64]) :

 *  * valida argumentos ingresados por linea de comandos
 * 
 * Created on 15 de abril de 2015, 1:59
 */

#ifndef VALIDAR_H
#define	VALIDAR_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

bool esBisiesto(int n) {
    if (n % 4 == 0) {
        if (n % 100 == 0) {
            if (n % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

//valida fecha en formato iso yyyy-mm-dd
bool ValidarFecha(char fecha[32]) {
    string _fecha = fecha;
    string aux;

    if (_fecha.length() == 10) {
        //condición guiones
        if (_fecha.substr(4, 1) == "-" && _fecha.substr(7, 1) == "-") {

            aux = _fecha.substr(0, 4) + _fecha.substr(5, 2) + _fecha.substr(8, 2);
            _fecha = aux.substr(0, 8);
            
            //verifica que sean digitos
            for (int i = 0; i < _fecha.length(); i++) {
                if (!isdigit(_fecha[i])) {
                    return false;
                }
            }
            
            //pasa los string a entero para aplicar condiciones de borde
            int year = atoi(_fecha.substr(0, 4).c_str());
            int month = atoi(_fecha.substr(4, 2).c_str());
            int day = atoi(_fecha.substr(6, 2).c_str());
            //condicion year valido
            if (year > 1900 && year < 2100) {
                //condicion mes valido
                if (month > 0 && month <= 12) {
                    //condicion dia valido
                    if (day > 0) {
                        //regla dia de cada mes
                        if (month == 1 || month == 3 || month == 5 || month == 7
                                || month == 8 || month == 10 || month == 12) {
                            if (day <= 31) {
                                //cout << "Fecha valida" << endl;
                                return true;
                            } else {
                                cout << "Mes " << month << "tiene 31 dias" << endl;
                                return false;
                            }
                        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
                            if (day <= 30) {
                                //cout << "Fecha valida" << endl;
                                return true;
                            } else {
                                cout << "Mes " << month << " tiene 30 dias" << endl;
                                return false;
                            }
                        } else {
                            if (esBisiesto(year)) {
                                if (day <= 29) {
                                    //cout << "Fecha valida" << endl;
                                    return true;
                                } else {
                                    cout << "Año es bisiesto, el mes 2 tiene 29 dias" << endl;
                                    return false;
                                }
                            } else {
                                if (day <= 28) {
                                    //cout << "Fecha valida" << endl;
                                    return true;
                                } else {
                                    cout << "El mes 2 tiene 28 dias" << endl;
                                    return false;
                                }

                            }

                        }


                    } else {
                        cout << "Dia debe ser mayor que 0" << endl;
                    }

                } else {
                    cout << "Mes debe estar entre 1 y 12" << endl;
                }

            } else {
                cout << "Año debe estar entre 1900 y 2099" << endl;
            }

        } else {
            cout << "Las fechas solo pueden contener numeros y guiones en formato yyyy-mm-dd" << endl;
            return false;
        }

    } else {
        cout << "Las fechas solo pueden contener numeros y guiones en formato yyyy-mm-dd" << endl;
        return false;
    }
}

bool ValidarArchivo(char archivo[64]) {
    string file = archivo;

    if (file == "access.log") {
        //cout << "Archivo valido" << endl;
        return true;
    } else {
        cout << "El archivo especificado es distinto a access.log" << endl;
        return false;
    }
}

bool ValidarArgumentos(char f1[32], char f2[32], char archivo[64]) {
    if (ValidarFecha(f1)) {
        if (ValidarFecha(f2)) {
            if (ValidarArchivo(archivo)) {

                return true;
            } else {
                cout << "Tercer Argumento Invalido" << endl;
                return false;
            }
        } else {
            cout << "Segundo Argumento Invalido" << endl;
            return false;
        }
    } else {

        cout << "Primer Argumento Invalido" << endl;
        return false;
    }
}


#endif	/* VALIDAR_H */

