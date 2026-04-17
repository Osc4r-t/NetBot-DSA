#include "netbot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//Convierte los strings de meses a int
int monthToInt(string m){
    if (m == "ene"){
        return 1;
    } else if (m == "Feb"){
        return 2;
    } else if (m == "Mar"){
        return 3;
    } else if (m == "Abr"){
        return 4;
    } else if (m == "May"){
        return 5;
    } else if (m == "Jun"){
        return 6;
    } else if (m == "Jul"){
        return 7;
    } else if (m == "Ago"){
        return 8;
    } else if (m == "Sep"){
        return 9;
    } else if (m == "Oct"){
        return 10;
    } else if (m == "Nov"){
        return 11;
    } else if (m == "Dic"){
        return 12;
    }
    return 0;
}

void pause(){
    cout << "Press enter to continue.";
    cin.ignore();
    cin.get();
}




void loadLogEntryData(const string& filename, LogEntry** out, int capacity, int &loaded) {
    ifstream file(filename);
    string line;
    int i = 0;

    while (i < capacity && getline(file, line)){
        stringstream ss(line);
        string s, min, hr, day, month, ip, port, reason;

        // obtiene cada elemento del log
        getline(ss, month,' ');
        getline(ss, day,' ');
        getline(ss, hr, ':');
        getline(ss, min, ':');
        getline(ss, s,' ');
        getline(ss, ip, ':');
        getline(ss, port,' ');
        getline(ss, reason);

        // convierte strings a numeros
        int _s   = stoi(s);
        int _min = stoi(min);
        int _hr  = stoi(hr);
        int _day = stoi(day);
        int _month = monthToInt(month);
        int _port = stoi(port);

        // crea y guarda puntero
        out[i] = new LogEntry(_s,_min,_hr,_day,_month,_port,ip,reason);
        ++i;
    }

    file.close();
    loaded = i;

    // inicializa el resto a nullptr
    for (int j = loaded; j < capacity; ++j) out[j] = nullptr;
}

// ---------- MERGE SORT sobre arreglo de punteros (LogEntry**) ----------
// complejidad 0(nlogn)
void merge(LogEntry** A, int L, int M, int R, bool asc = true){
    int s1 = M - L + 1;  // tamaño izquierda
    int s2 = R - M;      // tamaño derecha

    // temporales (arreglos de punteros)
    LogEntry** parteL = new LogEntry*[s1];
    LogEntry** parteR = new LogEntry*[s2];

    // copiar mitades
    for (int i = 0; i < s1; ++i) parteL[i] = A[L + i];
    for (int j = 0; j < s2; ++j) parteR[j] = A[M + 1 + j];

    int i = 0, j = 0, k = L;

    // fusionar comparando los objetos apuntados
    while (i < s1 && j < s2){
        bool takeLeft = asc ? (*parteL[i] <= *parteR[j])
                            : (*parteL[i] >= *parteR[j]);
        if (takeLeft) {
            A[k++] = parteL[i++];
        } else {
            A[k++] = parteR[j++];
        }
    }
    while (i < s1) A[k++] = parteL[i++];
    while (j < s2) A[k++] = parteR[j++];

    delete[] parteL;
    delete[] parteR;
}


void mergeSort(LogEntry** A, int L, int R, bool asc = true) {
    if (L >= R) return;
    int M = L + (R - L) / 2;
    mergeSort(A, L,     M, asc);
    mergeSort(A, M + 1, R, asc);
    merge(A, L, M, R, asc);
}


// complejidad o(logn)
int binarySearch(LogEntry** A, int n, const LogEntry& x){
    int lo = 0, hi = n;           // intervalo [lo, hi)
    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        if (*A[mid] < x) lo = mid + 1;
        else             hi = mid;
    }
    return lo; // posición de inserción (o primer >= x)
}

