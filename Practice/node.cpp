#include "node.h"

Node::Node(const QVector3D &position):
    _position(position)
{ }

Node::~Node()
{ }

QVector3D Node::position() const
{
    return _position;
}

std::set<Node *> Node::neighbours() const
{
    return _neighbours;
}

void Node::addNeighbour(Node *neighbour)
{
    if (neighbour == this) return;
    _neighbours.insert(neighbour);
}

float Node::lengthToNeighbour(const Node *neighbour) const
{
    return (position() - neighbour->position()).length();
}
