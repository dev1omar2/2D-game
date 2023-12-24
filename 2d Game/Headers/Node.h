#pragma once


class Node
{
public:
    Node* Parent;
    int row;
    int col;
    int gCoast;
    int hCoast;
    int fCoast;

    bool solid;
    bool open;
    bool checked;

    Node();

    Node(int col, int row)
    {
        this->col = col;
        this->row = row;
    }

    bool operator==(const Node& other) const
    {
        return (this->row == other.row && this->col == other.col);
    }

};
