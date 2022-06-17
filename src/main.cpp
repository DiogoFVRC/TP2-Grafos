/**
 * @brief Programa para obter caminhos distintos em um grafo direcionado
 * 
 */

#include "graph.cpp"
#include <bits/stdc++.h>

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    clock_t start, end;
  
    // /* Recording the starting clock tick.*/
    // start = clock();
    
    // vector<Graph> grafos;
    // for (size_t i = 1; i <= 20; i++)
    // {
    //     clock_t startIndividual, endIndividual;
    //     startIndividual = clock();

    //     cout << "data/Grafo" + to_string(i) + ".txt" << endl;
    //     grafos.push_back(Graph("data/Grafo" + to_string(i) + ".txt"));
    //     grafos[i-1].ford_fulkerson();

    //     endIndividual = clock();
    //     double time_taken = double(endIndividual - startIndividual) / double(CLOCKS_PER_SEC);
    //     cout << "Time taken by " << "data/Grafo" + to_string(i) + ".txt" << " is : " << fixed 
    //         << time_taken << setprecision(5);
    //     cout << " sec " << endl << endl;
    // }  
  
    // // Recording the end clock tick.
    // end = clock();
    // cout << endl;
    // double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    // cout << "Time taken by program is : " << fixed 
    //      << time_taken << setprecision(5);
    // cout << " sec " << endl;

    /* Recording the starting clock tick.*/
    start = clock();
    Graph G("data/testGraph.txt");
    G.ford_fulkerson();
    // Recording the end clock tick.
    end = clock();
    cout << endl;
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    return 0;
}