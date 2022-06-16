#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <set>

using namespace std;

#define INT_MAX 2147483647

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
    // number of vertices and edges
    int vertexQty = 0, edgeQty = 0;
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
    void print_graph(vector<vector<int>> graph);
    void print_clean_graph(vector<vector<int>> graph);
    void print_path(vector<int> parents, bool asChar);
    void print_to_file(string filename);
    vector<int> obtain_successors(int vertex);
    vector<int> obtain_successors(int vertex, vector<vector<int>> graph);
    map<int, int> depth_first_search(int rootVertex);
    map<int, int> breadth_first_search(int rootVertex);
    bool breadth_first_search(int rootVertex, int targetVertex, map<int, int> &parents);
    bool breadth_first_search(vector<vector<int>> graph,int rootVertex, int targetVertex, vector<int> &parents);
    void ford_fulkerson();
    void ford_fulkerson(vector<vector<int>> graph);
};

/**
 * @brief Construct a new Graph object
 * 
 * @param matrix adjacency matrix that represents the graph
 * @param numPaths pre calculated number of unique paths for said graph
 */
Graph::Graph(const vector<vector<int>> &matrix, int numPaths){
    // initializes and sets the values for the adjancency matrix
    adjacency_matrix = matrix;
    //sets number of paths
    numPaths = numPaths;
}

/**
 * @brief Construct a new Graph object without the optimal answer known
 * 
 * @param matrix adjacency matrix that represents the graph
 */
Graph::Graph(const vector<vector<int>> &matrix)
{    
    // initializes and sets the values for the adjancency matrix
    adjacency_matrix = matrix;
    numPaths = -1;
}

/**
 * @brief Construct a new Graph object from a .txt file
 * 
 * @param filePath path of the file containing graph information
 */
