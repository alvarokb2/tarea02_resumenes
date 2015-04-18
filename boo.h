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

#include "access.h"

using namespace std;


    struct _booToken {
        struct _booToken* previous;
        struct _booToken* next;
        char* value;
        long start;
        long lengh;
    };

    typedef struct _booToken booToken;
    typedef booToken* booTokenPtr;

    booTokenPtr addToken(booTokenPtr& __token, long& __start, string& __str) {
        booTokenPtr token = (booTokenPtr) malloc(sizeof (booToken));
        token->value = strdup(__str.c_str());
        token->start = __start;
        token->lengh = __str.length();
        token->previous = __token;
        token->next = NULL;
        if (__token != NULL) __token->next = token;
        __token = token;
        __start += __str.length();
        __str.clear();
        return token;
    }

    booTokenPtr getTokens(
            FILE *file,
            int ex = -1,
            void (*func)(const booTokenPtr token) = NULL
            ) {
        booTokenPtr response = NULL;
        booTokenPtr posToken = NULL;
        booTokenPtr auxToken = NULL;
        string str;
        int c = getc(file);
        long pos = 0;
        int count = 0;
        int estado = 0;
        int contador = 0;
        while (1) {
            str.clear();
            switch (estado) {
                case 0:
                    if (c != ' ' && c != '\n' && c != ex) {
                        while (c != ' ' && c != '\n' && c != ex) {
                            str += c;
                            c = getc(file);
                        }
                        estado = 1;
                    } else {
                        pos++;
                        c = getc(file);
                    }
                    break;
                case 1:
                    if (c == '[') {
                        while (c != ']' && contador < 13 && c != ex) {
                            if (contador++ > 0 && contador < 13) str += c;
                            c = getc(file);
                        }
                        contador = 0;
                        c = getc(file);
                        estado = 2;
                    } else {
                        pos++;
                        c = getc(file);
                    }
                    break;
                case 2:
                    if (c == '"') {
                        if (++contador == 2) {
                            estado = 4;
                            contador = 0;
                        }
                    }
                    pos++;
                    c = getc(file);
                    break;
                case 3:
                    if (c == ' ') {
                        if (++contador == 2) {
                            estado = 4;
                            contador = 0;
                        }
                    }
                    pos++;
                    c = getc(file);
                    break;
                case 4:
                    if (c != ' ' && c != '\n' && c != ex) {
                        while (c != ' ' && c != '\n' && c != ex) {
                            str += c;
                            c = getc(file);
                        }
                        estado = 5;
                    } else {
                        pos++;
                        c = getc(file);
                    }
                    break;
                case 5:
                    if (c == '"') {
                        if (++contador == 3) {
                            estado = 6;
                            contador = 0;
                        }
                    }
                    pos++;
                    c = getc(file);
                    break;
                case 6:
                    if (c != '"' && c != '\n' && c != ex) {
                        while (c != '"' && c != '\n' && c != ex) {
                            str += c;
                            c = getc(file);
                        }
                        pos++;
                        c = getc(file);
                        estado = 0;
                    } else {
                        pos++;
                        c = getc(file);
                    }
                    break;
                default:
                    break;
            }

            if (str.length() != 0) {
                if(estado == 2){
                }
                auxToken = addToken(posToken, pos, str);
                pos += str.length();
                if (func != NULL) func(auxToken);
            }
            if (response == NULL) response = auxToken;
            if (c == ex) break;
        }
        cout << endl;
        return response;
    }
    void imprimir(const booTokenPtr token) {
        if (token == NULL) return;
        cout << token->value << endl;
    }

#endif	/* BOO_H */

