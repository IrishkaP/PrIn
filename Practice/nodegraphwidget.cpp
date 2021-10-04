#include "nodegraphwidget.h"
#include <QPainter>
#include <QWheelEvent>

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
    QPointF end_3 = (to->position() - direction  * node_radius * 2).toPointF();
    painter.setPen(QPen(QColor(Qt::green), 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    painter.drawLine(end,end_3);

    painter.restore();
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

    const float node_radius = 10;

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
}

void NodeGraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (_mouse_dragging)
    {
        _offset = _start_offset + (event->pos() - _start_drag);
        repaint();
    }
}

void NodeGraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (_mouse_dragging && event->button() == Qt::RightButton)
    {
        _mouse_dragging = false;
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

QVector3D NodeGraphWidget::windowToGraph(const QPointF &point) const
{
    return QVector3D((point - _offset) / _scale);
}

QPointF NodeGraphWidget::graphToWindow(const QVector3D &pos) const
{
    return (pos * _scale).toPointF() + _offset;
}



