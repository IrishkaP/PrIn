#ifndef NODE_H
#define NODE_H
#include <set>
#include <QVector3D>


class Node
{
public:
    Node(const QVector3D & position = QVector3D());
    virtual ~Node();

    QVector3D position() const;

    std::set<Node * > neighbours() const;

    void addNeighbour(Node * neighbour);

    virtual float lengthToNeighbour(const Node * neighbour) const;

private:

    QVector3D _position;
    std::set<Node *> _neighbours;
};

#endif // NODE_H