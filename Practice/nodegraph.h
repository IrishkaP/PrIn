#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <set>
#include "node.h"


class NodeGraph
{
public:
    NodeGraph();

    const std::set<Node *> & nodes() const;
    void add(Node * node);
    void removeNode(Node * node);
    void removeAllNodes();
    int countNodes();

private:
    std::set<Node *> _nodes;
};

#endif // NODEGRAPH_H
