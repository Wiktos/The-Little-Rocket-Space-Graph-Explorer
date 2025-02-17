#include <exception>
#include <algorithm>
#include "undirected_graph.h"

int UndirectedGraph::degree(const UndirectedGraph& G, int v) {
	int degree = 0;
	for (auto w : G.adj(v)) {
		degree++;
	}
	return degree;
}

int UndirectedGraph::maxDegree(const UndirectedGraph& G) {
	int maxDegree = 0;
	for (int i = 0; i < G.V(); i++) {
		int vDegree = degree(G, i);
		if (maxDegree < vDegree) {
			maxDegree = vDegree;
		}
	}
	return maxDegree;
}

int UndirectedGraph::numberOfSelfLoops(const UndirectedGraph& G) {
	int selfLoops = 0;
	for (unsigned int i = 0; i < G.graph.size(); i++) {
		std::forward_list<int> adj = G.adj(i);
		if (std::find(adj.begin(), adj.end(), i) != adj.end()) {
			selfLoops++;
			continue;
		}
	}
	return selfLoops;
}

std::string UndirectedGraph::toString(const UndirectedGraph& G) {
	std::string retv;
	for (int i = 0; i < G.V(); i++) {
		retv.append("Vertex " + std::to_string(i) + " Edges : ");
		for (auto v : G.adj(i)) {
			retv.append(std::to_string(v) + ' ');
		}
		retv.push_back('\n');
	}
	return retv;
}

int UndirectedGraph::avgDegree(const UndirectedGraph& G) {
	return 2 * G.E() / G.V();
}

UndirectedGraph::UndirectedGraph() : graph(0), vertices(0), edges(0) {
}

UndirectedGraph::UndirectedGraph(int V) : graph(V), vertices(V), edges(0) {
	std::fill(graph.begin(), graph.end(), std::forward_list<int>());
}

UndirectedGraph::UndirectedGraph(const std::initializer_list<std::pair<int, int>>& ls) : graph(ls.size()), vertices(ls.size()), edges(0) {
	std::fill(graph.begin(), graph.end(), std::forward_list<int>());
	for (auto p : ls) {
		auto[first, second] = p;
		checkVertex(first);
		checkVertex(second);
		addEdge(first, second);
	}
}

int UndirectedGraph::V() const {
	return vertices;
}

int UndirectedGraph::E() const {
	return edges;
}

bool UndirectedGraph::areNeighbours(int v, int w) const {
	std::forward_list<int> neighbours = adj(v);
	return std::find(neighbours.begin(), neighbours.end(), w) != neighbours.end();
}

void UndirectedGraph::addEdge(int v, int w) {
	checkVertex(v);
	checkVertex(w);

	if (areNeighbours(v, w)) {
		return;
	}

	if (v == w) {
		addSelfLoop(v);
		return;
	}

	graph[v].push_front(w);
	graph[w].push_front(v);
	edges++;
}

std::forward_list<int> UndirectedGraph::adj(int v) const {
	return graph[v];
}

void UndirectedGraph::clearConnections() {
	graph = std::vector<std::forward_list<int>>(vertices);
	edges = 0;
	std::fill(graph.begin(), graph.end(), std::forward_list<int>());
}

void UndirectedGraph::checkVertex(int v) const {
	if (v < 0 || v > vertices) {
		throw std::invalid_argument("Graph vertex out of range");
	}
}

void UndirectedGraph::addSelfLoop(int v) {
	graph[v].push_front(v);
	edges++;
}