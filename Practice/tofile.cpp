#include "tofile.h"
#include <QMouseEvent>
#include <fstream>
#include <iostream>
#include <set>
#include <map>

void saveTo(const QString & filename, const NodeGraph * graph)
{
    std::ofstream out;
    out.open(filename.toLatin1().data());

    if (!out.is_open())
    {
        // Error
        return;
    }

    out << graph->countNodes() << std::endl;

    std::map<Node *, int> nodes_id;
    std::set <Node *> nodes = graph->nodes();

    int id = 0;
    for (auto node : nodes)
    {
        nodes_id[node] = id;
        ++id;
        QVector3D pos = node->position();
        out << id << " " << pos.x() << " " << pos.y() <<  " " << pos.z() << std::endl;
    }

    for (auto nodeIter : nodes_id)
    {
        Node * node = nodeIter.first;
        for (auto neighbour : node->neighbours())
        {
            int node_id = nodeIter.second;
            int neighbour_id = nodes_id[neighbour];
            out << node_id << " " << neighbour_id << std::endl;
        }
    }
}

inline Node * findNode(const std::map<int, Node *> & nodes_id, int id)
{
    auto node_iter = nodes_id.find(id);
    return node_iter != nodes_id.end() ? node_iter->second : nullptr;
}

void load (const QString & filename, NodeGraph * graph, NodeGraphWidget *graph_widget)
{
    std::ifstream in;
    in.open(filename.toLatin1().data());
    std::map<int, Node *> nodes_id;
    if (!in.is_open())
    {
        // Error
        return;
    }
    graph->removeAllNodes();
    int countNode, id;
    QVector3D pos;
    in >> countNode;
    for (int countStr = 0; countStr < countNode; countStr++)
    {
        in >> id >> pos[0] >> pos[1] >> pos[2];
        Node * newNode = new Node(pos);
        graph->add(newNode);
        nodes_id[id] = newNode;

    }
    while(!in.eof())
    {
        int id_first_node, id_second_node;
        in >> id_first_node >> id_second_node;
        Node * first_node = findNode(nodes_id, id_first_node);
        Node * second_node = findNode(nodes_id, id_second_node);
        if (first_node && second_node)
        {
            first_node->addNeighbour(second_node);
        }
        else
        {
            // error
        }

    }
    graph_widget->repaint();
}

