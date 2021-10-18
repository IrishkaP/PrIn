#ifndef GRAPHTOOL_H
#define GRAPHTOOL_H
#include <QWidget>
#include <nodegraph.h>
#include <nodegraphwidget.h>


class GraphTool
{
public:
    GraphTool(NodeGraph * graph, NodeGraphWidget * graph_widget);

    NodeGraph * graph() const;
    NodeGraphWidget * graphWidget() const;

    //обработчики событий

    virtual bool mousePress(QMouseEvent *) {return false;}
    virtual bool mouseRelease(QMouseEvent *) {return false;}
    virtual bool mouseMove(QMouseEvent *) {return false;}
    virtual bool mouseWheel(QWheelEvent *) {return false;}
    virtual bool keyPress(QKeyEvent *) {return false;}
    virtual bool keyRelease(QKeyEvent *) {return false;}

    virtual void onPaint(QPainter *) {}
private:
    NodeGraph * _graph;
    NodeGraphWidget * _graph_widget = nullptr;
};

#endif // GRAPHTOOL_H
