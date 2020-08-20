#ifndef NUMBERCELL_H
#define NUMBERCELL_H
#include "cell.h"

class NumberCell: public Cell {
    Q_OBJECT
private:
public:
    NumberCell(QWidget* parent = 0);
    NumberCell(const int number, const int row = -1, const int column = -1, QWidget* parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void customEvent(QEvent *event);
};

#endif // NUMBERCELL_H
