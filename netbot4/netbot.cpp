#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Operacion Medianoche - Fase 4: Analisis con grafos dirigidos.
// Cada nodo representa una IP y cada arco representa un acceso origen -> destino.
class Graph {
private:
    map<string, int> ipToIndex;
    vector<string> indexToIP;
    vector<vector<int> > adjacencyList;
    int totalEdges;
    // Registra una IP si aun no existe en el grafo.
    // Complejidad: O(log n), donde n es el total de IPs unicas.
    int getOrCreateNode(const string& ip) {
        map<string, int>::iterator it = ipToIndex.find(ip);

        if (it != ipToIndex.end()) {
            return it->second;
        }

        int newIndex = indexToIP.size();
        ipToIndex[ip] = newIndex;
        indexToIP.push_back(ip);
        adjacencyList.push_back(vector<int>());
        return newIndex;
    }

    // Funcion auxiliar para DFS recursivo usando lista de adyacencia.
    // Complejidad: O(n + m), donde n es IPs unicas y m es arcos.
    void dfsRecursive(int node, vector<bool>& visited, int& printed, int limit) const {
        if (printed >= limit) {
            return;
        }

        visited[node] = true;
        cout << indexToIP[node] << " ";
        printed++;

        for (int i = 0; i < adjacencyList[node].size(); i++) {
            int neighbor = adjacencyList[node][i];

            if (!visited[neighbor]) {
                dfsRecursive(neighbor, visited, printed, limit);
            }
        }
    }

public:
    // Complejidad: O(1).
    Graph() : totalEdges(0) {}

    // Inserta un arco dirigido de sourceIP hacia targetIP.
    // Complejidad: O(log n).
    void insertArc(const string& sourceIP, const string& targetIP) {
        int source = getOrCreateNode(sourceIP);
        int target = getOrCreateNode(targetIP);

        adjacencyList[source].push_back(target);
        totalEdges++;
    }

    // Regresa el fan-out de un nodo, contado como total de accesos salientes.
    // Complejidad: O(1).
    int calculateFanOut(int node) const {
        return adjacencyList[node].size();
    }

    // Regresa la cantidad de destinos diferentes a los que apunta una IP.
    // Complejidad: O(k log k), donde k es el fan-out del nodo.
    int calculateUniqueTargets(int node) const {
        set<int> uniqueTargets;

        for (int i = 0; i < adjacencyList[node].size(); i++) {
            uniqueTargets.insert(adjacencyList[node][i]);
        }

        return uniqueTargets.size();
    }

    // Complejidad: O(1).
    int nodeCount() const {
        return indexToIP.size();
    }

    // Complejidad: O(1).
    int edgeCount() const {
        return totalEdges;
    }

    // Complejidad: O(1).
    string getIP(int node) const {
        return indexToIP[node];
    }

    // Busca el indice de una IP.
    // Complejidad: O(log n).
    int findNode(const string& ip) const {
        map<string, int>::const_iterator it = ipToIndex.find(ip);

        if (it == ipToIndex.end()) {
            return -1;
        }

        return it->second;
    }

    // Imprime una muestra de la lista de adyacencia para validar la construccion.
    // Complejidad: O(n + m) en el peor caso.
    void printAdjacencySample(int limitNodes, int limitNeighbors) const {
        int printedNodes = 0;

        cout << "Muestra de lista de adyacencia:" << endl;
        for (int i = 0; i < adjacencyList.size() && printedNodes < limitNodes; i++) {
            if (adjacencyList[i].empty()) {
                continue;
            }

            cout << indexToIP[i] << " -> ";
            for (int j = 0; j < adjacencyList[i].size() && j < limitNeighbors; j++) {
                cout << indexToIP[adjacencyList[i][j]];

                if (j + 1 < adjacencyList[i].size() && j + 1 < limitNeighbors) {
                    cout << " -> ";
                }
            }

            if (adjacencyList[i].size() > limitNeighbors) {
                cout << " -> ...";
            }

            cout << " /" << endl;
            printedNodes++;
        }
    }

    // Imprime el fan-out de cada nodo que tenga conexiones salientes.
    // Complejidad: O(n).
    void printFanOutByNode() const {
        cout << "Fan-out por nodo:" << endl;

        for (int i = 0; i < adjacencyList.size(); i++) {
            if (!adjacencyList[i].empty()) {
                cout << indexToIP[i] << " - fan-out: " << calculateFanOut(i)
                     << ", destinos unicos: " << calculateUniqueTargets(i) << endl;
            }
        }
    }

