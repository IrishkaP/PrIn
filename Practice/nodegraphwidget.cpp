#include "nodegraphwidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <iostream>
#include <graphtool.h>

    const float node_radius = 10;
    static Node * nol;

NodeGraphWidget::NodeGraphWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

NodeGraph * NodeGraphWidget::graph() const
{
    return _graph;
}

void NodeGraphWidget::setGraph(NodeGraph *graph)
{
    _graph = graph;
}

void NodeGraphWidget::drawEdge(QPainter &painter, Node *from, Node *to, float node_radius)
{
    painter.save();

    QColor arrow_color = QColor(Qt::darkBlue);

    painter.setPen(QPen(arrow_color, 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    painter.setBrush(arrow_color);

    QVector3D delta = to->position() - from->position();
    QVector3D direction = delta.normalized();
    QPointF start = (from->position() + direction * node_radius).toPointF();
    QPointF end = (to->position() - direction * node_radius).toPointF();



    painter.drawLine(start,end);

    delta.normalize();
    QVector3D end_5 = (to->position() - direction  * node_radius * 2);

    double chislo = delta.x();

    delta.setX(-delta.y());
    delta.setY(chislo);

    QVector3D norm = (delta);

    QPointF t0 = (end_5 + norm * 2).toPointF();
    QPointF t1 = (end_5 - norm * 2).toPointF();
    QPointF points[3] = {t0,t1,end};

    painter.drawPolygon(points,3);


    painter.restore();
}

Node * NodeGraphWidget::getHowerNode(QVector3D point)
{
    for (Node * node : graph()->nodes())
    {
        if ((point-node->position()).length() <= node_radius)
        {
            return node;
        }
    }
    return nullptr;
}

void NodeGraphWidget::setTool(std::shared_ptr<GraphTool> tool)
{
    _currentTool = tool;
}

float NodeGraphWidget::scale() const
{
    return _scale;
}

void NodeGraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.fillRect(painter.viewport(), Qt::white);

    painter.translate(_offset);
    painter.scale(_scale, _scale);

    if (_graph == nullptr)
    {
        return;
    }



    for (auto node : _graph->nodes())
    {
        painter.setPen(QColor(Qt::black));
        painter.setBrush(QColor(Qt::red));
        painter.drawEllipse(node->position().toPointF(), node_radius, node_radius);

        for (auto neighbour : node->neighbours())
        {
            drawEdge(painter, node,neighbour, node_radius);
        }
    }
    if (_currentTool) _currentTool->onPaint(&painter);
}

static float clamp(float value, float min, float max)
{
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

void NodeGraphWidget::wheelEvent(QWheelEvent *event)
{
    QVector3D cursor_pos_in_graph = windowToGraph(event->posF());

    _scale *= 1.0 +0.05 * event->angleDelta().y() / 120;

    _scale = clamp(_scale, 0.1, 10);

    QPointF delta = event->pos() - graphToWindow(cursor_pos_in_graph);
    _offset += delta;

    if (_currentTool) _currentTool->mouseWheel(event);

    repaint();
}

void NodeGraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (!_mouse_dragging && event->button() == Qt::RightButton)
    {
        _mouse_dragging = true;
        _start_drag = event->pos();
        _start_offset = _offset.toPoint();
        setCursor(QCursor(Qt::ClosedHandCursor));
    }

    if (!_mouse_dragging && event->button() == Qt::LeftButton) {
        _start_drag = event->pos();
        _start_offset = _offset.toPoint();
        setCursor(QCursor(Qt::ClosedHandCursor));
        if (getHowerNode(windowToGraph(_start_drag)) != nullptr)
        {
                   _mouse_dragging_l = true;
                   nol = getHowerNode(windowToGraph(_start_drag));
        }
    }
    if (_currentTool) _currentTool->mousePress(event);
}

void NodeGraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (_mouse_dragging)
    {
        _offset = _start_offset + (event->pos() - _start_drag);
        repaint();
    }else
    if (_mouse_dragging_l) {
       nol->setPosition(windowToGraph(event->pos()));
       repaint();
    } else if (!(_currentTool && _currentTool->mouseMove(event)))
    {
        setCursor(getHowerNode(QVector3D(event->pos())) ? Qt::OpenHandCursor : Qt::ArrowCursor);
    }
}

void NodeGraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (_mouse_dragging && event->button() == Qt::RightButton)
    {
        _mouse_dragging = false;
        setCursor(QCursor(Qt::ArrowCursor));
    } else if (_currentTool) _currentTool->mouseRelease(event);
    if (!_mouse_dragging && event->button() == Qt::LeftButton) {
        _mouse_dragging_l = false;
        setCursor(QCursor(Qt::ArrowCursor));

    } else if (_currentTool) _currentTool->mouseRelease(event);
}

QVector3D NodeGraphWidget::windowToGraph(const QPointF &point) const
{
    return QVector3D((point - _offset) / _scale);
}

QPointF NodeGraphWidget::graphToWindow(const QVector3D &pos) const
{
    return (pos * _scale).toPointF() + _offset;
}



