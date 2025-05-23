// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
vector<int> resolver(const vector<int>& datos) {

    vector<int> resultados = {0, 0};

    if (datos.size() > 2) 
    {
        for (size_t i = 1; i < datos.size() - 1; i++)
        {
            if (datos[i-1] < datos[i] && datos[i] > datos[i+1])
            {
                resultados[0]++;
            }
            else if (datos[i-1] > datos [i] && datos[i] < datos[i+1])
            {
                resultados[1]++;
            }
        }
    }
    
    return resultados;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    size_t n;
    cin >> n;

    vector<int> datos(n);

    for (int i = 0; i < n; i++)
    {
        cin >> datos[i];
    }

    vector<int> sol = resolver(datos);
    // escribir sol
    cout << sol[0] << " " << sol[1] << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}