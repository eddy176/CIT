#include "graph.h"

Graph::Graph(int vertices) :
	mVerts(vertices), mMinWeight(10000), mMaxWeight(0) {
	mEdgeWeights.resize((mVerts + 1), std::vector<double>(mVerts + 1));
}

// returns number of vertices
int Graph::getNumVertices() const {
	return mVerts;
}

// adds edges to build the graph( v0, v1, weight )
void Graph::addEdges(int v0, int v1, double weight) {
	mEdgeWeights[v0].at(v1) = weight;	// mEdgeWeights[i]= outer, at(j)= inner
	if (weight > mMaxWeight) {			// finding the maximum weight
		mMaxWeight = weight;			// setting the constructor's max to current
	}
	if (weight < mMinWeight) {			// finding the minimum weight
		mMinWeight = weight;			// setting the constructor's min to current
	}
}

// find any path from beginning to end of vector
std::vector<int> Graph::findAnyPath(int v0, int v1) {
	int i;
	std::vector<int> path;
	for (i = 1; i < mVerts + 1; i++) {
		path.push_back(i);
	}
	return path;
}

// finding total weight of the path
double Graph::findWeight(std::vector<int>& path) const {
	size_t i;
	double total = 0;
	for (i = 0; i < path.size() - 1; i++) { // loop over path's size
		total += this->getWeight(path[i], path[i + 1]); // add a total of the weight
	}
	total += this->getWeight(path[0], path[path.size() - 1]);
	return total;
}

// finding the weight between two vertices
double Graph::getWeight(int v0, int v1) const {
	return mEdgeWeights[v0][v1];
}

double Graph::getQuality(double weight) {
	mMinWeight *= mVerts;
	mMaxWeight *= mVerts;
	return (1 - (weight - mMinWeight) / (mMaxWeight - mMinWeight));
}

//std::vector<int> Graph::shuffle(std::vector<int> path) {
//	random_shuffle(path.begin() + 1, path.end());
//	return path;
//}

//std::vector<double> Graph::randomNeighbor(std::vector<double> path) {
//	path = shuffle(path);
//	std::vector<double> cn;
//	cn.push_back(path[0]);
//	cn.push_back(path[1]);
//	return cn;
//}

//std::vector<double> Graph::bestPath(int v0, int v1) {
//	std::vector<int> path = this->findAnyPath(v0, v1);
//	std::vector<int> newPath;
//	double weight = this->findWeight(path);
//	double newWeight;
//	for (size_t i = 0; i < path.size(); i++) {
//		std::vector<int> newPath = this->shuffle(path);
//		double newWeight = this->findWeight(newPath);
//		if (newWeight < weight) {
//			path = newPath;
//		}
//	}
//	std::vector<double> dub;
//	for (size_t i = 0; i < path.size(); i++) {
//		dub.push_back((double)path[i]);
//	}
//	dub.push_back(newWeight);
//	return dub;
//}

//std::vector<double> bestNeightbor(std::vector<int> cycle, double quality) {
//	double bestQ = quality;
//	std::vector<int> bestC = cycle;
//	for (size_t i = 0; i < 1000; i++) {
//
//	}
//	std::vector<double> bestQVector.push_back(bestC);
//	return bestQ;
//}