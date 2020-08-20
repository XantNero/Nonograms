#include "program.h"
#include "cell.h"
#include "grid.h"
#include "backOfGrid.h"
#include "MainWindow.h"
#include "SettingsWindow.h"
#include "PlayWindow.h"
#include "ChooseWindow.h"
Program::Program(QWidget *parent)
    : QMainWindow(parent), pplayWindow(0)
{
    pmainWindow = new MainWindow(this);
    connect(pmainWindow, SIGNAL(signalAction(int)), SLOT(slotAction(int)));
    psettingsWindow = new SettingsWindow(this);
    connect(psettingsWindow, SIGNAL(signalAction(int)), SLOT(slotAction(int)));
//    pplayWindow = new PlayWindow(this);
//    connect(pplayWindow, SIGNAL(signalAction(int)), SLOT(slotAction(int)));
    pchooseWindow = new ChooseWindow(this);
    connect(pchooseWindow, SIGNAL(signalAction(int)), SLOT(slotAction(int)));
    connect(pchooseWindow, SIGNAL(signalFileName(QString)), SLOT(slotFileName(QString)));
    setCentralWidget(pmainWindow);
}

void Program::settingsAction() {
    centralWidget()->hide();
    takeCentralWidget();
    setCentralWidget(psettingsWindow);
    resize(psettingsWindow->size());
    psettingsWindow->show();
}

void Program::mainAction() {
    centralWidget()->hide();
    takeCentralWidget();
    setCentralWidget(pmainWindow);
    resize(pmainWindow->size());
    pmainWindow->show();
}

void Program::chooseAction() {
    centralWidget()->hide();
    takeCentralWidget();
    setCentralWidget(pchooseWindow);
    resize(pchooseWindow->size());
    pchooseWindow->show();
}

void Program::playAction() {
   pplayWindow = new PlayWindow(nonogramName, this);
   connect(pplayWindow, SIGNAL(signalAction(int)), SLOT(slotAction(int)));
   centralWidget()->hide();
   takeCentralWidget();
   setCentralWidget(pplayWindow);
   resize(pplayWindow->size());
   pplayWindow->show();
}

void Program::slotAction(int action) {
    switch (action) {
        case PlayAction:
            playAction();
            break;
        case SettingsAction:
            settingsAction();
            break;
        case MainAction:
            mainAction();
            break;
        case ChooseAction:
            chooseAction();
            break;
         //make case error
    }
}

void Program::setNonogramName(QString name) {
    nonogramName = name;
}

void Program::slotFileName(QString name) {
    setNonogramName(name);
}
