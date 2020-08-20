#include "SettingsWindow.h"
#include "program.h"


SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
{
    QLabel *lbl = new QLabel("Settings are in progress");
    QPushButton *pcmdBack = new QPushButton("&Back");
    connect(pcmdBack, SIGNAL(clicked()), SLOT(slotBack()));
    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(lbl);
    pvbxLayout->addWidget(pcmdBack);
    setLayout(pvbxLayout);
    hide();
}

void SettingsWindow::slotBack() {
    emit signalAction(Program::MainAction);
}

