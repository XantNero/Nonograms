#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#include <QtWidgets>

class SettingsWindow: public QWidget {
    Q_OBJECT
public:
    SettingsWindow(QWidget* parent);
public slots:
    void slotBack();
signals:
    void signalAction(int);
};



#endif // SETTINGSWINDOW_H
