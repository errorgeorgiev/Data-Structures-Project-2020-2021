#include "UI.h"

UI::UI()
{
    
}

UI::UI(std::string fileName) : map(fileName)
{
    setCurrentLocation(0, map.getVerticesValues()[0]);
}

UI::UI(const UI& rhs)
{
    this->map = rhs.map;
    this->currentLocation = rhs.currentLocation;
}

UI& UI::operator = (const UI& rhs)
{
    if (this != &rhs)
    {
        this->map = rhs.map;
        this->currentLocation = rhs.currentLocation;

    }
    return *this;
}

UI::~UI()
{

}
void UI::load()
{
    while (1)
    {
        std::string newCommand;
        std::getline(std::cin,newCommand); 
        readCommand(newCommand);
    }
}

void UI::readCommand(std::string command)
{
    if (isOneWord(command))
    {
        if (command == "location")
        {
            location();
        }
        else if (command == "neighbours")
        {
            neighbours();
        }
        else if (command == "closed")
        {
            closed();
        }
        else if (command == "tour")
        {
            tour();
        }
        else if (command == "print")
        {
            print();
        }
        else if (command == "exit")
        {
            exit(0); //not sure if this is good practice
        }
    }
    else
    {
        if (divideIntoTwoWords(command).first == "change")
        {
            change(divideIntoTwoWords(command).second);
        }
        else if (divideIntoTwoWords(command).first == "move")
        {
            move(divideIntoTwoWords(command).second);
        }
        else if (divideIntoTwoWords(command).first == "close")
        {
            close(divideIntoTwoWords(command).second);
        }
        else if (divideIntoTwoWords(command).first == "open")
        {
            open(divideIntoTwoWords(command).second);
        }
    }
}

bool UI::isOneWord(std::string command)
{
    bool flag = true;
    for (unsigned i = 0; i < command.size(); ++i)
    {
        if (command[i] == ' ')
        {
            flag = false;
        }
    }
    return flag;
}

std::pair<std::string, std::string> UI::divideIntoTwoWords(std::string command)
{
    std::string word1 = "";
    std::string word2 = "";
    if (!isOneWord(command)) 
    {
        bool flag = 0;
        for (auto x : command)
        {
            if (x == ' ')
            {
                flag = 1;
            }
            else if (flag == 0)
            {
                word1 += x;
            }
            else
            {
                word2 += x;
            }
        }
    }
    std::pair<std::string, std::string> answer;
    answer.first = word1;
    answer.second = word2;
    return answer;
}

std::pair<int, std::string> UI::getCurrentLocation()
{
    return this->currentLocation;
}

void UI::setCurrentLocation(int first, std::string second)
{
    this->currentLocation.first = first;
    this->currentLocation.second = second;

}

void UI::location()
{
    std::cout << getCurrentLocation().second << std::endl;
}

void UI::change(std::string name)
{
    // we loop through all the nodes and if there is a node with the certain name , we change
    // the currentNode to its name
    // else : we print that there is not a node with that name 
    bool flag = false;
    std::map<int, std::string> temp = this->map.getVerticesValues();
    std::map<int, std::string>::iterator it = temp.begin();
    for (; it != temp.end(); it++)
    {
        if (it->second == name)
        {
            flag = true;
            setCurrentLocation(it->first, it->second);
        }
    }
    if (!flag)
    {
        std::cout << "There is not a node with that name" << std::endl;
    }
}
//working
void UI::neighbours()
{
    //couts all the neighbours of the currentNode
    std::set<int> neighs = map.getNeighbours(currentLocation.first);
    for (auto x : neighs)
    {
        std::cout << map.getVerticesValues()[x] << std::endl;
    }
}

void UI::move(std::string name)
{
    map.get3ShortestPaths(currentLocation.second, name);
    change(name);

}

void UI::closed()
{
    std::list<std::string> newClosedNodes = map.getClosedNodes();

    std::list<std::string>::iterator it = newClosedNodes.begin();
    for (; it != newClosedNodes.end(); it++)
    {
        std::cout << it->data() << std::endl;
    }
}

void UI::tour()
{
    map.printTour(currentLocation.second);
}

void UI::print()
{
    map.print();
}

void UI::open(std::string name)
{
    map.openNode(name);
}

void UI::close(std::string name)
{
    map.closeNode(name);
}