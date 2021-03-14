#pragma once

#include <string>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>


class Graph
{
private:
	std::set<int> vertices; 
	std::map<int, std::string> verticesValues;
	std::map<int, std::set<int>> neighbours;
	std::map<std::pair<int, int>, int> weights;

	std::list<std::string> closedNodes;

	int fromStringToInt(std::string);
	int getVertexKeyByName(std::string) const;
	void swap(std::pair<std::vector<int>, int>*, std::pair<std::vector<int>, int>*);
	void sortMap(std::vector<std::pair<std::vector<int>, int>>&);
	bool hasVertex(std::string) const;
	void getAllPaths(int, int, std::vector<std::pair<std::vector<int>, int>>&);
	void getAllPathsHelper(int, int, bool*, int*, int&, int&, std::vector<std::pair<std::vector<int>, int>>&);
	bool isCyclicHelper(int, bool*, bool*);
	void BFS(int, std::list<int>&); //is used in isReachable
	void searchForPathsTo(int, std::set<std::pair<int, int>>&);
	bool eulerCycle();
	void print3ShortestPaths(std::vector<std::pair<std::vector<int>, int>>);
	void getEulerCycle(int, std::map<std::pair<int, int>, bool>&, std::vector<std::pair<int, int>>&);
public:
	Graph();
	//Graph(std::set<int>, std::map<int, std::string>, std::map<int, std::set<int>>, std::map<std::pair<int, int>, int>);
	Graph(std::string);
	~Graph();

	Graph& addVertex(int, const std::string&);
	Graph& addEdge(int, int, int);
	int& getEdgeWeight(int, int);
	int getEdgeWeight(int, int) const;
	std::string& getVertex(int); 
	std::string getVertex(int) const; 
	const std::set<int>& getNeighbours(int) const; //
	std::map<int, std::string> getVerticesValues();
	std::list<std::string> getClosedNodes();
	//tasks
	bool isReachable(std::string, std::string); // 1
	void get3ShortestPaths(std::string, std::string); // 2
	void get3ShortestPathsWithClosedNodes(std::string, std::string, std::list<std::string>); // 3 
	bool isCyclicNode(std::string); // 4
	void printTour(std::string); // 5
	bool isReachableToAllNodes(std::string); // 6
	std::set<std::pair<int, int>> allDeadEndEdges(); // 7
	//bonus
	void closeNode(std::string);
	void openNode(std::string);
	void print();
	
	
};

