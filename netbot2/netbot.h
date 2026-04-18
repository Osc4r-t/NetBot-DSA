#include <iostream>
using namespace std;

class LogEntry {
private:
    // Componentes de fecha y hora del registro.
    int sec, min, hr, day, month, attacks, ip;

    // Datos asociados al evento.
    string reason;

public:
    // Constructor por defecto: inicializa todos los campos vacios o en cero.
    LogEntry()
        : sec(0),
          min(0),
          hr(0),
          day(0),
          month(0),
          attacks(0),
          ip(0),
          reason("") {}

    // Constructor completo para crear una entrada con toda la informacion.
    LogEntry(int _s, int _min, int _h, int _d, int _m, int _r, const string& _nm)
       : sec(_s),
         min(_min),
         hr(_h),
         day(_d),
         month(_m),
         attacks(0),
         ip(_r), reason(_nm) {}

    // Getters de los atributos del registro.
    int getSec() const { return sec; }
    int getMin() const { return min; }
    int getHour() const { return hr; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getAttacks() const { return attacks; }
    string getReason() const { return reason; }
    int getIp() const { return ip; }

    // Compara dos registros en orden cronologico.
    // Regresa negativo si este registro va antes,
    // positivo si va despues y 0 si coinciden en fecha y hora.
    int compareTime(const LogEntry& other) const {
        if (month != other.month) { return (month < other.month) ? -1 : 1; }
        if (day   != other.day)   { return (day   < other.day)   ? -1 : 1; }
        if (hr    != other.hr)    { return (hr    < other.hr)    ? -1 : 1; }
        if (min   != other.min)   { return (min   < other.min)   ? -1 : 1; }
        if (sec   != other.sec)   { return (sec   < other.sec)   ? -1 : 1; }
        return 0;
    }

    // Compara dos registros por la IP almacenada como entero.
    int compareIP(const LogEntry& other) const {
        if (ip != other.ip) { return (ip < other.ip) ? -1 : 1; }
        return 0;
    }

    // Operadores de comparacion basados en IP.
    bool operator == (const LogEntry& other) const {
        return (compareIP(other) == 0);
    }
    bool operator > (const LogEntry& other) const {
        return (compareIP(other) > 0);
    }
    bool operator < (const LogEntry& other) const {
        return (compareIP(other) < 0);
    }
    bool operator >= (const LogEntry& other) const {
        return (compareIP(other) >= 0);
    }
    bool operator <= (const LogEntry& other) const {
        return (compareIP(other) <= 0);
    }

    // Permite imprimir una entrada en el formato usado por el programa.
    friend ostream& operator<<(ostream& os, const LogEntry& log){
        string mes;
        int ip1 = abs(log.getIp() / (256 * 256 * 256));
        int ip2 = abs((log.getIp() / (256 * 256)) % 256);
        int ip3 = abs((log.getIp() / 256) % 256);
        int ip4 = abs(log.getIp() % 256);

        if (log.getMonth() == 1) mes = "Jan";
        if (log.getMonth() == 2) mes = "Feb";
        if (log.getMonth() == 3) mes = "Mar";
        if (log.getMonth() == 4) mes = "Apr";
        if (log.getMonth() == 5) mes = "May";
        if (log.getMonth() == 6) mes = "Jun";
        if (log.getMonth() == 7) mes = "Jul";
        if (log.getMonth() == 8) mes = "Aug";
        if (log.getMonth() == 9) mes = "Sep";
        if (log.getMonth() == 10) mes = "Oct";
        if (log.getMonth() == 11) mes = "Nov";
        if (log.getMonth() == 12) mes = "Dec";

        os << mes << " " << log.getDay() << " " << log.getHour() << ":" << log.getMin() << ":" << log.getSec()
           << " " << ip1 << "." << ip2 << "." << ip3 << "." << ip4
           << " " << log.getReason();

        return os;
    }
};
