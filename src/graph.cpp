#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class Graph
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
    Graph(const vector<vector<int>> &matrix, int numPaths);
    Graph(const vector<vector<int>> &matrix);
    Graph(string filePath);
    Graph();
    
    // getters and setters
    int getNumPaths();
    void setNPathsFound(int num);
    int getNPathsFound();
    void setPathsFound(vector<tuple<int, int>> paths);
    vector<tuple<int,int>> getPathsFound();

    // auxiliary methods
    Graph generate_random_graph();
    Graph graph_from_txt(string filePath);
    vector<vector<int>> reverse_graph(vector<vector<int>> graph);
    void print_graph();
};

Graph::Graph(const vector<vector<int>> &matrix, int numPaths){
    // initializes and sets the values for the adjancency matrix
    adjacency_matrix = matrix;
    //sets number of paths
    numPaths = numPaths;
}

Graph::Graph(const vector<vector<int>> &matrix)
{    
    // initializes and sets the values for the adjancency matrix
    adjacency_matrix = matrix;
}

Graph::Graph(string filePath)
{
    string buff;

    int vertexQty;
    int edgeQty;

    ifstream myfile (filePath);
    if (myfile.is_open())
    {
        int v1, v2;
        myfile >> buff;
        vertexQty = stoi(buff);
        
        myfile >> buff;
        edgeQty = stoi(buff);

        myfile >> buff;
        numPaths = stoi(buff);
        
        adjacency_matrix  = vector<vector<int>>(vertexQty, vector<int> (vertexQty, -1));

        for (int i = 0; i < edgeQty; i++)
        {
            myfile >> buff;
            v1 = stoi(buff);
            myfile >> buff;
            v2 = stoi(buff);
            adjacency_matrix[v1][v2] = 1;
        }
        
        myfile.close();
    }
    else cout << "Unable to open file"; 
}

Graph::Graph()
{    
    adjacency_matrix = vector<vector<int>>();
    numPaths = -1;
}

int Graph::getNumPaths()
{
    return numPaths;
}

void Graph::setNPathsFound(int num)
{
    nPathsFound = num;
}

int Graph::getNPathsFound()
{
    return nPathsFound;
}

void Graph::setPathsFound(vector<tuple<int, int>> paths)
{
    pathsFound = paths;
}

Graph Graph::graph_from_txt(string filePath)
{    
    string buff;

    int vertexQty;
    int edgeQty;
    int pathQty;

    vector<vector<int>> matrix;

    ifstream myfile (filePath);
    if (myfile.is_open())
    {
        int v1, v2;
        myfile >> buff;
        vertexQty = stoi(buff);
        
        myfile >> buff;
        edgeQty = stoi(buff);

        myfile >> buff;
        pathQty = stoi(buff);
        
        matrix  = vector<vector<int>>(vertexQty, vector<int> (vertexQty, -1));

        for (int i = 0; i < edgeQty; i++)
        {
            myfile >> buff;
            v1 = stoi(buff);
            myfile >> buff;
            v2 = stoi(buff);
            matrix[v1][v2] = 1;
        }
        
        myfile.close();
    }
    else cout << "Unable to open file"; 

    return Graph(matrix, pathQty);
}

void Graph::print_graph()
{
    for (int i = 0; i < adjacency_matrix[0].size(); i++)
    {
        cout << "[ ";
        for (int j = 0; j < adjacency_matrix[0].size(); j++)
        {
            int val = adjacency_matrix[i][j];
            if (val == 1)
            {
                cout << "0" << val << " ";
            }
            else
            {
                cout << val << " ";
            }            
        }
        cout << " ]" << endl;
    }    
}
