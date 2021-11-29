#ifndef NEWGRAPH_H
#define NEWGRAPH_H
#include "nodegraphwidget.h"
#include "selecttool.h"


class NewGraph : public GraphTool
{
public:
    NewGraph(NodeGraph * graph, NodeGraphWidget *graph_widget);
    bool mousePress(QMouseEvent *event);
};

#endif // NEWGRAPH_H

