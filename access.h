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

class Peticion {
private:
    string ip;
    string fecha;
    string estado;
    string so;

public:
    //constructor

    Peticion(string linea) {
        //char *str = strdup(linea.c_str());
        parseLog(linea);
    }

    //destructor

    ~Peticion() {
    }

    //accesadores

    string getIp() {
        return ip;
    }

    string getFecha() {
        return fecha;
    }

    string getSo() {
        return so;
    }

    string getEstado() {
        return estado;
    }

    //mutadores

    void setIp(string _ip) {
        ip = _ip;
    }

    void setFecha(string _fecha) {
        fecha = _fecha;
    }

    void setSo(string _so) {
        so = _so;
    }

    void setEstado(string _estado) {
        estado = _estado;
    }

    //metodos de la clase

    string convertirMes(string month) {
        if (month == "Jan")return "01";
        else if (month == "Feb")return "02";
        else if (month == "Mar")return "03";
        else if (month == "Apr")return "04";
        else if (month == "May")return "05";
        else if (month == "Jun")return "06";
        else if (month == "Jul")return "07";
        else if (month == "Aug")return "08";
        else if (month == "Sep")return "09";
        else if (month == "Oct")return "10";
        else if (month == "Nov")return "11";
        else if (month == "Dec")return "12";
    }

    string parseFecha(string f) {

        string _fecha = f.substr(1, 11);
        string year = _fecha.substr(7, 4);
        string month = _fecha.substr(3, 3);
        string day = _fecha.substr(0, 2);
        _fecha = year + "-" + convertirMes(month) + "-" + day;
        return _fecha;
    }

    void parseLog(string log) {
        string aux;
        string aux2;
        int pos = log.find_first_of(" ");

        //ip
        setIp(log.substr(0, pos));
        aux = log.substr(pos + 1, log.size() - ip.size() - 1);
        pos = aux.find_first_of(" ");
        aux2 = aux.substr(0, pos);
        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);
        pos = aux.find_first_of(" ");
        aux2 = aux.substr(0, pos);
        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);
        pos = aux.find_first_of(" ");
        aux2 = aux.substr(0, pos);
        //fecha
        setFecha(parseFecha(aux2));
        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);
        pos = aux.find_first_of(" ");
        aux2 = aux.substr(0, pos);
        aux = aux.substr(pos + 2, log.size() - aux2.size() - 1);
        pos = aux.find_first_of("\"");
        aux2 = aux.substr(0, pos);
        aux = aux.substr(pos + 2, log.size() - aux2.size() - 1);
        pos = aux.find_first_of(" ");
        aux2 = aux.substr(0, pos);
        //estado
        setEstado(aux2);
        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);

        pos = aux.find_first_of("\"");
        aux2 = aux.substr(0, pos);

        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);
        pos = aux.find_first_of("\"");
        aux2 = aux.substr(0, pos);

        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);
        pos = aux.find_first_of("\"");
        aux2 = aux.substr(0, pos);
        aux = aux.substr(pos + 1, log.size() - aux2.size() - 1);
        pos = aux.find_first_of("\"");
        aux2 = aux.substr(0, pos);
        setSo(aux2);
    }


};

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

