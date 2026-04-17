#include <iostream>
using namespace std;

class LogEntry {
private:
    // Componentes de fecha y hora del registro.
    int sec, min, hr, day, month, attacks;

    // Datos asociados al evento.
    string ip, reason;

public:
    // Constructor por defecto: inicializa todos los campos vacios o en cero.
    LogEntry()
        : sec(0),
          min(0),
          hr(0),
          day(0),
          month(0),
          attacks(0),
          ip(""),
          reason("") {}

    // Constructor completo para crear una entrada con toda la informacion.
    LogEntry(int _s, int _min, int _h, int _d, int _m, int _n, const string& _r, const string& _nm)
       : sec(_s),
         min(_min),
         hr(_h),
         day(_d),
         month(_m),
         attacks(_n),
         ip(_r), reason(_nm) {}

    // Constructor auxiliar para comparaciones por fecha y hora.
    LogEntry(int _s, int _min, int _h, int _d, int _m)
        : sec(_s),
          min(_min),
          hr(_h),
          day(_d),
          month(_m),
          attacks(0),
          ip(""),
          reason("") {}

    // Getters de los atributos del registro.
    int getSec() const { return sec; }
    int getMin() const { return min; }
    int getHour() const { return hr; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getAttacks() const { return attacks; }
    string getReason() const { return reason; }
    string getIp() const { return ip; }

    // Compara dos registros en orden cronologico.
    // Regresa valores negativos si este registro es menor,
    // positivos si es mayor y 0 si coinciden en tiempo.
    int compareTime(const LogEntry& other) const {
        if (month != other.month) {return (month < other.month) ? (-2) : (2);}
        if (day   != other.day)   {return (day   < other.day)   ? (-3) : (3);}
        if (hr    != other.hr)    {return (hr    < other.hr)    ? (-4) : (4);}
        if (min   != other.min)   {return (min   < other.min)   ? (-5) : (5);}
        if (sec   != other.sec)   {return (sec   < other.sec)   ? (-6) : (6);}
        return 0;
    }

    // Operadores de comparacion basados en compareTime.
    bool operator == (const LogEntry& other) const {
        return (compareTime(other) == 0);
    }
    bool operator > (const LogEntry& other) const {
        return (compareTime(other) > 0);
    }
    bool operator < (const LogEntry& other) const {
        return (compareTime(other) < 0);
    }
    bool operator >= (const LogEntry& other) const {
        return (compareTime(other) >= 0);
    }
    bool operator <= (const LogEntry& other) const {
        return (compareTime(other) <= 0);
    }

    // Permite imprimir una entrada en el formato usado por el programa.
    friend ostream& operator<<(ostream& os, const LogEntry& log){
        string mes;

        if (log.getMonth() == 1) mes = "ENE";
        if (log.getMonth() == 2) mes = "FEB";
        if (log.getMonth() == 3) mes = "MAR";
        if (log.getMonth() == 4) mes = "ABR";
        if (log.getMonth() == 5) mes = "MAY";
        if (log.getMonth() == 6) mes = "JUN";
        if (log.getMonth() == 7) mes = "JUL";
        if (log.getMonth() == 8) mes = "AGO";
        if (log.getMonth() == 9) mes = "SEP";
        if (log.getMonth() == 10) mes = "OCT";
        if (log.getMonth() == 11) mes = "NOV";
        if (log.getMonth() == 12) mes = "DIC";

        os << mes << " " << log.getDay() << " " << log.getHour() << ":" << log.getMin() << ":" << log.getSec()
           << " R:" << log.getIp() << "O:" << log.getReason() << "(" << log.getAttacks() << ")";

        return os;
    }
};
