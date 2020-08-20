#include "ChooseWindow.h"
#include "program.h"

ChooseWindow::ChooseWindow(QWidget* parent /*= 0*/)
    : QScrollArea(parent)
{
    QDir dir(qApp->applicationDirPath());
    QWidget* widget = new QWidget(this);
    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    QStringList filters;
    filters << "*.non";
    QString fileName;
    foreach (fileName, dir.entryList(filters, QDir::Files, QDir::Name)) {
        QPushButton *cmd = new QPushButton(fileName);
        connect(cmd, SIGNAL(clicked()), SLOT(playSlot()));
        pvbxLayout->addWidget(cmd);
    }
    widget->setLayout(pvbxLayout);
    setWidget(widget);
    setWidgetResizable(true);
    hide();
};

void ChooseWindow::playSlot() {
    QPushButton *cmd = (QPushButton*)sender();
    emit signalFileName(cmd->text());
    emit signalAction(Program::PlayAction);
}