    // Ordena e imprime las IPs con mayor fan-out.
    // Complejidad: O(n log n + suma(k log k)).
    vector<pair<int, int> > getFanOutRanking() const {
        vector<pair<int, int> > ranking;

        for (int i = 0; i < adjacencyList.size(); i++) {
            if (!adjacencyList[i].empty()) {
                ranking.push_back(make_pair(calculateFanOut(i), i));
            }
        }

        sort(ranking.begin(), ranking.end(),
             [this](const pair<int, int>& left, const pair<int, int>& right) {
                 if (left.first != right.first) {
                     return left.first > right.first;
                 }

                 return indexToIP[left.second] < indexToIP[right.second];
             });

        return ranking;
    }

    // Ordena e imprime las IPs con mayor fan-out.
    // Complejidad: O(n log n + suma(k log k)).
    void printTopFanOut(int limit) const {
        vector<pair<int, int> > ranking = getFanOutRanking();

        cout << "Top " << limit << " IPs con mayor fan-out:" << endl;
        for (int i = 0; i < ranking.size() && i < limit; i++) {
            int node = ranking[i].second;

            cout << i + 1 << ". " << indexToIP[node]
                 << " - fan-out: " << ranking[i].first
                 << ", destinos unicos: " << calculateUniqueTargets(node) << endl;
        }

        if (!ranking.empty()) {
            int botMaster = ranking[0].second;

            cout << endl;
            cout << "IP presumiblemente bot master: " << indexToIP[botMaster] << endl;
            cout << "Justificacion: es el nodo con mayor cantidad de conexiones salientes"
                 << " registradas en la bitacora." << endl;
        }
    }

    // Imprime las respuestas solicitadas en la tarjeta de mision.
    // Complejidad: O(n log n + suma(k log k)).
    void printMissionAnswers(int limit) const {
        vector<pair<int, int> > ranking = getFanOutRanking();
        int topTraffic = 0;

        cout << fixed << setprecision(2);
        cout << "RESPUESTAS DE LA MISION" << endl;
        cout << endl;

        cout << "1. Top " << limit << " nodos con mayor fan-out y proporcion del trafico saliente:" << endl;
        for (int i = 0; i < ranking.size() && i < limit; i++) {
            int fanOut = ranking[i].first;
            int node = ranking[i].second;
            double proportion = 0.0;

            if (totalEdges > 0) {
                proportion = (static_cast<double>(fanOut) / totalEdges) * 100.0;
            }

            topTraffic += fanOut;

            cout << i + 1 << ". " << indexToIP[node]
                 << " - fan-out: " << fanOut
                 << ", destinos unicos: " << calculateUniqueTargets(node)
                 << ", proporcion: " << proportion << "%" << endl;
        }

        if (totalEdges > 0) {
            cout << "En conjunto, el top " << limit << " representa "
                 << (static_cast<double>(topTraffic) / totalEdges) * 100.0
                 << "% del trafico saliente registrado." << endl;
        }

        cout << endl;
        cout << "2. Lista de adyacencia vs matriz:" << endl;
        cout << "La lista de adyacencia es preferible porque este grafo es disperso:"
             << " hay " << nodeCount() << " nodos y " << totalEdges << " arcos."
             << " La lista usa O(V + E), mientras que una matriz usa O(V^2)."
             << " Con estos datos, la matriz reservaria " << nodeCount() * nodeCount()
             << " posiciones aunque solo existan " << totalEdges << " conexiones." << endl;

        cout << endl;
        cout << "3. IP presumiblemente bot master:" << endl;
        if (!ranking.empty()) {
            int botMaster = ranking[0].second;

            cout << indexToIP[botMaster] << " es la principal sospechosa porque tiene fan-out "
                 << ranking[0].first << " y conecta hacia "
                 << calculateUniqueTargets(botMaster) << " destinos unicos."
                 << " Ese patron muestra una IP que intenta alcanzar muchas maquinas,"
                 << " comportamiento esperado en un centro de control o coordinacion." << endl;

            if (ranking.size() > 1 && ranking[0].first == ranking[1].first) {
                cout << "Nota: existe empate en fan-out con " << indexToIP[ranking[1].second]
                     << "; se reporta primero " << indexToIP[botMaster]
                     << " por orden lexicografico para mantener un criterio consistente." << endl;
            }
        } else {
            cout << "No hay nodos con conexiones salientes para proponer bot master." << endl;
        }

        cout << endl;
        cout << "4. Costo de calcular fan-out:" << endl;
        cout << "En lista de adyacencia, calcular todos los fan-out cuesta O(V + E)"
             << " porque se recorre cada nodo y sus listas de vecinos."
             << " En matriz de adyacencia cuesta O(V^2), ya que se revisa cada celda"
             << " para contar las salidas de cada nodo." << endl;
        cout << "Conviene lista cuando el grafo es disperso, como en bitacoras de red."
             << " Conviene matriz cuando el grafo es denso o cuando se necesita consultar"
             << " muy rapido si existe un arco especifico entre dos nodos." << endl;
    }

