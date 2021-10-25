#include "graphtool.h"


GraphTool::GraphTool(NodeGraph * graph, NodeGraphWidget * graph_widget):
    _graph(graph), _graph_widget(graph_widget)
{

}

NodeGraphWidget *GraphTool::graphWidget() const
{
    return _graph_widget;
}

NodeGraph *GraphTool::graph() const
{
    return _graph;
}
