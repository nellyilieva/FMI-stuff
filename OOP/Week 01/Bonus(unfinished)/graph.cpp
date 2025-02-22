#include <iostream>

const int MAX_LENGTH = 10;

struct Vertex {
	char name[MAX_LENGTH + 1];
};

struct Edge {
	Vertex v1;
	Vertex v2;
};

struct Graph {
	int vertexCount;
	int edgeCount;
	Edge* arrEdge;
};

Vertex createVertex() {
	Vertex v;
	std::cin >> v.name;

	return v;
}

Edge* initEdges(size_t m) {
	Edge* edges = new Edge[m];

	for (size_t i = 0; i < m; i++) {

		Vertex v1 = createVertex();
		Vertex v2 = createVertex();

		Edge newEdge = { v1, v2 };
		edges[i] = newEdge;
	}

	return edges;
}

bool vertexAreEqual(const Vertex& v1, const Vertex& v2) {
	return !strcmp(v1.name, v2.name);
}

void addEdge(Graph& g, const Vertex& v1, const Vertex& v2) {
	for (int i = 0; i < g.edgeCount; i++) {
		if (!vertexAreEqual(v1, g.arrEdge[i].v1) && vertexAreEqual(v2, g.arrEdge[i].v2)) {

			Edge newEdge = Edge{ v1, v2 };

			Edge* newArrEdge = new Edge[g.edgeCount + 1];
			for (int i = 0; i < g.edgeCount; ++i) {
				newArrEdge[i] = g.arrEdge[i];
			}
			newArrEdge[g.edgeCount] = newEdge;

			delete[] g.arrEdge;
			g.arrEdge = newArrEdge;
			++g.edgeCount;
		}
	}
}

Graph initGraph(int m) {
	Edge* edges = initEdges(m);

	Graph graph;
	graph.edgeCount = m;
	graph.arrEdge = edges;

	//...

	return graph;
}

void deleteGraph(Graph& g) {
	delete[] g.arrEdge;

	g.edgeCount = 0;
	g.vertexCount = 0;
}

void getDegreeOfVertex(const Vertex& v1, const Graph& g) {
	int dPlus = 0;
	int dMinus = 0;

	for (int i = 0; i < g.edgeCount; i++) {
		if (vertexAreEqual(v1, g.arrEdge[i].v1)) {
			dPlus++;
		}
		if (vertexAreEqual(v1, g.arrEdge[i].v2)) {
			dMinus++;
		}
	}
	std::cout << 'd+:' << dPlus << "d-:" << dMinus;
}

void addEdge(const Graph& g, const Vertex& v1, const Vertex& v2) {
	Edge e;

	e.v1 = v1;
	e.v2 = v2;

	Edge* newArrEdge = new Edge[g.edgeCount + 1];

	for (int i = 0; i < g.edgeCount; i++) {
		newArrEdge[i] = g.arrEdge[i];
	}

	newArrEdge[g.edgeCount] = e;

	delete[] g.arrEdge;
}

bool isFull(Graph& g) {
	return g.edgeCount == (int)((g.vertexCount + g.vertexCount + 1) / 2);
}


int main()
{
	int m;
	std::cin >> m;

	Graph graph = initGraph(m);
	deleteGraph(graph);
}
