#include "Graph.h"
//uncomment this to include your own "heap.h"
//we will assume that you use the same code in your previous assignment
#include "heap.h"

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}


Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}

int Graph::shortestDistance(int s, int d) {
	Heap <nodeWeightPair> heapVertex;

	int* distance = new int[_nv];
	int* true_distance = new int[_nv];
	int* parent = new int[_nv];
	int* path = new int[_nv];

	for (int i = 0; i < _nv; i++) {
		distance[i] = 1e6;
		true_distance[i] = 1e6;
		parent[i] = -1;
		path[i] = -1;
	}

	distance[s] = 0;
	true_distance[s] = 0;
	nodeWeightPair source = nodeWeightPair(s, 0);
	heapVertex.insert(source);

	while (!heapVertex.empty()) {
		nodeWeightPair node = heapVertex.extractMax();
		int nodeWeight = -node.weight();
		int e = node.nodeIndex();
		if (nodeWeight > distance[e])
			continue;

		for (_al[e].start(); !_al[e].end(); _al[e].next()) {
			nodeWeightPair v = _al[e].current();
			if (distance[e] + v.weight() >= distance[v.nodeIndex()]) {
				continue;
			}
			distance[v.nodeIndex()] = distance[e] + v.weight();
			true_distance[v.nodeIndex()] = distance[v.nodeIndex()];
			heapVertex.insert(nodeWeightPair(v.nodeIndex(), -distance[v.nodeIndex()]));
			parent[v.nodeIndex()] = e;
		}
	}

	int return_item = -1;

	//update return_item
	if (true_distance[d] < 1e6) {
		return_item = true_distance[d];
	}
	if (return_item != -1) {
		cout << "Path: ";
		int i = 0;
		for (int traversal = d; traversal != s && traversal != -1; i++) {
			path[i] = traversal;
			traversal = parent[traversal];
		}
		path[i] = s;
		for (int j = i; j >= 0; j--) {
			cout << path[j];
			if (j != 0)
				cout << " ";
		}
		cout << endl;
	}

	delete[] path;
	delete[] parent;
	delete[] distance;
	delete[] true_distance;
	return return_item;
}

/*void printPath(int* node, int idx) {
	if (node[idx] == -1) {
		cout << " ";
		cout << idx;
		return;
	}

	printPath(node, node[idx]);
	cout << " ";
	cout << idx;
}

int Graph::shortestDistance(int s, int d) {

	int* node = (int*)calloc(_nv, sizeof(int));
	bool* dist_travelled = (bool*)calloc(_nv, sizeof(bool));
	int* distance = (int*)calloc(_nv, sizeof(int));
	Heap<nodeWeightPair> heapVertex;

	heapVertex.insert(nodeWeightPair(s, 0));

	for (int i = 0; i < _nv; i++) {
		if (i != s) {
			distance[i] = -1e6;
		}
	}
	node[s] = -1;

	while (!heapVertex.empty()) {
		nodeWeightPair v = heapVertex.extractMax();
		dist_travelled[v.nodeIndex()] = true;
		if (v.nodeIndex() == d) {
			break;
		}
		_al[v.nodeIndex()].start();

		while (!_al[v.nodeIndex()].end()) {
			nodeWeightPair neighbor = _al[v.nodeIndex()].current();
			if (!dist_travelled[neighbor.nodeIndex()] && distance[neighbor.nodeIndex()] < distance[v.nodeIndex()] - neighbor.weight()) {
				if (distance[neighbor.nodeIndex()] == -1e6) {
					heapVertex.insert(nodeWeightPair(neighbor.nodeIndex(), distance[v.nodeIndex()] - neighbor.weight()));
				}
				else {
					heapVertex.increaseKey(neighbor, nodeWeightPair(neighbor.nodeIndex(), distance[v.nodeIndex()] - neighbor.weight()));
				}
				distance[neighbor.nodeIndex()] = distance[v.nodeIndex()] - neighbor.weight();

				node[neighbor.nodeIndex()] = v.nodeIndex();
			}
			_al[v.nodeIndex()].next();
		}
	}
	// Output path
	if (distance[d] != -1e6) {
		cout << "Path:";
		printPath(node, d);
		cout << endl;
	}
	int sd;
	if (distance[d] == -1e6) {
		sd = -1;
	}
	else {
		sd = -distance[d];
	}

	free(dist_travelled);
	free(distance);
	return sd;
}*/

void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}

Graph::~Graph()
{

	delete[] _al;

}