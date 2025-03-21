#include <iostream>
#include <memory>

// #include "Adjacency List/AdjacencyList.h"
// #include "Adjacency Map/AdjacencyMap.h"
#include "Edge List/EdgeList.h"
// #include "Adjacency Matrix/AdjacencyMatrix.h"
// #include "General Graph/GraphAbstract.h"

using namespace Graph;

int main()
{
	// For testing different graphs implementation
	GraphAbstract<std::string, std::string> *graph;
	char op;
	size_t number;
	std::string vertex1, vertex2, edge;
	std::vector<std::string> *edges;
	std::vector<std::string> *vertices;
	std::vector<std::pair<std::string, std::string>> *endVertices;
	do
	{
		std::cout << "1-Edge_List 2-Adjacency_List 3-Adjacency_Map 4-Adjacency_Matrix: ";
		std::cin >> number;
		switch (number)
		{
		case 1:
			graph = new EdgeList<std::string, std::string>();
			break;
		// case 2:
		// 	graph = new AdjacencyList<std::string, std::string>();
		// 	break;
		// case 3:
		// 	graph = new AdjacencyMap<std::string, std::string>{};
		// 	break;
		/*case 4:
			graph = new AdjacencyMatrix<std::string, std::string>{};
			break;*/
		default:
			std::cout << "Invalid operation\n";
		}
	}
	while (number < 1 || number > 4);
	do
	{
		std::cout << "Enter operation: ";
		std::cin >> op;
		try
		{
			switch (op)
			{
			case 'E':
				std::cout << "Enter edge name: ";
				std::cin >> edge;
				std::cout << "Enter the first vertex: ";
				std::cin >> vertex1;
				std::cout << "Enter the second vertex: ";
				std::cin >> vertex2;
				graph->add_bidirected_Edge(edge, vertex1, vertex2);
				break;
			case 'V':
				std::cout << "Enter vertex name: ";
				std::cin >> vertex1;
				graph->addVertex(vertex1);
				break;
			case 'P':
				std::cout << graph;
				break;
			case 'v':
				vertices = graph->vertices();
				std::cout << "Vertices:";
				for (const std::string &s : *vertices)
					std::cout << " " << s;
				break;
			case 'e':
				edges = graph->edges();
				std::cout << "Edge:";
				for (const std::string &pair : *edges)
					std::cout << "\nName: " << pair;
				break;
			case 'Q':
				std::cout << "Enter edge: ";
				std::cin >> edge;
				endVertices = graph->endVertices(edge);
				if (!endVertices->empty())
					for (const std::pair<std::string, std::string> &pair : *endVertices)
					{
						std::cout << pair.first << " -> " << pair.second << '\n';
					}
				else
					std::cout << edge << " edge doesn't exist";
				break;
			case 'q':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				edges = graph->outgoingEdges(vertex1);
				if (!edges->empty())
				{
					std::cout << "Outgoing edges:";
					for (const std::string &e : *edges)
						std::cout << ' ' << e;
				}
				else
					std::cout << vertex1 << " doesn't have outgoing edges";
				break;
			case 'I':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				edges = graph->incomingEdges(vertex1);
				if (!edges->empty())
				{
					std::cout << "Incoming edges:";
					for (const std::string &e : *edges)
						std::cout << ' ' << e;
				}
				else
					std::cout << vertex1 << " doesn't have incoming edges";
				break;
			case 'G':
				std::cout << "Enter vertex 1: ";
				std::cin >> vertex1;
				std::cout << "Enter vertex 2: ";
				std::cin >> vertex2;
				edge = graph->getEdge(vertex1, vertex2);
				if (!edge.empty())
					std::cout << "Edge: " << edge;
				else
					std::cout << "Edge doesn't exist";
				break;
			case 'o':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				vertices = graph->opposite(vertex1);
				if (vertices->empty())
					std::cout << vertex1 << " doesn't exists";
				else
				{
					std::cout << "Opposite of " << vertex1 << ": ";
					for (const std::string &s : *vertices)
						std::cout << s << ' ';
				}
				break;
			case 'R':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				graph->removeVertex(vertex1);
				break;
			case 'r':
				std::cout << "Enter edge : ";
				std::cin >> edge;
				graph->removeEdge(edge);
				break;
			case 'C':
				std::cout << "Enter edge : ";
				std::cin >> edge;
				std::cout << edge << " edge" << (graph->containEdge(edge) ? " " : " doesn't ") << "exists";
				break;
			case 'c':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				std::cout << vertex1 << " vertex" << (graph->containVertex(vertex1) ? " " : " doesn't ") << "exists";
				break;
			case 'N':
				std::cout << "Number of vertices: " << graph->numVertices();
				break;
			case 'n':
				std::cout << "Number of edges: " << graph->numEdges();
				break;
			case 'D':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				number = graph->outDegree(vertex1);
				std::cout << vertex1 << " vertex"
						  << (number == -1 ? " doesn't exist" : " outgoing edges: " + std::to_string(number));
				break;
			case 'd':
				std::cout << "Enter vertex: ";
				std::cin >> vertex1;
				number = graph->inDegree(vertex1);
				std::cout << vertex1 << " vertex"
						  << (number == -1 ? " doesn't exist" : " incoming edges: " + std::to_string(number));
				break;
			case 't':
				delete graph;
				do
				{
					std::cout << "1-Edge_List 2-Adjacency_List 3-Adjacency_Map: ";
					std::cin >> number;
					switch (number)
					{
					case 1:
						graph = new EdgeList<std::string, std::string>();
						break;
					// case 2:
					// 	graph = new AdjacencyList<std::string, std::string>();
					// 	break;
					// case 3:
					// 	graph = new AdjacencyMap<std::string, std::string>{};
					// 	break;
						//                            case 4:
						//                                graph = new AdjacencyMatrix<std::string, std::string>{};
						//                                break;
					default:
						std::cout << "Invalid operation\n";
					}
				}
				while (number < 1 || number > 3);
				break;
			default:
				std::cout << "Invalid operation";
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what();
		}
		std::cout << '\n';
	}
	while (op != 'X' && op != 'x');
}
