#include <iostream>
#include <fstream>
using namespace std;

class graphColoring
{
	public:
	
	int uncolorNode;
	int newColor;
	int numNodes;
	int **adjacencyMatrix;
	
	graphColoring(int num)
	{
		numNodes = num;
		newColor = 0;
		adjacencyMatrix = new int*[numNodes+1];
		for(int i = 1; i <= numNodes; i++)
		{
			adjacencyMatrix[i] = new int[numNodes+1];
		}
		
		//intialization of matrix
		for(int i = 1; i <= numNodes; i++)
		{
			for(int j = 1; j <= numNodes; j++)
			{
				adjacencyMatrix[i][j] = 0;	
			}
		}
	}
	
	bool isAllColor()
	{
		for(int i = 1; i <= numNodes; i++)
		{
			for(int j = 1; j <= numNodes; j++)
			{
				if(adjacencyMatrix[i][j] == 0 && (i == j))
				return false;
			}
		}
		return true;
	}
	
	void loadCostMatrix(ifstream& inFile, ofstream& outFile1)
	{
		int from, to;
		while(inFile >> from >> to)
		{
			outFile1 << from << " "<< to << endl;
			adjacencyMatrix[from][to] = 1;
			adjacencyMatrix[to][from] = 1;
		}
	}	
	
	void print_2D(ofstream& outFile1)
	{
		for(int i = 1; i <= numNodes; i++)
		{
			for(int j = 1; j <= numNodes; j++)
			{
				outFile1 << adjacencyMatrix[i][j] << " ";
			}
			outFile1 << endl;
		}
		outFile1 << endl << endl;
	}
		
};

int main(int argc, char* argv[])
{
	int item;
	ifstream inFile;
	ofstream outFile1;
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	inFile >> item;
	outFile1 << "Number of Nodes: " << item << "\n\n";
	graphColoring graph(item); 
	outFile1 << "Input Edges: "<< endl;
	graph.loadCostMatrix(inFile, outFile1);
	outFile1 << "\n\nAdjacency Matrix: " << endl;
	
	graph.print_2D(outFile1);
	graph.adjacencyMatrix[1][1] = 1;
	graph.print_2D(outFile1);
	graph.newColor++;
	for(int i = 2; i <= graph.numNodes; i++)
	{
		graph.uncolorNode = i;
		for(int j = 1; j <= graph.numNodes; j++)
		{
			if(graph.adjacencyMatrix[graph.uncolorNode][j] == 1 && graph.adjacencyMatrix[j][j] == graph.newColor)
			{
				graph.newColor++;
				graph.adjacencyMatrix[graph.uncolorNode][graph.uncolorNode] = graph.newColor;
			}
			
			else if(graph.adjacencyMatrix[graph.uncolorNode][j] == 1 && graph.adjacencyMatrix[j][j] != graph.newColor)
			graph.adjacencyMatrix[graph.uncolorNode][graph.uncolorNode] = graph.newColor;
		}
		graph.print_2D(outFile1);
	}
	
	graph.print_2D(outFile1);
	outFile1 << "Number of colors used is: " << graph.newColor << endl;
	inFile.close();
	outFile1.close();
}


