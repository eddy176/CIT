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
std::vector<double> Graph::findAnyPath(int v0, int v1) {
	int i;
	std::vector<double> path;
	for (i = 1; i < mVerts + 1; i++) {
		path.push_back(i);
	}
	return path;
}

// finding total weight of the path
double Graph::findWeight(std::vector<double>& path) const {
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

std::vector<double>& Graph::shuffle(std::vector<double>& path) {
	int r = rand() % (path.size() - 1) + 1;
	int p1 = path[1];
	path[1] = path[r];
	path[r] = p1;
	return path;
}

std::vector<double> Graph::bestPath(std::vector<double>& path, double quality) {
	std::vector<double> bestPath;
	std::vector<double> currentPath = shuffle(path);
	double currentWeight = findWeight(currentPath);
	double currentQuality = getQuality(currentWeight);
	double bestQuality = quality;
	while(currentQuality > bestQuality){
		bestQuality = currentQuality;
		bestPath = currentPath;
		for (size_t i = 0; i < 1000; i++) {
			std::vector<double> rNeighbors = bestNeightbor(bestPath, bestQuality);
			double rQuality = rNeighbors[rNeighbors.size() - 1];
			rNeighbors.pop_back();
			if (rQuality > bestQuality) {
				currentQuality = rQuality;
				bestPath = rNeighbors;
				break;
			}
		}
	}
	bestPath.push_back(bestQuality);
	return bestPath;
}

std::vector<double> Graph::bestNeightbor(std::vector<double>& cycle, double quality) {
	double bestQ = quality;
	std::vector<double> bestC = cycle;
	for (size_t i = 0; i < 1000; i++) {
		std::vector<double> rC = shuffle(bestC);
		double rWeight = this->findWeight(rC);
		double rQ = this->getQuality(rWeight);
		if (rQ > bestQ) {
			bestQ = rQ;
			bestC = rC;
		}
	}
	bestC.push_back(bestQ);
	return bestC;
}