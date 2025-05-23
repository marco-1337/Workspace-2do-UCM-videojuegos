// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/* 
    El algoritmo pertenece a O(n) ya que se itera tanto como la longitud de las palabras
    introducidas (+ una iteración de hasta 26 para comprobar las repeticiones de caracteres)
*/
bool anagramas(const string& cad1, const string& cad2) {

    if(cad1.length() != cad2.length())
        return false;

    int cuenta1[26] = {0}, cuenta2[26] = {0};
    int lastA = 0, lastB = 0;

    for (int i = 0; i < cad1.length(); i++)
    {
        // Cada uno deberia estar en una funcion pero me da mucho palo
        cuenta1[cad1[i] - 'a']++;

        if (cad1[i] - 'a' > lastA)
            lastA = cad1[i] - 'a';
        
        cuenta2[cad2[i] - 'a']++;

        if (cad2[i] - 'a' > lastB)
            lastB = cad2[i] - 'a';
    }

    if(lastA != lastB)
        return false;
    
    for(int i = 0; i <= lastA; i++)
    {
        if(cuenta1[i] != cuenta2[i])
            return false;
    }

    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    string word1, word2;
    cin >> word1 >> word2;
    cout << (anagramas(word1,word2) ? "SI" : "NO") << endl;
}

//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}