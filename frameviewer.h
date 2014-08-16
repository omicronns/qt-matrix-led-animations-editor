#ifndef FRAMEVIEWER_H
#define FRAMEVIEWER_H

#include <QTableWidget>

class FrameViewer : public QTableWidget
{
    Q_OBJECT
public:
    explicit FrameViewer(QWidget *parent = 0);
    QModelIndexList selectedIndexesList(void);

};

#endif // FRAMEVIEWER_H
