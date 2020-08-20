#ifndef PROGRAM_H
#define PROGRAM_H
#include <QtWidgets>
#include "MainWindow.h"

class Program : public QMainWindow
{
    Q_OBJECT
private:
    MainWindow *pmainWindow;
    QWidget *psettingsWindow;
//    QGraphicsScene *pplayWindowScene;
   // QGraphicsView *pplayWindowView;
    QScrollArea *pplayWindow;
    QScrollArea *pchooseWindow;
    QString nonogramName;

public:
    Program(QWidget *parent = nullptr);
    enum action{SettingsAction, MainAction, PlayAction, ChooseAction};
    void setNonogramName(QString);
private:
    void playAction();
    void settingsAction();
    void mainAction();
    void chooseAction();
private slots:
    void slotAction(int);
    void slotFileName(QString);
};
#endif // PROGRAM_H
