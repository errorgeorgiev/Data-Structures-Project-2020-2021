#include "UI.h"

using namespace std;

int main()
{
	//examples for the first seven functions
	Graph map("info.txt");
	map.isReachable("Popa", "NDK"); //1
	map.get3ShortestPaths("BSFS", "NDK"); //2
	map.get3ShortestPathsWithClosedNodes("BSFS", "NDK", map.getClosedNodes()); //3
	map.isCyclicNode("BSFS"); //4
	map.printTour("NDK"); //5
	map.isReachableToAllNodes("RuskiPametnik"); //6
	map.allDeadEndEdges(); //7

	//UI interface("info.txt");
	//interface.load();

	return 0;
};
