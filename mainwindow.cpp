#include "MainWindow.h"
#include "program.h"


MainWindow::MainWindow(QWidget* parent) :
    QWidget(parent)
{
   QPushButton *pcmdPlay = new QPushButton("&Play");
   QPushButton *pcmdSettings = new QPushButton("&Settings");
   QPushButton *pcmdExit = new QPushButton("&Exit");
   connect(pcmdExit, SIGNAL(clicked()), qApp, SLOT(quit()));
   connect(pcmdPlay, SIGNAL(clicked()), SLOT(slotPlay()));
   connect(pcmdSettings, SIGNAL(clicked()), SLOT(slotSettings()));
   QVBoxLayout *pvbxLayout = new QVBoxLayout(this);
   pvbxLayout->addWidget(pcmdPlay);
   pvbxLayout->addWidget(pcmdSettings);
   pvbxLayout->addWidget(pcmdExit);
   setLayout(pvbxLayout);
}

void MainWindow::slotPlay() {
    emit signalAction(Program::ChooseAction);
}

void MainWindow::slotSettings() {
    emit signalAction(Program::SettingsAction);
}
