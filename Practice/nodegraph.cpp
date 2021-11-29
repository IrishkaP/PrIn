#include "nodegraph.h"

NodeGraph::NodeGraph()
{
    for (Node * node : _nodes)
    {
        delete node;
    }
}

const std::set<Node *> & NodeGraph::nodes() const
{
    return _nodes;
}

void NodeGraph::add(Node *node)
{
    _nodes.insert(node);
}

void NodeGraph::removeNode(Node *node)
{

    for (auto i = _nodes.begin(); i != _nodes.end(); i++) {
        if (*i != node) {
            Node * node_1 = *i;
            node_1->removeNeighbour(node);
        }
    }
    _nodes.erase(node);
}
