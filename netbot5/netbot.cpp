#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DomainData {
private:
    string domain;
    int accesses;
    set<string> ips;

public:
    DomainData() {
        domain = "";
        accesses = 0;
    }

    DomainData(string _domain, string ip) {
        domain = _domain;
        accesses = 1;
        ips.insert(ip);
    }

    string getDomain() const {
        return domain;
    }

    int getAccesses() const {
        return accesses;
    }

    int getUniqueIPCount() const {
        return ips.size();
    }

    set<string> getIPs() const {
        return ips;
    }

    void addAccess(string ip) {
        accesses++;
        ips.insert(ip);
    }

    void display() const {
        vector<string> ipList(ips.begin(), ips.end());
        sort(ipList.begin(), ipList.end());

        cout << "Dominio/destino: " << domain << endl;
        cout << "Numero de accesos: " << accesses << endl;
        cout << "Numero de IPs unicas: " << ipList.size() << endl;
        cout << "Lista de IPs:" << endl;

        for (int i = 0; i < ipList.size(); i++) {
            cout << "  " << i + 1 << ". " << ipList[i] << endl;
        }
    }
};

class HashTable {
private:
    int bucketCount;
    int collisions;
    int uniqueDomains;
    vector<vector<DomainData> > table;

    // Funcion hash propia para convertir el dominio en indice.
    // Complejidad: O(k), donde k es la longitud del dominio.
    int hashFunction(string key) const {
        unsigned long long value = 0;
        int prime = 37;

        for (int i = 0; i < key.length(); i++) {
            value = (value * prime + static_cast<unsigned char>(key[i])) % bucketCount;
        }

        return static_cast<int>(value);
    }

public:
    HashTable(int buckets) {
        bucketCount = buckets;
        collisions = 0;
        uniqueDomains = 0;
        table.resize(bucketCount);
    }

    // Inserta o actualiza un dominio usando encadenamiento.
    // Complejidad promedio: O(1). Peor caso: O(n).
    void insertAccess(string domain, string ip) {
        int index = hashFunction(domain);

        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i].getDomain() == domain) {
                table[index][i].addAccess(ip);
                return;
            }
        }

        if (!table[index].empty()) {
            collisions++;
        }

        table[index].push_back(DomainData(domain, ip));
        uniqueDomains++;
    }

    // Busca el resumen asociado a un dominio.
    // Complejidad promedio: O(1). Peor caso: O(n).
    bool searchDomain(string domain, DomainData& result) const {
        int index = hashFunction(domain);

        for (int i = 0; i < table[index].size(); i++) {
            if (table[index][i].getDomain() == domain) {
                result = table[index][i];
                return true;
            }
        }

        return false;
    }

    // Metodo pedido por la evidencia: dado un dominio, despliega su valor asociado.
    // Complejidad promedio: O(1), mas O(u log u) al imprimir IPs.
    void displayDomain(string domain) const {
        DomainData result;

        if (searchDomain(domain, result)) {
            result.display();
        } else {
            cout << "No se encontro el dominio/destino: " << domain << endl;
        }
    }

    // Muestra la tabla hash completa por cubeta.
    // Complejidad: O(b + n), donde b es cubetas y n dominios.
    void displayHash() const {
        for (int i = 0; i < bucketCount; i++) {
            cout << i;

            for (int j = 0; j < table[i].size(); j++) {
                cout << " --> " << table[i][j].getDomain()
                     << " (" << table[i][j].getAccesses() << " accesos)";
            }

            cout << endl;
        }
    }

    // Muestra estadisticas generales.
    // Complejidad: O(1).
    void displayStats(int totalRecords) const {
        double loadFactor = static_cast<double>(uniqueDomains) / bucketCount;

        cout << fixed << setprecision(3);
        cout << "Registros leidos: " << totalRecords << endl;
        cout << "Buckets: " << bucketCount << endl;
        cout << "Dominios/destinos unicos: " << uniqueDomains << endl;
        cout << "Colisiones: " << collisions << endl;
        cout << "Factor de carga: " << loadFactor << endl;
    }

    // Muestra los dominios con mas accesos.
    // Complejidad: O(n log n).
    void displayTopDomains(int limit) const {
        vector<DomainData> domains;

        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                domains.push_back(table[i][j]);
            }
        }

        sort(domains.begin(), domains.end(), [](const DomainData& a, const DomainData& b) {
            if (a.getAccesses() != b.getAccesses()) {
                return a.getAccesses() > b.getAccesses();
            }

            if (a.getUniqueIPCount() != b.getUniqueIPCount()) {
                return a.getUniqueIPCount() > b.getUniqueIPCount();
            }

            return a.getDomain() < b.getDomain();
        });

        cout << "Top " << limit << " dominios/destinos con mas accesos:" << endl;
        for (int i = 0; i < domains.size() && i < limit; i++) {
            cout << i + 1 << ". " << domains[i].getDomain()
                 << " - accesos: " << domains[i].getAccesses()
                 << ", IPs unicas: " << domains[i].getUniqueIPCount() << endl;
        }
    }

    // Muestra las 4 preguntas de la tarjeta de mision con respuestas.
    // Complejidad: O(n log n), donde n es el numero de dominios.
    void displayMissionQuestions(int totalRecords) const {
        vector<DomainData> domains;
        int topTraffic = 0;

        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                domains.push_back(table[i][j]);
            }
        }

        sort(domains.begin(), domains.end(), [](const DomainData& a, const DomainData& b) {
            if (a.getAccesses() != b.getAccesses()) {
                return a.getAccesses() > b.getAccesses();
            }

            if (a.getUniqueIPCount() != b.getUniqueIPCount()) {
                return a.getUniqueIPCount() > b.getUniqueIPCount();
            }

            return a.getDomain() < b.getDomain();
        });

        cout << fixed << setprecision(2);
        cout << endl;
        cout << "PREGUNTAS A RESPONDER - OPERACION MEDIANOCHE" << endl;
        cout << endl;

        cout << "1. Cuales son los top-5 dominios por numero de accesos?" << endl;
        cout << "   Que porcentaje del trafico total representan?" << endl;
        for (int i = 0; i < domains.size() && i < 5; i++) {
            double percentage = 0.0;

            if (totalRecords > 0) {
                percentage = (static_cast<double>(domains[i].getAccesses()) / totalRecords) * 100.0;
            }

            topTraffic += domains[i].getAccesses();

            cout << "   " << i + 1 << ". " << domains[i].getDomain()
                 << " - accesos: " << domains[i].getAccesses()
                 << ", IPs unicas: " << domains[i].getUniqueIPCount()
                 << ", porcentaje: " << percentage << "%" << endl;
        }

        if (totalRecords > 0) {
            cout << "   En conjunto representan "
                 << (static_cast<double>(topTraffic) / totalRecords) * 100.0
                 << "% del trafico total." << endl;
        }

        cout << endl;
        cout << "2. Por que una tabla hash es eficiente para consultas O(1) por dominio?" << endl;
        cout << "   La tabla hash calcula directamente la cubeta donde debe estar el dominio,"
             << " por eso la busqueda promedio es O(1). Un BST balanceado requiere comparar"
             << " contra varios nodos y su busqueda cuesta O(log n). Para consultas exactas"
             << " por dominio, hash es mas directo; el BST conviene mas cuando se necesita"
             << " mantener las llaves ordenadas." << endl;

        cout << endl;
        cout << "3. Que funcion hash elegiste y como validaste que distribuye bien las llaves?" << endl;
        cout << "   Use una funcion polinomial: value = value * 37 + caracter, aplicando modulo"
             << " con el numero de buckets. La valide observando el numero de colisiones,"
             << " el factor de carga y la distribucion visible con la opcion de mostrar"
             << " la tabla hash completa." << endl;

        cout << endl;
        cout << "4. Como manejaste las colisiones y por que?" << endl;
        cout << "   Use encadenamiento: cada bucket guarda un vector con los dominios que caen"
             << " en el mismo indice. Es una opcion clara para esta evidencia porque permite"
             << " insertar aunque haya colisiones y funciona bien con un factor de carga bajo."
             << " En esta ejecucion el factor de carga fue "
             << static_cast<double>(uniqueDomains) / bucketCount
             << " y hubo " << collisions << " colisiones." << endl;
    }
};

