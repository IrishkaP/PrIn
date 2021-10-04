#include "mainwindow.h"
#include "ui_mainwindow.h"

std::unique_ptr<NodeGraph> createTestGraph()
{
    std::unique_ptr<NodeGraph> graph = std::make_unique<NodeGraph>();
    auto n0 = new Node(QVector3D(250,150,0));
    auto n1 = new Node(QVector3D(50,50,0));
    auto n2 = new Node(QVector3D(50,150,0));
    auto n3 = new Node(QVector3D(120,200,0));

    n0->addNeighbour(n2);
    n0->addNeighbour(n3);
    n1->addNeighbour(n0);
    n1->addNeighbour(n2);
    n1->addNeighbour(n3);
    n2->addNeighbour(n1);
    n3->addNeighbour(n2);

    graph->add(n0);
    graph->add(n1);
    graph->add(n2);
    graph->add(n3);

    return graph;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _graph_widget = new NodeGraphWidget(this);

    setCentralWidget(_graph_widget);

    _graph = createTestGraph();
    _graph_widget->setGraph(_graph.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

