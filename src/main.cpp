/**
 * @brief Programa para obter caminhos distintos em um grafo direcionado
 * 
 */

#include "graph.cpp"

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    vector<Graph> grafos;
    for (size_t i = 1; i <= 20; i++)
    {
        cout << "data/Grafo" + to_string(i) + ".txt" << endl;
        grafos.push_back(Graph("data/Grafo" + to_string(i) + ".txt"));
        grafos[i-1].ford_fulkerson();
        cout << endl;
    }
    
    // Graph G1("data/Grafo1.txt");
    // G1.ford_fulkerson();
    // Graph G2("data/Grafo2.txt");
    // G2.ford_fulkerson();
    // Graph G3("data/Grafo3.txt");
    // G3.ford_fulkerson();
    // Graph G4("data/Grafo4.txt");
    // G4.ford_fulkerson();
    // Graph G5("data/Grafo5.txt");
    // G5.ford_fulkerson();
    return 0;
}