Graph::Graph(string filePath)
{
    string buff;

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
        
        adjacency_matrix  = vector<vector<int>>(vertexQty, vector<int> (vertexQty, 0));

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

/**
 * @brief Default constructor for a new Graph
 * 
 */
Graph::Graph()
{    
    adjacency_matrix = vector<vector<int>>();
    numPaths = -1;
}

//Getters and setters
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

/**
 * @brief Creates a Graph object from a .txt file
 * 
 * @param filePath path for the file containing graph information
 * @return Graph constructed from file
 */
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


vector<int> Graph::obtain_successors(int vertex)
{
    vector<int> successors;
    for (size_t i = 0; i < adjacency_matrix[0].size(); i++)
    {
        if (adjacency_matrix[vertex][i] != 0)
        {
            successors.insert(successors.begin(), i);
            //successors.push_back(i);
        }
        
    }
    return successors;
}

vector<int> Graph::obtain_successors(int vertex, vector<vector<int>> graph)
{
    vector<int> successors;
    for (size_t i = 0; i < graph[0].size(); i++)
    {
        if (graph[vertex][i] != 0)
        {
            successors.insert(successors.begin(), i);
            //successors.push_back(i);
        }
        
    }
    return successors;
}

/**
 * @brief Depth first search that starts on the rootVertex
 * 
 * @param rootVertex vertex in which the search will start at
 * @return map<int,int> parents map
 */
map<int,int> Graph::depth_first_search(int rootVertex)
{
    // Pilha de vertices
    stack<int> S;
    S.push(rootVertex);
    // Dicionario de pais
    map<int,int> parents;
    parents.emplace(rootVertex, -1);
    // Elementos visitados
    unordered_set<int> visited;

    // DFS
    while (!S.empty())
    {
        int vertex = S.top(); 
        cout << "Vertex: " << vertex << endl;
        S.pop();
        if (!visited.count(vertex))
        {
            visited.insert(vertex);
            //cout << "visited: " << (char)(vertex + 'A') << endl;
            for (auto &&v : obtain_successors(vertex))
            {                
                //cout << "Vertex: " << (char)(vertex + 'A') << " Successor: " << (char)(v + 'A') << endl;
                if(!visited.count(v))
                {
                    S.push(v);
                    parents.emplace(v, vertex);
                }
            }            
        }        
    }

    return parents;
}

/**
 * @brief Breadth first search that starts on the rootVertex
 * 
 * @param rootVertex vertex in which the search will start at
 * @return map<int,int> parents map
 */
map<int,int> Graph::breadth_first_search(int rootVertex)
{
    // Pilha de vertices
    queue<int> Q;
    Q.push(rootVertex);
    // Dicionario de pais
    map<int,int> parents;
    parents.emplace(rootVertex, -1);
    // Elementos visitados
    unordered_set<int> visited;

    // BFS
    while (!Q.empty())
    {
        int vertex = Q.front(); 
        //cout << "Vertex: " << vertex << endl;
        Q.pop();
        if (visited.find(vertex) != visited.end())
        {
            visited.insert(vertex);
            //cout << "visited: " << (char)(vertex + 'A') << endl;
            for (auto &&v : obtain_successors(vertex))
            {                
                //cout << "Vertex: " << (char)(vertex + 'A') << " Successor: " << (char)(v + 'A') << endl;
                if(!visited.count(v))
                {
                    Q.push(v);
                    parents.emplace(v, vertex);
                }
            }            
        }        
    }

    return parents;
}

/**
 * @brief Breadth first search that starts on the rootVertex
 * 
 * @param rootVertex source vertex
 * @param targetVertex terminal vertex
 * @param parents map that will store parent data
 * @return if targetVertex is in the visited list
 */
bool Graph::breadth_first_search(int rootVertex, int targetVertex, map<int,int> &parents)
{
    // Pilha de vertices
    queue<int> Q;
    Q.push(rootVertex);
    // Set parent of root as null
    parents.emplace(rootVertex, -1);
    // Elementos visitados
    unordered_set<int> visited;

    // BFS
    while (!Q.empty())
    {
        int vertex = Q.front(); 
        //cout << "Vertex: " << vertex << endl;
        Q.pop();
        if (!visited.count(vertex))
        {
            visited.insert(vertex);
            //cout << "visited: " << (char)(vertex + 'A') << endl;
            for (auto &&v : obtain_successors(vertex))
            {                
                //cout << "Vertex: " << (char)(vertex + 'A') << " Successor: " << (char)(v + 'A') << endl;
                if(!visited.count(v))
                {
                    Q.push(v);
                    parents.emplace(v, vertex);
                }
            }            
        }        
    }

    return(visited.count(targetVertex));
}

/**
 * @brief Breadth first search that starts on the rootVertex
 * 
 * @param rootVertex source vertex
 * @param targetVertex terminal vertex
 * @param parents vector that will store parent data
 * @return if targetVertex is in the visited list
 */
bool Graph::breadth_first_search(vector<vector<int>> graph,int rootVertex, int targetVertex, vector<int> &parents)
{
    // Pilha de vertices
    queue<int> Q;
    Q.push(rootVertex);
    // Set parent of root as null
    parents[rootVertex] = -1;
    // Elementos visitados
    unordered_set<int> visited;

    // BFS
    while (!Q.empty())
    {
        int vertex = Q.front(); 
        //cout << "Vertex: " << vertex << endl;
        Q.pop();
        if (!visited.count(vertex))
        {
            visited.insert(vertex);
            //cout << "visited: " << (char)(vertex + 'A') << endl;
            for (auto &&v : obtain_successors(vertex, graph))
            {                
                //cout << "Vertex: " << (char)(vertex + 'A') << " Successor: " << (char)(v + 'A') << endl;
                if(!visited.count(v))
                {
                    Q.push(v);
                    parents[v] = vertex;
                }
            }            
        }        
    }
    // for (auto &&i : visited)
    // {
    //     cout << "Visited vert: " << i << endl;
    // }
    // cout << "Any paths found? " << (visited.count(targetVertex)) << endl;
    

    return (visited.count(targetVertex));
}

/**
 * @brief Ford fulkerson implementation
 * @ref reference for implementation "https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/"
 * 
 */
void Graph::ford_fulkerson()
{
    int u, v;
    int s = 0, t = adjacency_matrix.size()-1;
 
    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    vector<vector<int>> rGraph; // Residual graph where rGraph[i][j]
                   // indicates residual capacity of edge
                   // from i to j (if there is an edge. If
                   // rGraph[i][j] is 0, then there is not)
    size_t graphLen = adjacency_matrix.size();
    vector<vector<int>> uniquePaths;

    // for (u = 0; u < graphLen; u++)
    //     for (v = 0; v < graphLen; v++)
    //         rGraph[u][v] = adjacency_matrix[u][v];
 
    rGraph = vector<vector<int>>(adjacency_matrix);

    vector<int> parent(graphLen); // This array is filled by BFS and to
                   // store path
 
    int max_flow = 0; // There is no flow initially
 
    // Augment the flow while there is path from source to
    // sink
    while (breadth_first_search(rGraph, s, t, parent)) {
        // uniquePaths.push_back(parent);
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // print_clean_graph(rGraph);
    // adjacency_matrix[i][j] - graph[i][j];
    vector<vector<int>> cleanGraph(adjacency_matrix);

    for (size_t i = 0; i < graphLen; i++)
    {
        for (size_t j = 0; j < graphLen; j++)
        {
            if (adjacency_matrix[i][j] - rGraph[i][j] != 1)
            {
                cleanGraph[i][j] = 0;
            }            
        }
    }
    // print_graph(cleanGraph);

    s = 0, t = adjacency_matrix.size()-1;
    while (breadth_first_search(cleanGraph, s, t, parent)) {
        uniquePaths.push_back(parent);

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            cleanGraph[u][v] = 0;
            cleanGraph[v][u] = 0;
        }
    }

    cout << "Number of paths found (algorithm): " << max_flow << endl;
    cout << "Number of paths found (by hand): " << numPaths << endl;
    for (size_t i = 0; i < max_flow; i++)
    {
        print_path(uniquePaths[i], false);
    //     cout << "[ ";
    //     for (size_t j = 0; j < uniquePaths[i].size(); j++)
    //     {
    //         cout << "(Vertex: " << (char)(j + 'A') << " Parent: " << (char)(uniquePaths[i][j] + 'A') << " )";
    //     }        
    //     cout << " ]" << endl;
    }
    
    // Return the overall flow
    // return max_flow;
}

/**
 * @brief Prints graph in a formatted manner
 * Ex: 
 * Input: 
 * V1->V2->V3 
 * Output: 
 * [ 00 01 00 ]
 * [ 00 00 01 ]
 * [ 00 00 00 ]
 */
void Graph::print_clean_graph(vector<vector<int>> graph)
{
    cout << "[ V ";
    for (int i = 0; i < adjacency_matrix[0].size(); i++)
    {
        cout << (char)(i +'A')  << " ";
    }
    cout << "]" << endl;
    for (int i = 0; i < adjacency_matrix[0].size(); i++)
    {
        cout << "[ " << (char)(i +'A') << " ";
        for (int j = 0; j < adjacency_matrix[0].size(); j++)
        {
            int val = adjacency_matrix[i][j] - graph[i][j] + 1;
            if (val == 2)
            {
                cout << 1 << " ";
            }
            else
            {
                cout << 0 << " ";
            }            
        }
        cout << "]" << endl;
    }    
}

/**
 * @brief Prints graph in a formatted manner
 * Ex: 
 * Input: 
 * V1->V2->V3 
 * Output: 
 * [ 00 01 00 ]
 * [ 00 00 01 ]
 * [ 00 00 00 ]
 */
void Graph::print_graph()
{
    cout << "[ V ";
    for (int i = 0; i < adjacency_matrix[0].size(); i++)
    {
        cout << (char)(i +'A')  << " ";
    }
    cout << "]" << endl;
    for (int i = 0; i < adjacency_matrix[0].size(); i++)
    {
        cout << "[ " << (char)(i +'A') << " ";
        for (int j = 0; j < adjacency_matrix[0].size(); j++)
        {
            int val = adjacency_matrix[i][j];
            if (val == 1)
            {
                cout << val << " ";
            }
            else
            {
                cout << 0 << " ";
            }            
        }
        cout << "]" << endl;
    }    
}

/**
 * @brief Prints graph in a formatted manner
 * Ex: 
 * Input: 
 * V1->V2->V3 
 * Output: 
 * [ 00 01 00 ]
 * [ 00 00 01 ]
 * [ 00 00 00 ]
 */
void Graph::print_graph(vector<vector<int>> graph)
{
    cout << "[ V ";
    for (int i = 0; i < graph[0].size(); i++)
    {
        cout << (char)(i +'A')  << " ";
    }
    cout << "]" << endl;
    for (int i = 0; i < graph[0].size(); i++)
    {
        cout << "[ " << (char)(i +'A') << " ";
        for (int j = 0; j < graph[0].size(); j++)
        {
            int val = graph[i][j];
            if (val == 1)
            {
                cout << val << " ";
            }
            else
            {
                cout << 0 << " ";
            }            
        }
        cout << "]" << endl;
    }    
}

/**
 * @brief Prints graph in a formatted manner
 * Ex: 
 * Input: 
 * V1->V2->V3 
 * Output: 
 * [ 00 01 00 ]
 * [ 00 00 01 ]
 * [ 00 00 00 ]
 */
void Graph::print_path(vector<int> parents, bool asChar)
{    
    string output = "", buff = "0 ";
    vector<int> path;
    int s = 0, t = adjacency_matrix.size()-1;
    for (int v = t; v != s; v = parents[v]) {
        path.push_back(v);
        // output += to_string(v);//((char)(v+'A'));
    }   
    
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (asChar)
        {
            buff += to_string((char)(path.at(i) + 'A')) + " ";
        }
        else
        {
            buff += to_string(path.at(i)) + " ";
        }
    }
    cout << buff << endl;
}


/**
 * @brief Outputs graph to file 
 */
void Graph::print_to_file(string filename)
{   
    // Create and open a text file
    ofstream file(filename);
    // Create header
    string header = to_string(vertexQty) + " " + to_string(edgeQty) + " " + to_string(numPaths);

    file << header << endl;
    for (size_t i = 0; i < vertexQty; i++)
    {
        for (size_t j = 0; j < vertexQty; j++)
        {
            if (adjacency_matrix[i][j] > 0)
            {
                file << i << " " << j << endl;
            }            
        }        
    }

    // Close the file
    file.close();
}