void mergeByAttacks(LogEntry** A, int L, int M, int R, bool asc = true) {
    int s1 = M - L + 1;
    int s2 = R - M;

    LogEntry** parteL = new LogEntry*[s1];
    LogEntry** parteR = new LogEntry*[s2];

    for (int i = 0; i < s1; ++i) parteL[i] = A[L + i];
    for (int j = 0; j < s2; ++j) parteR[j] = A[M + 1 + j];

    int i = 0, j = 0, k = L;

    while (i < s1 && j < s2) {
        bool takeLeft = asc ? (parteL[i]->getAttacks() <= parteR[j]->getAttacks())
                            : (parteL[i]->getAttacks() >= parteR[j]->getAttacks());
        if (takeLeft) {
            A[k++] = parteL[i++];
        } else {
            A[k++] = parteR[j++];
        }
    }

    while (i < s1) A[k++] = parteL[i++];
    while (j < s2) A[k++] = parteR[j++];

    delete[] parteL;
    delete[] parteR;
}

void mergeSortByAttacks(LogEntry** A, int L, int R, bool asc = true) {
    if (L >= R) return;
    int M = L + (R - L) / 2;
    mergeSortByAttacks(A, L, M, asc);
    mergeSortByAttacks(A, M + 1, R, asc);
    mergeByAttacks(A, L, M, R, asc);
}

int main(){

    const int n = 3350;       // capacidad
    LogEntry* _orders[n];         // arreglo de PUNTEROS a LogEntry
    int loaded = 0;            // cuántos cargamos

    loadLogEntryData("bitacora_junio.txt", _orders, n, loaded);

    // ordena si hay datos
    if (loaded > 0) {
        mergeSort(_orders, 0, loaded - 1, true);
    }

    // Crear un archivo con las ordenes en orden
    ofstream archivo("ordenado.txt");
    if (archivo){
        for (int i = 0; i < loaded; ++i) {
            archivo << *_orders[i] << '\n';
        }
        archivo.close();
    }

    // Le pregunta al usuario el rango que desea buscar
    int m,d,h,minute,s;
    cout << "\n¿Qué rango de fechas desea buscar?\nIngrese fecha inicial (M D H Min S): ";
    cin >> m >> d >> h >> minute >> s;
    LogEntry x1 = LogEntry(s,minute,h,d,m);
    int rango_bajo = binarySearch(_orders, loaded, x1);

    cout << "Ingrese fecha final (M D H Min S): ";
    cin >> m >> d >> h >> minute >> s;
    LogEntry x2 = LogEntry(s,minute,h,d,m);
    int rango_alto = binarySearch(_orders, loaded, x2);

    if (rango_bajo > rango_alto) {
        int tmp = rango_bajo; rango_bajo = rango_alto; rango_alto = tmp;
    }
    if (rango_bajo < 0) rango_bajo = 0;
    if (rango_alto > loaded) rango_alto = loaded;




    cout << "\n--- Resultados en rango ordenados por ataques ---\n";

    int size = rango_alto - rango_bajo;

    /* crear arreglo temporal */
    LogEntry** resultados = new LogEntry*[size];

    /* copiar los elementos del rango */
    for (int i = 0; i < size; ++i){
        resultados[i] = _orders[rango_bajo + i];
    }

    /* ordenar por ataques (descendente) */
    mergeSortByAttacks(resultados, 0, size - 1, false);

    /* imprimir */
    for (int i = 0; i < size; ++i){
        cout << *resultados[i] << '\n';
    }

    delete[] resultados;

    bool guardar;
    cout << "\n¿Deseas guardas los datos (1/0)? ";
    cin >> guardar;
    if (guardar) {
        ofstream archivo2("busqueda.txt");
        if (archivo2){
            for (int i = rango_alto-1; i <= rango_bajo; --i) {
                archivo2 << *_orders[i] << '\n';
            }
            archivo2.close();
        }
    }

    // borra los objetos creados 
    for (int i = 0; i < loaded; ++i) {
        delete _orders[i];
        _orders[i] = nullptr;
    }

    return 0;
}