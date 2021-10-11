#ifndef NODEGRAPHWIDGET_H
#define NODEGRAPHWIDGET_H

#include <QWidget>
#include <nodegraph.h>


class NodeGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NodeGraphWidget(QWidget * parent = nullptr);

    NodeGraph * graph() const;
    void setGraph(NodeGraph * graph);

    QVector3D windowToGraph(const QPointF & point) const;
    QPointF graphToWindow(const QVector3D & pos) const;

protected:

    void paintEvent(QPaintEvent * event) override;
    void wheelEvent(QWheelEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;

    void drawEdge(QPainter & painter, Node * from, Node * to, float node_radius);
    Node * getHowerNode(QVector3D point);

private:
    NodeGraph * _graph = nullptr;

    float _scale = 1.0;
    QPointF _offset;

    bool _mouse_dragging = false;
    bool _mouse_dragging_l = false;
    QPoint _start_drag;
    QPoint _start_offset;

};

#endif // NODEGRAPHWIDGET_H
