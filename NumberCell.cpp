#include "NumberCell.h"

NumberCell::NumberCell(QWidget* parent /*= 0*/)
    : Cell(parent) { };

NumberCell::NumberCell(const int number, const int row, const int column, QWidget* parent /*= 0*/)
    : Cell(parent)
{
    setText(QString::number(number));
    setRow(row);
    setColumn(column);
}

void NumberCell::mousePressEvent(QMouseEvent *event) {
    if (isReadOnly())
        return;
    if(event->button() == Qt::RightButton || event->button() == Qt::LeftButton) {
        if (getState() != cross)
            setState(cross);
        else
            setState(empty);
    }
    setTempBlock(true);
    emit lastStateSignal(getState());
}

void NumberCell::customEvent(QEvent *event) { };
