#include "addneighbour.h"
#include <QMouseEvent>

AddNeighbourTool::AddNeighbourTool(NodeGraph * graph, NodeGraphWidget *graph_widget):
    GraphTool(graph,graph_widget)
{}

bool AddNeighbourTool::mousePress(QMouseEvent *event)
{
   /* if (event->button() == Qt::LeftButton)
    {
        QVector3D pos = graphWidget()->windowToGraph(event->pos());
        if (graphWidget()->getHowerNode(pos))
        {
            Node * node = graphWidget()->getHowerNode(pos);
            graph()->removeNode(node);
        }
        //Node * node = new Node(pos);
        //graph()->add(node);
        graphWidget()->repaint();
        return true;
    }*/
    return false;
}
