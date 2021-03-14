#include "Graph.h"

Graph::Graph()
{

}

Graph::Graph(std::string fileName)
{
	//reading from file
	std::ifstream file(fileName, std::ifstream::in);
	std::vector<std::string> wordsOnLine;
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) { // reading line by line
			std::stringstream stream(line);
			std::string temp;
			int root;
			std::string nextName;
			int br = 0;
			while (getline(stream, temp, ' ')) {
				if (br == 0) {
					if (!hasVertex(temp)) {
						addVertex(verticesValues.size(), temp);
					}
					root = getVertexKeyByName(temp);
				}
				else if (br % 2 != 0) {
					if (!hasVertex(temp)) {
						addVertex(verticesValues.size(), temp);
					}
					nextName = temp;
				}
				else if (br % 2 == 0) {
					int tempId = getVertexKeyByName(nextName);
					int number = fromStringToInt(temp);
					addEdge(root, tempId, number);
				}
				br++;
			}
		}
	}
	file.close();
}

Graph::~Graph()
{
	
}
//set and get methods
Graph& Graph::addVertex(int node, const std::string& nodeName)
{
	vertices.insert(node);
	verticesValues[node] = nodeName;
	neighbours[node];
	return *this;
}

Graph& Graph::addEdge(int startNode, int endNode, int weight)
{
	neighbours[startNode].insert(endNode);
	weights[{startNode, endNode}] = weight;
	return *this;
}

int& Graph::getEdgeWeight(int startNode, int endNode)
{
	return weights[{startNode, endNode}];
}

int Graph::getEdgeWeight(int startNode, int endNode) const
{
	assert(weights.count({ startNode, endNode }) > 0);
	return weights.find({ startNode, endNode })->second;
}

std::string& Graph::getVertex(int node)
{
	return verticesValues[node];
}

std::string Graph::getVertex(int node) const
{
	assert(verticesValues.count(node) > 0);
	return verticesValues.find(node)->second;
}

int Graph::getVertexKeyByName(std::string nodeName) const
{
	for (auto& it : verticesValues) {
		if (it.second == nodeName)
		{
			return it.first;
		}
	}
	return -1;
}

const std::set<int>& Graph::getNeighbours(int node) const 
{
	assert(neighbours.count(node) > 0);
	return neighbours.find(node)->second;
}
//functions
int Graph::fromStringToInt(std::string text) //takes a string and parses it to int
{
	int result = 0;
	int size = text.size();
	for (int i = 0; i < size; i++)
	{
		result += (int)pow(10, size - i - 1) * (text[i] - (int)48);
	}
	return result;
}
//bubble sort algorithm
void Graph::swap(std::pair<std::vector<int>, int>* x, std::pair<std::vector<int>, int>* y)
{
	std::pair<std::vector<int>, int> temp = *x;
	*x = *y;
	*y = temp;
}

