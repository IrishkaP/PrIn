#include "createnodetool.h"
#include <QMouseEvent>

CreateNodeTool::CreateNodeTool(NodeGraph * graph, NodeGraphWidget *graph_widget):
    GraphTool(graph,graph_widget)
{}

bool CreateNodeTool::mousePress(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QVector3D pos = graphWidget()->windowToGraph(event->pos());
        Node * node = new Node(pos);
        graph()->add(node);
        graphWidget()->repaint();
        return true;
    }
    return false;
}
