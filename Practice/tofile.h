#ifndef TOFILE_H
#define TOFILE_H
#include "nodegraphwidget.h"
#include "selecttool.h"
#include "nodegraph.h"

class ToFile: public GraphTool
{
public:
    ToFile(NodeGraph * graph, NodeGraphWidget *graph_widget);
    bool mousePress(QMouseEvent *event);
};

#endif // TOFILE_H
