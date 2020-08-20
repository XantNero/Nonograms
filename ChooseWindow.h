#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H
#include <QtWidgets>

class ChooseWindow: public QScrollArea {
    Q_OBJECT
public:
    ChooseWindow(QWidget* parent = 0);
public slots:
    void playSlot();
signals:
    void signalAction(int);
    void signalFileName(QString);
};


#endif // CHOOSEWINDOW_H
