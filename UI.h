#pragma once
#include "Graph.h"
#include <cstdlib>

class UI
{
private:
    Graph map;
    std::pair<int, std::string> currentLocation;

public:
    UI();
    UI(std::string);
    UI(const UI&);
    UI& operator = (const UI&);
    ~UI();

    void load();
    void readCommand(std::string);
    bool isOneWord(std::string);
    std::pair<std::string, std::string> divideIntoTwoWords(std::string);

    std::pair<int, std::string> getCurrentLocation();
    void setCurrentLocation(int, std::string);

    void location(); // 1
    void change(std::string); // 2
    void neighbours(); // 3
    void move(std::string); // 4
    void close(std::string); // 5
    void open(std::string); // 6
    void closed(); // 7
    void tour(); // 8
    void print(); // bonus

};