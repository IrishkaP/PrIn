#ifndef REMOVENODETOOL_H
#define REMOVENODETOOL_H
#include "nodegraphwidget.h"
#include "selecttool.h"


class RemoveNodeTool:public GraphTool
{
public:
    RemoveNodeTool(NodeGraph * graph, NodeGraphWidget *graph_widget);
     bool mousePress(QMouseEvent *event);
};

#endif // REMOVENODETOOL_H
