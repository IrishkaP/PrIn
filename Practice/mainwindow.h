#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <nodegraphwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_select_action_triggered();

    void on_add_action_triggered();

    void on_remove_action_triggered();

private:
    Ui::MainWindow *ui;
    NodeGraphWidget * _graph_widget = nullptr;
    std::unique_ptr<NodeGraph> _graph;
};
#endif // MAINWINDOW_H
