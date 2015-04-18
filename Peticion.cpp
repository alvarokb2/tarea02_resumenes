#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        parseLog(linea);
    }

    //destructor
    ~Peticion(){
        
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
    

    
    void parseLog(string log) {
        char* str = strdup(log.c_str());
        string aux;
        ip = strtok(str, " ");
        aux = strtok(NULL, " ");
        aux = strtok(NULL, " ");
        fecha = parseFecha(strtok(NULL, " "));
        aux = strtok(NULL, " ");
        aux = strtok(NULL, " ");
        aux = strtok(NULL, " ");
        aux = strtok(NULL, " ");
        estado = strtok(NULL, " ");

        aux = strtok(NULL, "\"");
        aux = strtok(NULL, "\"");
        aux = strtok(NULL, "\"");
        so = strtok(NULL, "\"");
        
        free(str);
    }

    string parseFecha(string f) {

        string _fecha = f.substr(1, 11);
        string year = _fecha.substr(7, 4);
        string month = _fecha.substr(3, 3);
        string day = _fecha.substr(0, 2);
        _fecha = year+"-"+convertirMes(month)+"-"+day;
        return _fecha;
    }

    string convertirMes(string month){
        if(month == "Jan")return "01";
        else if(month == "Feb")return "02";
        else if(month == "Mar")return "03";
        else if(month == "Apr")return "04";
        else if(month == "May")return "05";
        else if(month == "Jun")return "06";
        else if(month == "Jul")return "07";
        else if(month == "Aug")return "08";
        else if(month == "Sep")return "09";
        else if(month == "Oct")return "10";
        else if(month == "Nov")return "11";
        else if(month == "Dec")return "12";
    }
};
