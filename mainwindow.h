#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>

class MainWindow: public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent);
public slots:
    void slotPlay();
    void slotSettings();
signals:
    void signalAction(int);
};


#endif // MAINWINDOW_H
