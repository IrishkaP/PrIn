#ifndef TOFILE_H
#define TOFILE_H
#include "nodegraphwidget.h"
#include "selecttool.h"
#include "nodegraph.h"


void saveTo(const QString & name, const NodeGraph * graph);

void load (const QString & name,NodeGraph * graph, NodeGraphWidget *graph_widget);


#endif // TOFILE_H
