#include "backOfGrid.h"
#include "cell.h"
#include "CellExtendedEvent.h"

backOfGrid::backOfGrid(QWidget* parent /*=0*/) :
    QWidget(parent)
{
    setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    setBrush(QBrush(Qt::gray));
    setPaintRect(QRect(0, 0, width(), height()));
    selectedCell = false;
    valueForChange = 0;
    lastClickedWidget = 0;
    //setUpdatesEnabled(true);
};
void backOfGrid::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::gray));
    painter.setBrush(QBrush(Qt::gray));
    painter.drawRect(QRect(0, 0, width(), height()));
    painter.setPen(pen);
    painter.setBrush(brush);
    if (selectedCell) {
        painter.drawRect(QRect(paintRect.x(), 0, paintRect.width(), height()));
        painter.drawRect(QRect(0, paintRect.y(), width(), paintRect.height()));
    }
}


void backOfGrid::mouseEnterSlot() {
    Cell *cell = dynamic_cast<Cell*>(sender());
    QPainter painter(this);
    setPen(QPen(Qt::red, 4, Qt::SolidLine));
    setBrush(QBrush(Qt::red));
    selectedCell = true;
    setPaintRect(cell->geometry());
    update();

};

void backOfGrid::mouseLeaveSlot() {
    Cell *cell = dynamic_cast<Cell*>(sender());
    setPen(QPen(Qt::gray, 4, Qt::SolidLine));
    setBrush(QBrush(Qt::gray));
    setPaintRect(cell->geometry());
    update();
    selectedCell = false;
};


void backOfGrid::setPen(const QPen &pen) {
    this->pen = pen;
}

void backOfGrid::setBrush(const QBrush &brush) {
    this->brush = brush;
}


void backOfGrid::setPaintRect(const QRect &rect) {
    this->paintRect = rect;
}

void backOfGrid::mouseMoveEvent(QMouseEvent *ev) {
    QWidget* child = childAt(ev->x(), ev->y());
    if (child) {
        if (child != lastClickedWidget) {
            QMouseEvent* mouseEvent = new QMouseEvent(QEvent::MouseButtonRelease, lastClickedWidget->pos(), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            QApplication::postEvent(lastClickedWidget, mouseEvent);
            mouseEvent = new QMouseEvent(QEvent::Leave, lastClickedWidget->pos(), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            QApplication::postEvent(lastClickedWidget, mouseEvent);
            lastClickedWidget = child;
        }
        QMouseEvent* mouseEvent = new QMouseEvent(QEvent::Enter, ev->localPos(), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
        QApplication::postEvent(child, mouseEvent);
        CellExtendedEvent* event = new CellExtendedEvent(valueForChange);
         QApplication::postEvent(child, event);
    }

}

void backOfGrid::stateSlot(int state) {
    valueForChange = state;
    lastClickedWidget = (QWidget*)sender();
}