class LogReader {
private:
    string filename;

    // Convierte una IP completa en dominio organizacional por dos octetos.
    // Ejemplo: 192.168.10.25 -> 192.168
    string getDomainFromIP(string ip) const {
        int dots = 0;

        for (int i = 0; i < ip.length(); i++) {
            if (ip[i] == '.') {
                dots++;

                if (dots == 2) {
                    return ip.substr(0, i);
                }
            }
        }

        return ip;
    }

    // Extrae IP origen y dominio/destino de una linea con formato:
    // Mes Dia Hora IP_origen Dominio_o_IP_destino Mensaje...
    // Complejidad: O(1) por registro.
    bool getDataFromLine(string line, string& ip, string& domain) const {
        string month;
        string day;
        string time;
        string targetIP;
        stringstream ss(line);

        if (ss >> month >> day >> time >> ip >> targetIP) {
            domain = getDomainFromIP(targetIP);
            return true;
        }

        return false;
    }

public:
    LogReader(string _filename) {
        filename = _filename;
    }

    // Lee el archivo y construye la tabla hash.
    // Complejidad promedio: O(r), donde r es el numero de registros.
    bool buildHashTable(HashTable& hashTable, int& totalRecords) const {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "No se pudo abrir el archivo " << filename << endl;
            return false;
        }

        string line;
        totalRecords = 0;

        while (getline(file, line)) {
            string ip;
            string domain;

            if (getDataFromLine(line, ip, domain)) {
                hashTable.insertAccess(domain, ip);
                totalRecords++;
            }
        }

        file.close();
        return true;
    }
};

void menu() {
    cout << endl;
    cout << "Menu" << endl;
    cout << "1. Consultar dominio/destino" << endl;
    cout << "2. Mostrar top dominios/destinos" << endl;
    cout << "3. Mostrar tabla hash completa" << endl;
    cout << "4. Mostrar estadisticas" << endl;
    cout << "5. Ver preguntas de la tarjeta de mision" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

int main() {
    HashTable hashTable(211);
    LogReader reader("bitacora.txt");
    int totalRecords = 0;

    if (!reader.buildHashTable(hashTable, totalRecords)) {
        return 1;
    }

    cout << "Actividad 5.2 - Tabla hash por dominio" << endl;
    hashTable.displayStats(totalRecords);
    cout << endl;
    hashTable.displayTopDomains(5);

    string option;

    do {
        menu();
        getline(cin, option);

        if (option == "1") {
            string domain;

            cout << "Dominio/destino a consultar: ";
            getline(cin, domain);
            hashTable.displayDomain(domain);
        } else if (option == "2") {
            hashTable.displayTopDomains(10);
        } else if (option == "3") {
            hashTable.displayHash();
        } else if (option == "4") {
            hashTable.displayStats(totalRecords);
        } else if (option == "5") {
            hashTable.displayMissionQuestions(totalRecords);
        } else if (option != "0") {
            cout << "Opcion invalida." << endl;
        }
    } while (option != "0");

    return 0;
}
