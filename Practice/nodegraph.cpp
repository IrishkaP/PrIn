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
    _nodes.erase(node);
}
