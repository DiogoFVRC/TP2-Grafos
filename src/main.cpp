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
    clock_t start, end;
    start = clock();
    
    if (argc == 2)
    {
        string filename(argv[1]);
        Graph G(filename);
        G.find_unique_paths();
    }
    else
    {
        cout << "Wrong number of parameters" << endl;
    }

    end = clock();
    cout << endl;
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    return 0;
}