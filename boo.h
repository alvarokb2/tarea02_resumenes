/* 
 * File:   boo.h
 * Author: alvarokb2
 *
 * Created on 18 de abril de 2015, 17:32
 */
#ifndef BOO_H
#define	BOO_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
//namespace boo {

struct _booToken {
    struct _booToken* previous;
    struct _booToken* next;
    char* value;
    long start;
    long lengh;
};

typedef struct _booToken booToken;
typedef booToken* booTokenPtr;

void imprimirBooTokenPtr(const booTokenPtr&);
string convertirMes(const string&);
string parseFecha(const string&);
int compararFecha(const string&, const string&, const string&, const string&);
booTokenPtr addToken(booTokenPtr&, long&, string&);
booTokenPtr getTokensAccess(FILE *, const int&, void (*) (const booTokenPtr&));

void imprimirBooTokenPtr(const booTokenPtr& __token) {
    if (__token == NULL) return;
    cout << __token->value << endl;
}

string convertirMes(const string& __month) {
    if (__month == "Jan")return "01";
    else if (__month == "Feb")return "02";
    else if (__month == "Mar")return "03";
    else if (__month == "Apr")return "04";
    else if (__month == "May")return "05";
    else if (__month == "Jun")return "06";
    else if (__month == "Jul")return "07";
    else if (__month == "Aug")return "08";
    else if (__month == "Sep")return "09";
    else if (__month == "Oct")return "10";
    else if (__month == "Nov")return "11";
    else if (__month == "Dec")return "12";
}

string parseFecha(const string& __fecha) {
    string fecha = __fecha.substr(0, 11);
    string year = fecha.substr(7, 4);
    string month = fecha.substr(3, 3);
    string day = fecha.substr(0, 2);
    fecha = year + "-" + convertirMes(month) + "-" + day;
    return fecha;
}

int compararFecha(const string& __fecha1, const string& __fecha2) {
    if (__fecha1.substr(0, 4) < __fecha2.substr(0, 4)) {
        return -1;
    } else if (__fecha1.substr(0, 4) == __fecha2.substr(0, 4)) {
        if (__fecha1.substr(5, 2) < __fecha2.substr(5, 2)) {
            return -1;
        } else if (__fecha1.substr(5, 2) == __fecha2.substr(5, 2)) {
            if (__fecha1.substr(8, 2) < __fecha2.substr(8, 2)) {
                return -1;
            } else if (__fecha1.substr(8, 2) == __fecha2.substr(8, 2)) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

booTokenPtr addToken(booTokenPtr& __token, long& __start, string& __str) {
    booTokenPtr token = (booTokenPtr) malloc(sizeof (booToken));
    token->value = strdup(__str.c_str());
    token->start = __start;
    token->lengh = __str.length();
    token->previous = __token;
    token->next = NULL;
    if (__token != NULL) __token->next = token;
    __token = token;
    __str.clear();
    return token;
}

booTokenPtr getTokensAccess(
        FILE *file,
        const string& fecha_i,
        const string& fecha_f,
        const int& ex = -1,
        void (*func)(const booTokenPtr) = NULL
        ) {
    booTokenPtr response = NULL;
    booTokenPtr posToken = NULL;
    booTokenPtr auxToken = NULL;
    string str;
    int c = getc(file);
    long pos = 0;
    int estado = 0;
    int contador = 0;
    while (1) {
        switch (estado) {
            case 0:
                if (c != ' ' && c != '\n' && c != ex) {
                    while (c != ' ' && c != '\n' && c != ex) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    estado = 1;
                }
                break;
            case 1:
                if (c == '[') {
                    pos++;
                    c = getc(file);
                    while (contador++ <= 10) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    contador = 0;
                    estado = 2;
                }
                break;
            case 2:
                if (c == '"') {
                    pos++;
                    c = getc(file);
                    while (c != '"' && c != ex) {
                        pos++;
                        c = getc(file);
                    }
                    estado = 3;
                }
                break;
            case 3:
                if (isdigit(c) && c != ex) {
                    while (isdigit(c) && c != ex) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    estado = 4;
                }
                break;
            case 4:
                if (c == '"') {
                    if (++contador == 3) {
                        estado = 5;
                        contador = 0;
                    }
                }
                break;
            case 5:
                if (c != '"' && c != '\n' && c != ex) {
                    while (c != '"' && c != '\n' && c != ex) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    estado = 6;
                }
                break;
            case 6:
                if (c = '\n') estado = 0;
                break;
            default:
                break;
        }
        if (str.length() != 0) {
            if (estado == 2) {
                str = parseFecha(str);
                if (response == NULL) {
                    if (compararFecha(str, fecha_i) >= 0 && compararFecha(str, fecha_f) <= 0) {
                        response = auxToken;
                    }
                } else {
                    if (compararFecha(str, fecha_f) > 0) {
                        if (auxToken->previous != NULL) auxToken->previous->next = NULL;
                        break;
                    }
                }
            }
            auxToken = addToken(posToken, pos, str);
            if (func != NULL) func(posToken);
        } else {
            pos++;
            c = getc(file);
        }
        if (c == ex) break;
    }
    return response;
}

booTokenPtr getTokensLocations(
        FILE *file,
        int ex = -1,
        void (*func)(const booTokenPtr) = NULL
        ) {
    booTokenPtr response = NULL;
    booTokenPtr posToken = NULL;
    booTokenPtr auxToken = NULL;
    string str;
    int c = getc(file);
    long pos = 0;
    int estado = 0;
    int contador = 0;
    while (1) {
        switch (estado) {
            case 0:
                if (c != ',' && c != '\n' && c != ex) {
                    while (c != ',' && c != '\n' && c != ex) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    estado = 1;
                }
                break;
            case 1:
                if (c == ',') contador++;
                if (contador == 5) {
                    contador = 0;
                    estado = 2;
                }
                break;
            case 2:
                if (c != ',' && c != '\n' && c != ex) {
                    while (c != ',' && c != '\n' && c != ex) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    estado = 3;
                }
                break;
            case 3:
                if (c == '\n') estado = 0;
                break;
            default:
                break;
        }
        if (str.length() != 0) {
            auxToken = addToken(posToken, pos, str);
            if (func != NULL) func(auxToken);
            if (response == NULL) response = auxToken;
        } else {
            pos++;
            c = getc(file);
        }
        if (c == ex) break;
    }
    return response;
}

booTokenPtr getTokensBlock(
        FILE *file,
        int ex = -1,
        void (*func)(const booTokenPtr) = NULL
        ) {
    booTokenPtr response = NULL;
    booTokenPtr posToken = NULL;
    booTokenPtr auxToken = NULL;
    string str;
    int c = getc(file);
    long pos = 0;
    int estado = 0;
    int contador = 0;
    while (1) {
        switch (estado) {
            case 0:
                if (c != ',' && c != '\n' && c != ex) {
                    while (c != ',' && c != '\n' && c != ex) {
                        str += c;
                        pos++;
                        c = getc(file);
                    }
                    contador++;
                    if (contador == 2) {
                        contador = 0;
                        estado = 1;
                    }
                }
                break;
            case 1:
                if (c == '\n') estado = 0;
                break;
            default:
                break;
        }
        if (str.length() != 0) {
            auxToken = addToken(posToken, pos, str);
            if (func != NULL) func(auxToken);
            if (response == NULL) response = auxToken;
        } else {
            pos++;
            c = getc(file);
        }
        if (c == ex) break;
    }
    return response;
}

#endif	/* BOO_H */
