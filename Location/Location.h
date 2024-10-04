/**
* @brief Assignment 3
* @name Andrew Sabin
*/
#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <iostream>

/*
 * Directions:
 * NORTH = 0
 * EAST = 1
 * SOUTH = 2
 * WEST = 3
 */
enum Direction{
    NORTH,EAST,SOUTH,WEST
};

/*
 * Location Class
 * Private variables-
 * String name = name of the location
 * bool visited = checks to see if it has been visited
 * bool exit = checks to see if it is the exit
 * Location* neighbors[4] gives an array of 4 neighbors for each enumerated direction
 *
 * --
 * Public Functions-
 * Location() = Creates the location object
 * Location(string IocName, bool isTheExit) = Sets the name of the Location object and whether or not it is the Exit
 * getName() = getter to get the name of the location
 * getDescription() = getter to the get the description of the location
 * hasNeighbor() = tests to see if the location has a neighboring location in a specific direction
 * getNeighbor() = getter function for the location's neighbor at a specific direction
 * setNeighbor() = setter function to set the neighbor's location at a specific direction
 * isExit() = tests to see if the location is the exit
 * vist() = sets the location visited value to true
 * isVisited() = tests to see if the location has been visited.
 *
 */

class Location
{
private:
    std::string name;
    bool visited;
    bool exit;
    Location* neighbors[4];


public:
    Location();
    Location(std::string IocName, bool isTheExit);
    std::string getName();
    std::string getDescription();
    bool hasNeighbor(Direction dir);
    Location* getNeighbor(Direction dir);
    void setNeighbor(Direction dir, Location* neighborLoc);
    bool isExit();
    void visit();
    bool isVisited();
};

#endif // LOCATION_H
