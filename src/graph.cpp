#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class graph
{
private:
    // matrix that stores graph data
    vector<vector<int>> adjacency_matrix;
    // precalculated number of unique paths
    int numPaths = 0;
    // calculated number of unique paths and paths found
    int nPathsFound = 0;
    vector<tuple<int, int>> pathsFound;
public:
    // constructors
    graph(const vector<vector<int>> &matrix, int numPaths);
    graph(const vector<vector<int>> &matrix);
    graph(string filePath);
    graph();
    
    // getters and setters
    int getNumPaths();
    void setNPathsFound(int num);
    int getNPathsFound();
    void setPathsFound(vector<tuple<int, int>> paths);
    vector<tuple<int,int>> getPathsFound();

    // auxiliary methods
    graph generate_random_graph();
    graph graph_from_txt(string filePath);
    vector<vector<int>> reverse_graph(vector<vector<int>> graph);
};

graph::graph(const vector<vector<int>> &matrix, int numPaths){
    // initializes and sets the values for the adjancency matrix
    adjacency_matrix = matrix;
    //sets number of paths
    numPaths = numPaths;
}

graph::graph(const vector<vector<int>> &matrix)
{    
    // initializes and sets the values for the adjancency matrix
    adjacency_matrix = matrix;
}

int graph::getNumPaths()
{
    return numPaths;
}

void graph::setNPathsFound(int num)
{
    nPathsFound = num;
}

int graph::getNPathsFound()
{
    return nPathsFound;
}

void graph::setPathsFound(vector<tuple<int, int>> paths)
{
    pathsFound = paths;
}
