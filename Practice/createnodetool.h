#ifndef CREATENODETOOL_H
#define CREATENODETOOL_H
#include "nodegraphwidget.h"
#include "selecttool.h"


class CreateNodeTool  :public GraphTool
{
public:
    CreateNodeTool(NodeGraph * graph, NodeGraphWidget *graph_widget);
    bool mousePress(QMouseEvent *event);
};

#endif // CREATENODETOOL_H
