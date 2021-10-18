#include "selecttool.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <Qpainter>

SelectTool::SelectTool(NodeGraph * graph, NodeGraphWidget * graph_widget):
    GraphTool(graph,graph_widget)
{}

bool SelectTool::mousePress(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        Node * hover = graphWidget()->getHowerNode(QVector3D(event->pos()));
        if(hover)
        {
            _dragged_node = hover;
            _dragged_node_start = _dragged_node->position();
            _start_drag = event->pos();
            graphWidget()->setCursor(Qt::ClosedHandCursor);
            return true;
        }
        else
        {
            _selection_box = true;
            _selection_box_start = event->pos();
        }
    }
    return false;
}

bool SelectTool::mouseRelease(QMouseEvent * event)
{
    if(_dragged_node && event->button() == Qt::LeftButton)
    {
        _dragged_node = nullptr;
        graphWidget()->setCursor(Qt::ArrowCursor);
        return true;
    }
    else if (_selection_box)
    {
        _selection_box = false;
        graphWidget()->repaint();
        return true;
    }
    return false;
}

bool SelectTool::mouseMove(QMouseEvent * event)
{
    _mouse_pos = event->pos();
    if (_dragged_node)
    {
        QVector3D delta = QVector3D(QPointF(event->pos()) - QPointF(_start_drag)) / graphWidget()->scale();
        _dragged_node->setPosition(_dragged_node_start + delta);
        graphWidget()->repaint();
        return true;
    }
    else if (_selection_box)
    {
        graphWidget()->repaint();
        return true;
    }
    return false;
}

bool SelectTool::keyPress(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Delete)
    {
        return true;
    }
    return false;
}

void SelectTool::onPaint(QPainter * painter)
{
    if (_selection_box)
    {
        painter->save();
        painter->setPen(Qt::darkBlue);
        painter->setBrush(QColor(150,150,250,70));
        painter->drawRect(QRect(_selection_box_start,_mouse_pos));

        painter->restore();
    }
}
