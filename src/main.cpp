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
    map<int, int> parentsMap = G.breadth_first_search(0);
    // map<int, int> parentsMap = G.depth_first_search(0);

    // for (auto &&i : parentsMap)
    // {
    //     cout << "Parent Pairs: (" << (char)(i.first + 'A') << "," << (char)(i.second + 'A') << ")" << endl;
    // }
    
    G.ford_fulkerson();

    return 0;
}