#ifndef ADDNEIGHBOUR_H
#define ADDNEIGHBOUR_H
#include "nodegraphwidget.h"
#include "selecttool.h"


class AddNeighbourTool:public GraphTool
{
public:
    AddNeighbourTool(NodeGraph * graph, NodeGraphWidget *graph_widget);
     bool mousePress(QMouseEvent *event);
};
#endif // ADDNEIGHBOUR_H
