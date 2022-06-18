#include<iostream>
#include<stdlib.h>
#include<string>
#include <sstream>

// Modified from https://www.sanfoundry.com/cpp-program-construct-random-directed-acyclic-graph/

// The maximum number of the vertex for the sample random graph.
// #define NOV 8192
int NOV = 20;
int e = 20;
 
using namespace std;
 
// A function to check for the cycle, on addition of a new edge in the random graph.
bool CheckAcyclic(int edge[][2], int ed, bool check[], int v)
{
	int i;
	bool value;
	// If the current vertex is visited already, then the graph contains cycle.
	if(check[v] == true)
	{
		return false;
	}
	else
	{
		check[v] = true;
		// For each vertex, go for all the vertex connected to it.
		for(i = ed; i >= 0; i--)
		{
			if(edge[i][0] == v)
			{
				return CheckAcyclic(edge, ed, check, edge[i][1]);
			}
		}
	}
	// In case, if the path ends then reassign the vertexes visited in that path to false again.
	check[v] = false;
 
	if(i == 0)
		return true;
}
 
// A function to generate random graph.
void GenerateRandGraphs(int e)
{
	int i, j, edge[e][2], count;
 
	bool check[NOV+1];
 
	// Build a connection between two random vertex.
	i = 0;
	while(i < e)
	{
		edge[i][0] = rand()%NOV+1;
		edge[i][1] = rand()%NOV+1;
 
		for(j = 1; j <= NOV; j++)check[j] = false;
 
		if(CheckAcyclic(edge, i, check, edge[i][0]) == true)
			i++;
	}
 

    // create header
    // nVertex, nEdges, Solution
    // e1 e2
    string buff = to_string(NOV+1) + " " +  to_string(e) + " -1" ;
	cout <<  buff << endl;

	// Print the random graph.
	// cout<<"\nThe generated random random graph is: ";
	for(i = 0; i < NOV; i++)
	{
		count = 0;
		//  cout<<"\n\t"<<i+1<<"-> { ";
		
		for(j = 0; j < e; j++)
		{
			if(edge[j][0] == i+1)
			{
				// cout << "first vertex: " << i << " ";
				// cout << "second vertex: "<< edge[j][1] <<endl;
				cout << i << " ";
				cout << edge[j][1] <<endl;
				count++;
			}
			else if(edge[j][1] == i+1)
			{
				count++;
			}
			else if(j == e-1 && count == 0)
			{
				// cout<<"Isolated Vertex!";
			}
		}
		// cout<<" }";
	}	


}
 
int main(int argc, char const *argv[])
{
	if (argc == 3)
	{
		istringstream nVertexstream(argv[1]);
		nVertexstream >> NOV;
		// cout << NOV << endl;
		istringstream nEdgesstream(argv[2]);
		nEdgesstream >> e;
	 	// cout << e << endl;
	}
 
	// cout << NOV << "   " << e << endl;

	// A function to generate a random undirected graph with e edges.
	GenerateRandGraphs(e);
}