#include "frameviewer.h"

FrameViewer::FrameViewer(QWidget *parent) :
    QTableWidget(parent)
{
}

QModelIndexList FrameViewer::selectedIndexesList()
{
    return selectedIndexes();
}
