#include "newgraph.h"
#include <QMouseEvent>
#include "iostream"

NewGraph::NewGraph(NodeGraph * graph, NodeGraphWidget *graph_widget):
    GraphTool(graph,graph_widget)
{}

bool NewGraph::mousePress(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        graph()->removeAllNodes();
        graphWidget()->repaint();
        return true;
    }
    return false;
}
