#include "tofile.h"
#include <QMouseEvent>
#include <fstream>
#include <iostream>
#include <set>


ToFile::ToFile(NodeGraph * graph, NodeGraphWidget *graph_widget):
    GraphTool(graph,graph_widget)
{}


bool ToFile::mousePress(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
       std::set <Node *> nodes;
       nodes = graph()->nodes();
       Node * j;

       std::ofstream out;
       out.open("E:\\pech\\PrIn\\Practice\\output.text");
       int k;
       if (out.is_open())
       {
           k = graph()->countNodes();
           out << k << std::endl;
           for (auto i = nodes.begin(); i != nodes.end(); i++)
           {
               j = *i;
               out << j->position()[0] << " " << j->position()[1] <<  " " << j->position()[2] << std::endl;
           }
       }
    }
       return false;
}
