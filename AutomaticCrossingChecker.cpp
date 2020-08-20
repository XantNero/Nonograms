#include "AutomaticCrossingChecker.h"
#include "NumberCell.h"
AutomaticCrossingChecker::AutomaticCrossingChecker(const QVector<int> &row, const QVector<int> &column, QWidget* parent)
    : QObject(parent)
{
    setRows(row);
    setColumns(column);
};


void AutomaticCrossingChecker::crossSlot() {
    NumberCell *gridCell = (NumberCell*)sender();
    int num = 0;
    if (gridCell->getState() == Cell::empty)
        num = 1;
    else
        num = -1;
    if (gridCell->row() != -1) {
        changeEmptyRowCount(gridCell->row(), num);
        if (getEmptyRowCount(gridCell->row()) == 0)
            emit setRowCrosses(gridCell->row());
    }
    else if (gridCell->column() != -1) {
        changeEmptyColumnCount(gridCell->column(), num);
        if (getEmptyColumnCount(gridCell->column()) == 0)
            emit setColumnCrosses(gridCell->column());
    }
}

void AutomaticCrossingChecker::changeEmptyRowCount(int row, int num) {
    if (row < rows.size())
        rows[row] += num;
}

void AutomaticCrossingChecker::changeEmptyColumnCount(int column, int num) {
    if (column < columns.size())
        columns[column] += num;
}


void AutomaticCrossingChecker::setRows(const QVector<int> &rows) {
    this->rows = rows;
}

void AutomaticCrossingChecker::setColumns(const QVector<int> &columns) {
    this->columns = columns;
}


int AutomaticCrossingChecker::getEmptyRowCount(int row) {
    if (row < rows.size())
        return rows[row];
    return -1;
}

int AutomaticCrossingChecker::getEmptyColumnCount(int column) {
    if (column < columns.size())
        return columns[column];
    return -1;
}