    // Recorre el grafo por DFS desde una IP.
    // Complejidad: O(n + m).
    void DFS(const string& startIP, int limit) const {
        int start = findNode(startIP);

        if (start == -1) {
            cout << "IP inicial invalida para DFS." << endl;
            return;
        }

        vector<bool> visited(nodeCount(), false);
        int printed = 0;

        cout << "Recorrido DFS desde " << startIP << ": ";
        dfsRecursive(start, visited, printed, limit);
        cout << endl;
    }

    // Recorre el grafo por BFS desde una IP.
    // Complejidad: O(n + m).
    void BFS(const string& startIP, int limit) const {
        int start = findNode(startIP);

        if (start == -1) {
            cout << "IP inicial invalida para BFS." << endl;
            return;
        }

        vector<bool> visited(nodeCount(), false);
        queue<int> pending;
        int printed = 0;

        visited[start] = true;
        pending.push(start);

        cout << "Recorrido BFS desde " << startIP << ": ";
        while (!pending.empty() && printed < limit) {
            int node = pending.front();
            pending.pop();

            cout << indexToIP[node] << " ";
            printed++;

            for (int i = 0; i < adjacencyList[node].size(); i++) {
                int neighbor = adjacencyList[node][i];

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    pending.push(neighbor);
                }
            }
        }

        cout << endl;
    }

    // Regresa la IP con mayor fan-out para usarla como inicio de recorridos.
    // Complejidad: O(n).
    string getHighestFanOutIP() const {
        int bestNode = -1;
        int bestFanOut = -1;

        for (int i = 0; i < adjacencyList.size(); i++) {
            int fanOut = calculateFanOut(i);

            if (fanOut > bestFanOut ||
                (fanOut == bestFanOut && bestNode != -1 && indexToIP[i] < indexToIP[bestNode])) {
                bestFanOut = fanOut;
                bestNode = i;
            }
        }

        if (bestNode == -1) {
            return "";
        }

        return indexToIP[bestNode];
    }
};

// Extrae IP origen e IP destino de una linea con formato:
// Mes Dia Hora IP_origen IP_destino Mensaje...
// Complejidad: O(1) respecto al numero de registros.
bool extractIPs(const string& line, string& sourceIP, string& targetIP) {
    string month;
    string day;
    string time;
    stringstream ss(line);

    return static_cast<bool>(ss >> month >> day >> time >> sourceIP >> targetIP);
}

// Lee bitacora.txt y construye el grafo dirigido.
// Complejidad: O(r log n), donde r es registros y n IPs unicas.
bool buildGraphFromLogFile(const string& filename, Graph& graph, int& totalLogs) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << filename << endl;
        return false;
    }

    string line;
    totalLogs = 0;

    while (getline(file, line)) {
        string sourceIP;
        string targetIP;

        if (extractIPs(line, sourceIP, targetIP)) {
            graph.insertArc(sourceIP, targetIP);
            totalLogs++;
        }
    }

    file.close();
    return true;
}

// Coordina la lectura, construccion del grafo y analisis de fan-out.
// Complejidad: O(r log n + n log n + m).
int main() {
    Graph graph;
    int totalLogs = 0;

    if (!buildGraphFromLogFile("bitacora.txt", graph, totalLogs)) {
        return 1;
    }

    string startIP = graph.getHighestFanOutIP();

    cout << "Operacion Medianoche - Fase 4: Analisis con grafos" << endl;
    cout << "Archivo leido: bitacora.txt" << endl;
    cout << "Total de registros leidos: " << totalLogs << endl;
    cout << "Total de IPs/nodos unicos: " << graph.nodeCount() << endl;
    cout << "Total de arcos dirigidos: " << graph.edgeCount() << endl;
    cout << endl;

    graph.printAdjacencySample(10, 8);
    cout << endl;

    graph.printFanOutByNode();
    cout << endl;

    graph.printMissionAnswers(5);
    cout << endl;

    if (startIP != "") {
        graph.DFS(startIP, 20);
        graph.BFS(startIP, 20);
    }

    return 0;
}
