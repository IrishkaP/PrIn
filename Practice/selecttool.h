#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include <graphtool.h>


class SelectTool : public GraphTool
{
public:
    SelectTool(NodeGraph * graph, NodeGraphWidget * graph_widget);

    bool mousePress(QMouseEvent *) override;
    bool mouseRelease(QMouseEvent * event) override;
    bool mouseMove(QMouseEvent * event) override;
    bool keyPress(QKeyEvent *) override;
    void onPaint(QPainter * painter) override;

private:
    QPoint _start_drag;
    Node * _dragged_node = nullptr;
    QVector3D _dragged_node_start;

    bool _selection_box = false;
    QPoint _selection_box_start;
    QPoint _mouse_pos;
};

#endif // SELECTTOOL_H
