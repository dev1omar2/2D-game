#pragma once
#include <iostream>


#include "Game.h"

#ifndef PATHFINDER_H
#define PATHFINDER_H



class PathFinder
{
public:
    
    Game *m_game = nullptr;
    Node node[25][25];
    std::vector<Node> openSet;
    std::vector<Node> pathList;
    Node startNode, goalNode, currentNode;
    bool goalReached = false;
    int step = 0;

    std::vector<std::vector<Tile>> m_tiles;

    PathFinder();

    PathFinder(Game *game, std::vector<std::vector<Tile>> tiles);
    void initNodes();
    void reset();

    void setNode(int startCol, int startRow, int goalCol, int goalRow);

    void getCoast(Node node);

    bool search();
    void openNode(Node node);
    
    void trackThePath();

};

#endif //PATHFINDER_H
