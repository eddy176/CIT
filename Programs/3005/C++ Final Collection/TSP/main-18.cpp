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
	std::vector<int> path = g.findAnyPath(1, n);
	double wizeight = g.findWeight(path);
	double tQuality = g.getQuality(wizeight);

	for (size_t i = 0; i < path.size(); i++) {
		std::cout << path[i] << " ";
	}
	std::cout << wizeight << " " << tQuality << std::endl;

    return 0;
}