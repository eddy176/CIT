#include "graph.h"

int main() {
	srand(time(NULL));
    size_t i, n;
    std::cin >> n;
	int v0, v1;
	double weight;
	Graph g(n);
	for (i = 0; i < (n * (n-1)); i++){
		std::cin >> v0 >> v1 >> weight;
		g.addEdges(v0, v1, weight);
    }
	std::vector<double> path = g.findAnyPath(1, n);
	double wizeight = g.findWeight(path);
	double tQuality = g.getQuality(wizeight);
	std::vector<double> goodPath = g.bestPath(path, tQuality);
	double wizleight = g.findWeight(goodPath);
	double bestQuality = goodPath[goodPath.size() - 1];
	goodPath.pop_back();
	for (size_t i = 0; i < goodPath.size(); i++) {
		std::cout << goodPath[i] << " ";
	}
	std::cout << wizleight << " " << bestQuality << std::endl;

    return 0;
}