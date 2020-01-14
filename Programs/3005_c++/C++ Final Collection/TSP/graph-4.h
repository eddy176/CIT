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
	std::vector<int> findAnyPath(int v0, int v1);
    double findWeight( std::vector<int>& path)const;
	double getWeight(int v0, int v1) const;
	double getQuality(double weight);
    //std::vector<int> shuffle(std::vector<int> path);
	/*std::vector<double> randomNeighbor(std::vector<int> path);
	std::vector<double> bestPath(int v0, int v1);
	std::vector<double> bestNeightbor(std::vector<int> cycle, double quality);*/


protected:

    std::vector<std::vector<double>> mEdgeWeights;
	int mNumVertices;
	int mVerts;
	double mMinWeight;
	double mMaxWeight;
};

#endif
