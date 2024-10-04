/**
* @brief Assignment 3
* @name Andrew Sabin
*/
#include "Location.h"
#include <iostream>
#include <string>


Location::Location()
{
    name = "?";
    neighbors[0] = {nullptr};
    neighbors[1] = {nullptr};
    neighbors[2] = {nullptr};
    neighbors[3] = {nullptr};
    exit = false;
    visited = false;
}
Location::Location(std::string IocName, bool isTheExit){
    name = IocName;
    exit = isTheExit;
    visited = false;
    neighbors[0] = {nullptr};
    neighbors[1] = {nullptr};
    neighbors[2] = {nullptr};
    neighbors[3] = {nullptr};
}
bool Location::hasNeighbor(Direction dir){
    if (dir == NORTH){
        if (neighbors[0] != nullptr)
            return true;
        else
            return false;
    }
    else if (dir == EAST){
        if (neighbors[1] != nullptr)
            return true;
        else
            return false;
    }
    else if (dir == SOUTH){
        if (neighbors[2] != nullptr)
            return true;
        else
            return false;
    }
    else if (dir == WEST){
        if (neighbors[3] != nullptr)
            return true;
        else
            return false;
    }
    else
        return false;
}
Location* Location::getNeighbor(Direction dir){
    if (dir == NORTH)
        return neighbors[0];
    else if (dir == EAST)
        return neighbors[1];
    else if (dir == SOUTH)
        return neighbors[2];
    else if (dir == WEST)
        return neighbors[3];
}

void Location::setNeighbor(Direction dir, Location* neighborLoc){
    if (dir == NORTH){
        neighbors[0] = neighborLoc;
    }
    else if (dir == EAST)
        neighbors[1] = neighborLoc;
    else if (dir == SOUTH)
        neighbors[2] = neighborLoc;
    else if (dir == WEST)
        neighbors[3] = neighborLoc;
}

std::string Location::getName(){
    return name;

}
std::string Location::getDescription(){
    std::string listOfExits;
    if(getNeighbor(NORTH) != nullptr)
        listOfExits += " North";
    if(getNeighbor(EAST) != nullptr)
        listOfExits += " East";
    if(getNeighbor(SOUTH) != nullptr)
        listOfExits += " South";
    if(getNeighbor(WEST) != nullptr)
        listOfExits += " West";
    std::string fullDescription = getName() + ". Exits:" + listOfExits +". ";
    if(isVisited() == true)
        fullDescription += "You have visted this location.";
   return fullDescription;
}


bool Location::isExit(){
    if (exit == true)
       return true;
    else
        return false;
}
void Location::visit(){
    visited = true;
}
bool Location::isVisited(){
    if (visited == true)
        return true;
    else
        return false;
}
