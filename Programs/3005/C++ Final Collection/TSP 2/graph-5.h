#ifndef _GRAPH_H
#define _GRAPH_H
#include <vector>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>

class Graph{
 public:
	 Graph(int vertices);
	int getNumVertices() const;
	void addEdges(int v0, int v1, double weight); // adds edges
	std::vector<double> findAnyPath(int v0, int v1);
    double findWeight( std::vector<double>& path)const;
	double getWeight(int v0, int v1) const;
	double getQuality(double weight);
    std::vector<double>& shuffle(std::vector<double>& path);
	//std::vector<double> randomNeighbor(std::vector<int>& path);
	std::vector<double> bestPath(std::vector<double>& path, double quality);
	std::vector<double> bestNeightbor(std::vector<double>& cycle, double quality);


protected:

    std::vector<std::vector<double>> mEdgeWeights;
	int mNumVertices;
	int mVerts;
	double mMinWeight;
	double mMaxWeight;
};

#endif
