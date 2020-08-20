#include "cell.h"
#include "CellExtendedEvent.h"


Cell::Cell(QWidget *parent/* = 0*/)
    : QLabel(parent)
{
    QArrayData arr;
    setAutoFillBackground(true);
    //pcmd = new QPushButton(this);
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
    setState(empty);
    setReadOnly(false);
    setTempBlock(false);
    setRow(-1);
    setColumn(-1);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

Cell::Cell(int row, int column, QWidget *parent/* = 0*/)
    : QLabel(parent)
{
    setRow(row);
    setColumn(column);
    setAutoFillBackground(true);
    //pcmd = new QPushButton(this);
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
    setState(empty);
    setReadOnly(false);
    setTempBlock(false);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

//Cell::Cell(QString text, QWidget *parent/* = 0*/)
//    : QLabel(parent)
//{   setAutoFillBackground(true);
//    //pcmd = new QPushButton(this);
//    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    policy.setHeightForWidth(true);
//    setSizePolicy(policy);
//    setText(text);
//    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
//}

//Cell::~Cell() {

//};

void Cell::mousePressEvent(QMouseEvent *event) {
    if (isReadOnly() || isTempBlock())
        return;
    if (event->button() == Qt::LeftButton) {
        if (getState() !=  colored)
            setState(colored);
        else
            setState(empty);
    }
    else if(event->button() == Qt::RightButton) {
        if (getState() != cross)
            setState(cross);
        else
            setState(empty);
    }
    setTempBlock(true);
    emit lastStateSignal(getState());
}

void Cell::mouseReleaseEvent(QMouseEvent *event) {
    setTempBlock(false);
}

//void Cell::paintEvent(QPaintEvent *e) {
//    QStylePainter p(this);
//    QStyleOptionButton option;
//    //initStyleOption(&option);
//    p.drawControl(QStyle::CE_PushButton, option);
//}

//QSize Cell::sizeHint() const{
//    QSize newSize;
//    int newWidth = baseSize().width() + sizeIncrement().width();
//    int newHeight = baseSize().height() + sizeIncrement().height();
//    if (newWidth > newHeight) {
//        newSize.setWidth(newWidth);
//        newSize.setHeight(newWidth);
//    }
//    else {
//        newSize.setWidth(newHeight);
//        newSize.setHeight(newHeight);
//    }
//    return newSize;
//}
int Cell::heightForWidth(int width) const {
    //QApplication::postEvent(static_cast<QWidget*>(this), new QEvent(QEvent::UpdateRequest));
    return width;

}

bool Cell::hasHeightForWidth() const {
    return true;
}


void Cell::enterEvent(QEvent *event) {
    emit mouseEnterSignal();
}

void Cell::leaveEvent(QEvent *event) {
    emit mouseLeaveSignal();
}

void Cell::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (getState() != colored) {
        painter.setPen(QPen(Qt::white));
        painter.setBrush(QBrush(Qt::white));
        painter.drawRect(0, 0, width(), height());
    }
    else {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::black));
        painter.drawRect(0, 0, width(), height());
    }
    if (getState() == cross) {
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        painter.drawLine(0, 0, width(), height());
        painter.drawLine(0, height(), width(), 0);
    }
    if (text() != "") {
        painter.setPen(QPen(Qt::black));
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, text());
    }
}

void Cell::setRow(int row) {
    cellRow = row;
}
void Cell::setColumn(int column) {
    cellColumn = column;
}

int Cell::row() {
    return cellRow;
}

int Cell::column() {
    return cellColumn;
}

int Cell::value() {
    if (getState() != colored)
        return 0;
    return 1;
}


void Cell::customEvent(QEvent *event) {
    if (isReadOnly() || isTempBlock())
        return;
    if (event->type() == CellExtendedEvent::getType()) {
        CellExtendedEvent* ev = dynamic_cast<CellExtendedEvent*>(event);
        switch (ev->getState()) {
            case empty:
                setState(empty);
                break;
            case colored:
                setState(colored);
                break;
            case cross:
                setState(cross);
                break;
        }
    }
}

Cell::state Cell::getState() {
    return cellState;
}

void Cell::setReadOnly(bool value) {
    readOnly = value;
}

bool Cell::isReadOnly() {
    return  readOnly;
}

void Cell::setState(state valueToSet) {
    cellState = valueToSet;
    emit valueChangedSignal();
    update();
}


void Cell::setTempBlock(bool value) {
    tempBlock = value;
}

bool Cell::isTempBlock() {
    return tempBlock;
}
