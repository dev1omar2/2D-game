#include "PathFinder.h"



PathFinder::PathFinder()
{

}

PathFinder::PathFinder(Game *game, std::vector<std::vector<Tile>> &tiles)
    : m_game(game), m_tiles(tiles)
{
    

    initNodes();
}
void PathFinder::initNodes()
{
    int col = 0;
    int row = 0;

    while (col < m_game->columns && row < m_game->rows)
    {
        node[col][row] = Node(col, row);
        col++;

        if (col == m_game->columns)
        {
            col = 0;
            row++;
        }
    }

}
void PathFinder::reset()
{
    int col = 0;
    int row = 0;

    while (col < m_game->columns && row < m_game->rows)
    {
        node[col][row].checked = false;
        node[col][row].open = false;
        node[col][row].solid = false;


        col++;

        if (col == m_game->columns)
        {
            col = 0;
            row++;
        }
    }

    openSet.clear();
    pathList.clear();

    goalReached = false;
    step = 0;
}

void PathFinder::setNode(int startCol, int startRow, int goalCol, int goalRow)
{
    reset();

    startNode = node[startCol][startRow];
    currentNode = startNode;
    goalNode = node[goalCol][goalRow];

    openSet.push_back(currentNode);

    int col = 0;
    int row = 0;

    while (col < m_game->columns && row < m_game->rows)
    {
        Tile tileNum = m_tiles[col][row];
        if (tileNum.isSolid)
        {
            node[col][row].solid = true;
        }
        col++;




        getCoast(node[col][row]);

        col++;
        if (col == m_game->columns)
        {
            col = 0;
            row++;
        }
    }
}

void PathFinder::getCoast(Node node)
{

    // G coast
    int XDistance = std::abs(node.col - startNode.col);
    int YDistance = std::abs(node.row - startNode.row);
    node.gCoast = XDistance + YDistance;

    // H coast
    XDistance = std::abs(node.col - goalNode.col);
    YDistance = std::abs(node.row - goalNode.row);
    node.hCoast = XDistance + YDistance;

    //F coast
    node.fCoast = node.gCoast + node.hCoast;

}

bool PathFinder::search()
{
    while (!goalReached && step < 500)
    {
        int col = currentNode.col;
        int row = currentNode.row;

        currentNode.checked = true;
        openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());

        //open the up node
        if (row - 1 >= 0)
        {
            openNode(node[col][row - 1]);
        }
        // open the left node
        if (col - 1 >= 0)
        {
            openNode(node[col - 1][row]);

        }
        if (row + 1 < m_game->rows)
        {
            openNode(node[col][row + 1]);
        }
        // open right node
        if (col + 1 < m_game->columns)
            openNode(node[col + 1][row]);

        int bestNodeIndex = 0;
        int bestNodefCoast = 999;

        for (int i = 0; i < openSet.size(); i++)
        {
            if (openSet[i].fCoast < bestNodefCoast) {
                bestNodeIndex = i;
                bestNodefCoast = openSet[i].fCoast;
            }
            else if (openSet[i].fCoast == bestNodefCoast)
            {
                if (openSet[i].gCoast < openSet[bestNodeIndex].gCoast)
                {
                    bestNodeIndex = i;
                }
            }

            if (openSet.empty())
            {
                break;
            }

            currentNode = openSet[bestNodeIndex];

            if (currentNode == goalNode)
            {
                goalReached = true;
                trackThePath();
            }
        }
        step++;
    }
    return goalReached;
}
void PathFinder::openNode(Node node)
{
    if (!node.open && !node.checked && !node.solid)
    {
        node.open = true;
        node.Parent = &currentNode;
        openSet.push_back(node);
    }
}
void PathFinder::trackThePath()
{
    Node current = goalNode;
    while (current.Parent != nullptr)
    {
        pathList.push_back(current);
        current = *current.Parent;
        
    }
}