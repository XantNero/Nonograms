#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include <QtWidgets>
#include "Grid.h"

class PlayWindow: public QScrollArea {
    Q_OBJECT
private:
    QString goal;
    QString result;
    int rowsCount;
    int columnsCount;
    int maxRowLen;
    int maxColumnLen;
    Grid *pgrdLayout;
public:
    PlayWindow(QString fileName, QWidget* parent);
    ~PlayWindow();
private slots:
    void changeResultSlot();
    void checkAnswerSlot();
    void clearSlot();
    void setRowCrossSlot(int);
    void setColumnCrossSlot(int);
signals:
    void signalAction(int);
};

#endif // PLAYWINDOW_H
