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

int Graph::shortestDistance(int s, int d)
{
	// implement your code here
	Heap <nodeWeightPair> heapVertex;

	nodeWeightPair source_node;
	for (int i = 0; i < _nv; i++) {
		nodeWeightPair initialise = nodeWeightPair(i, -999999999);
		if (i == s) {
			//set weight of source node to 0 and insert to heap
			source_node = nodeWeightPair(i, 0);
			heapVertex.insert(source_node);
		}
		else {
			//insert the rest with infinity weight 
			heapVertex.insert(initialise);
		}
	}

	int *distance = new int [_nv];
	int *final_dist = new int [_nv];
	int *path = new int [_nv];
	int *parent = new int [_nv];
	for (int i = 0; i < _nv; i ++) {
		if (i == s) {
			distance[s] = 0;
			final_dist[s] = 0;
		}
		distance[i] = -999999999;
		final_dist[i] = -999999999;
		path[i] = -1;
		parent[i] = -1;
	}

	int return_item;
	
	while(!heapVertex.empty()) {
		nodeWeightPair extracted_item = heapVertex.extractMax();
		int extracted_index = extracted_item.nodeIndex();

		//relaxing and update
		for (_al[extracted_index].start(); !_al[extracted_index].end(); _al[extracted_index].next()) {
			nodeWeightPair neighbor = _al[extracted_index].current();
			int neighbor_index = neighbor.nodeIndex();
			int neighbor_weight = neighbor.weight() * -1;

			if (distance[extracted_index] != -999999999 && (distance[extracted_index] + neighbor_weight	> distance[neighbor_index])) {
				distance[neighbor_index] = distance[extracted_index] + neighbor_weight;
				final_dist[neighbor_index] = final_dist[extracted_index] + (-1 * neighbor_weight);
				nodeWeightPair adjusted_neighbor = nodeWeightPair(neighbor_index, distance[neighbor_index]);
				heapVertex.increaseKey(neighbor, adjusted_neighbor);
			}
		}

		if (final_dist[d] == -999999999) {
			return_item = -1;
		} else {
			return_item = final_dist[d];
		}
	}

	if (return_item != -1) {
		cout << "Path: ";
		int traversal = d;
		int i = 0;
		do {
			path[i] = traversal;
			traversal = parent[traversal];
			i++;
		} while(traversal != s && traversal != -1);

		path[i] = s;

		int start = 0;
		int end = i;

		while (start < end) {
			swap(path[start], path[end]);
			start++;
			end++;
		}

		int j = 0;

		if (path[i] == path[j+1]) {
			cout << path[j];
		}
		else {
			for (j = 0; path[j] != -1 && j < _nv; j++)
            {
                cout << path[j];
                if (path[j+1] != -1)
                    cout << " ";
            }
		}
		cout << endl;

	}
	delete[] distance;
    delete[] final_dist;
    delete[] path;
    delete[] parent;
    return return_item;
}

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
