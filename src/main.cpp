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
    Graph G("data/exampleGraph.txt");
    
    G.print_graph();

    return 0;
}