void Graph::sortMap(std::vector<std::pair<std::vector<int>, int>>& arr)
{
	for (unsigned i = 0; i < arr.size() - 1; i++)
	{
		for (unsigned j = 0; j < arr.size() - i - 1; j++)
		{
			if (arr[j].second > arr[j + 1].second) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

bool Graph::hasVertex(std::string nodeName) const //cheks if vertex already exists in the graph
{
	for (auto& it : verticesValues) {
		if (it.second == nodeName) return true;
	}
	return false;
}

bool Graph::isReachable(std::string startNode, std::string endNode) //uses BFS function
{
	std::list<int> bfsNodes;
	int start = getVertexKeyByName(startNode);
	int end = getVertexKeyByName(endNode);
	BFS(start, bfsNodes);
	std::list<int>::iterator it = bfsNodes.begin();
	for (; it != bfsNodes.end(); it++) {
		if (*it == end) return true;
	}
	return false;
}

void Graph::BFS(int startNode, std::list<int>& nodes)
{
	bool* visited = new bool[vertices.size()]{ false }; //we should delete[] visited
	visited[startNode] = true;
	std::queue<int> tempQueue;
	tempQueue.push(startNode);
	while (!tempQueue.empty()) {
		int curNode = tempQueue.front();
		tempQueue.pop();
		nodes.push_back(curNode);
		std::set<int>::iterator it = neighbours[curNode].begin();
		for (; it != neighbours[curNode].end(); it++)
		{
			if (!visited[*it]) {
				visited[*it] = true;
				tempQueue.push(*it);
				nodes.push_back(*it);
			}
		}
	}
	delete[] visited;
}

bool Graph::isReachableToAllNodes(std::string startNode) //uses isReachable for all nodes
{
	int start = getVertexKeyByName(startNode);
	std::set<int>::iterator itVertices = vertices.begin();
	for (; itVertices != vertices.end(); itVertices++) {
		if (!isReachable(startNode, getVertex(*itVertices)) && start != *itVertices) return false;
	}
	return true;
}

void Graph::print3ShortestPaths(std::vector<std::pair<std::vector<int>, int>> arr)
{
	for (unsigned i = 0; i < arr.size(); i++)
	{
		std::vector<int> temp = arr[i].first;
		for (unsigned j = 0; j < temp.size(); j++)
		{
			std::cout << verticesValues[temp[j]] << " -> ";
		}
		std::cout << arr[i].second << std::endl;
	}
}

//next 3 functions are used to find the 3 shortest paths from node to node
void Graph::get3ShortestPaths(std::string startNode, std::string endNode) // uses getAllPaths
{
	std::vector<std::pair<std::vector<int>, int>> results;
	int start = getVertexKeyByName(startNode);
	int end = getVertexKeyByName(endNode);
	getAllPaths(start, end, results);
	if (results.size() != 0)
		sortMap(results);
	if (results.size() > 3) {
		results.erase(results.begin() + 4, results.end());
	}
	print3ShortestPaths(results);

}

void Graph::getAllPaths(int startNode, int endNode, std::vector<std::pair<std::vector<int>, int>>& results)
{
	bool* visited = new bool[vertices.size()]{ false }; // delete[] visited
	int* path = new int[vertices.size()]; // delete[] path
	int path_index = 0;
	int sumWeight = 0;
	getAllPathsHelper(startNode, endNode, visited, path, path_index, sumWeight, results);
}

void Graph::getAllPathsHelper(int startNode, int endNode, bool* visited, int* path, int& pathIndex, int& sumWeight, std::vector<std::pair<std::vector<int>, int>>& results)
{
	visited[startNode] = true;
	path[pathIndex] = startNode;
	pathIndex++;
	if (startNode == endNode) {
		std::vector<int> temp(pathIndex);
		for (int i = 0; i < pathIndex; i++)
		{
			temp[i] = path[i];
		}
		results.push_back({ temp,sumWeight });
		sumWeight = 0;
	}
	else {
		std::set<int>::iterator it = neighbours[startNode].begin();
		for (; it != neighbours[startNode].end(); it++) {
			if (!visited[*it]) {
				sumWeight += weights[{startNode, * it}];
				getAllPathsHelper(*it, endNode, visited, path, pathIndex, sumWeight, results);
			}
		}

	}
	pathIndex--;
	visited[startNode] = false;
}
//finding 3 shortest paths from node to node, when some nodes are closed
void Graph::get3ShortestPathsWithClosedNodes(std::string startNode, std::string endNode, std::list<std::string> closedNodes)
{
	std::set<int> tempClosedVertices;
	std::list<std::string>::iterator itList = closedNodes.begin();
	for (; itList != closedNodes.end(); itList++) {
		if (hasVertex(*itList)) {
			tempClosedVertices.insert(getVertexKeyByName(*itList));
		}
	}
	Graph graph;
	//addingVerticesExcludingClosed
	std::set<int>::iterator itTempClosedVertices = tempClosedVertices.begin();
	std::set<int>::iterator itVertices = vertices.begin();
	for (itVertices = vertices.begin(); itVertices != vertices.end(); itVertices++) {

		for (itTempClosedVertices = tempClosedVertices.begin(); itTempClosedVertices != tempClosedVertices.end(); itTempClosedVertices++) {
			if (*itVertices == *itTempClosedVertices) {
				continue;
			}
			else {
				graph.addVertex(*itVertices, getVertex(*itVertices));
				break;
			}
		}

	}
	std::map<std::pair<int, int>, int>::iterator itEdges = weights.begin();
	for (itEdges = weights.begin(); itEdges != weights.end(); itEdges++)
	{
		bool flag = false;
		for (itTempClosedVertices = tempClosedVertices.begin(); itTempClosedVertices != tempClosedVertices.end(); itTempClosedVertices++) {
			if (itEdges->first.first != *itTempClosedVertices && itEdges->first.second != *itTempClosedVertices)
				flag = true;
			else if (itEdges->first.first == *itTempClosedVertices || itEdges->first.second == *itTempClosedVertices) {
				flag = false;
				break;
			}
		}
		if (flag)
		{
			graph.addEdge(itEdges->first.first, itEdges->first.second, itEdges->second);
		}
	}
	graph.get3ShortestPaths(startNode, endNode);

	//return results;
}

//next 3 functions search for Euler cycle and print it
bool Graph::eulerCycle() 
{
	//checks if IN and OUT degree is the same
	std::set<int>::iterator it = vertices.begin();
	for (; it != vertices.end(); it++)
	{
		int inEdges = 0;
		int outEdges = 0;

		std::map<std::pair<int, int>, int>::iterator it2 = weights.begin();
		for (; it2 != weights.end(); it2++)
		{
			if (it2->first.first == *it)
			{
				outEdges++;
			}
			if (it2->first.second == *it)
			{
				inEdges++;
			}
		}
		
		if (inEdges != outEdges)
		{
			return false;
		}
	}
	return true;
}

void Graph::getEulerCycle(int node, std::map<std::pair<int, int>, bool>& visitedPaths, std::vector<std::pair<int, int>>& path)
{
	std::set<int>::iterator itNeighbours = neighbours[node].begin();
	for (; itNeighbours != neighbours[node].end(); itNeighbours++)
	{
		std::pair<int, int> tempPath = { node, *itNeighbours };

		if (visitedPaths[tempPath] == false)
		{
			visitedPaths[tempPath] = true;
			path.push_back(tempPath);
			getEulerCycle(*itNeighbours, visitedPaths, path);
		}

	}
}

void Graph::printTour(std::string node)
{

	if (!eulerCycle())
	{
		std::cout << "Tour doesn't exist." << std::endl;
	}

	else
	{
		int start = getVertexKeyByName(node);
		std::vector<std::pair<int, int>> paths;
		std::map<std::pair<int, int>, bool> visitedPaths;
		std::map<std::pair<int, int>, int>::iterator it = weights.begin();
		for (; it != weights.end(); it++)
		{
			visitedPaths[it->first] = false;
		}
		getEulerCycle(start, visitedPaths, paths);
		std::map<std::pair<int, int>, bool>::iterator itVisitedPaths = visitedPaths.begin();
		bool flag = true;
		for (; itVisitedPaths != visitedPaths.end(); itVisitedPaths++)
		{
			if (itVisitedPaths->second == false)
			{
				flag = false;
			}
		}
		if (flag)
		{
			for (unsigned i = 0; i < paths.size(); i++)
			{
				std::cout << getVertex(paths[i].first) << " -> " << getVertex(paths[i].second) << " ";
			}
			std::cout << std::endl;
		}
	}
}

//next 2 functions find cycles in the graph
bool Graph::isCyclicNode(std::string startNode) //uses isCyclicHelper
{
	bool* visited = new bool[vertices.size()]{ false };
	bool* stack = new bool[vertices.size()]{ false };
	int curentNode = getVertexKeyByName(startNode);
	if (isCyclicHelper(curentNode, visited, stack)) {
		delete[] visited;
		delete[] stack;
		return true;
	}
	delete[] visited;
	delete[] stack;
	return false;
}

bool Graph::isCyclicHelper(int curNode, bool* visited, bool* stack)
{
	if (visited[curNode] == false) {
		visited[curNode] = true;
		stack[curNode] = true;
		std::set<int>::iterator it = neighbours[curNode].begin(); 
		for (; it != neighbours[curNode].end(); it++) {
			if (!visited[*it] && isCyclicHelper(*it, visited, stack)) {
				return true;
			}
			else if (stack[*it]) {
				return true;
			}
		}
	}
	stack[curNode] = false;
	return false;
}

//next 2 functions find and print all dead ends
std::set<std::pair<int, int>> Graph::allDeadEndEdges() 
{
	std::map<int, std::set<int>>::iterator itNeighbours = neighbours.begin();
	std::set<std::pair<int, int>> results;
	for (; itNeighbours != neighbours.end(); itNeighbours++)
	{
		if (itNeighbours->second.empty()) {
			searchForPathsTo(itNeighbours->first, results);
		}
	}
	return results;
}

void Graph::searchForPathsTo(int endNode, std::set<std::pair<int, int>>& results) //finds all the nodes that lead to deadEndNode
{
	std::map<int, std::set<int>>::iterator itNeighbours = neighbours.begin();
	for (; itNeighbours != neighbours.end(); itNeighbours++) {
		std::set<int>::iterator itTemp = itNeighbours->second.begin();
		for (; itTemp != itNeighbours->second.end(); itTemp++) {
			if (*itTemp == endNode) {
				results.insert({ itNeighbours->first, endNode });
			}
		}

	}
}

std::map<int, std::string> Graph::getVerticesValues()
{
	return this->verticesValues;
}

std::list<std::string> Graph::getClosedNodes()
{
	return this->closedNodes;
}

//open and close nodes
void Graph::closeNode(std::string node)
{
	bool flag = false;
	std::map<int, std::string>::iterator it = verticesValues.begin();
	for (; it != verticesValues.end(); it++)
	{
		if (it->second == node)
		{
			flag = true;
		}
	}
	if (flag)
	{
		closedNodes.push_back(node);
	}
	else
	{
		std::cout << "There is not open node with that name" << std::endl;
	}

}

void Graph::openNode(std::string node)
{
	closedNodes.remove(node);
}

void Graph::print()
{
	std::map<std::pair<int, int>, int>::iterator itEdges = weights.begin();
	for (; itEdges != weights.end(); itEdges++) {
		std::cout << verticesValues[itEdges->first.first] << " -> ";
		std::cout << verticesValues[itEdges->first.second] << " = ";
		std::cout << itEdges->second << std::endl;
	}
}
