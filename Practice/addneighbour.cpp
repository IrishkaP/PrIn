#include "addneighbour.h"
#include "node.h"
#include <QMouseEvent>
#include "iostream"

AddNeighbourTool::AddNeighbourTool(NodeGraph * graph, NodeGraphWidget *graph_widget):
    GraphTool(graph,graph_widget)
{}

bool AddNeighbourTool::mousePress(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        QVector3D pos = graphWidget()->windowToGraph(event->pos());
        if (graphWidget()->getHowerNode(pos))
        {
            Node * node = graphWidget()->getHowerNode(pos);
            if (pr == 1 && node != newneighbour)
            {
                newneighbour->addNeighbour(node);
                pr = 0;
                graphWidget()->repaint();
            } else
            if (pr == 0 )
            {
                newneighbour = node;
                pr = 1;
            }
        }
        return true;
    }
    return false;
}
