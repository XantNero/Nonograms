#include "PlayWindow.h"
#include "backOfGrid.h"
#include "cell.h"
#include "grid.h"
#include "Nanogram.h"
#include "program.h"
#include "NumberCell.h"
#include "AutomaticCrossingChecker.h"


PlayWindow::PlayWindow(QString fileName, QWidget* parent) :
    QScrollArea(parent)
{
    Nanogram nan(fileName.toStdString());
    rowsCount = nan.getHeight();
    columnsCount = nan.getWidth();
    int* rows_len = new int[rowsCount];
    nan.getRowsLens(rows_len);
    int** rows = new int*[rowsCount];
    for (int i = 0; i < rowsCount; ++i)
        rows[i] = new int[rows_len[i]];
    nan.getRows(rows);
    QVector<int> rowCross;
    for (int i = 0; i < rowsCount; ++i)
        rowCross.push_back(rows_len[i]);
    int* columns_len = new int[columnsCount];
    nan.getColumnsLens(columns_len);
    QVector<int> columnCross;
    for (int i = 0; i < columnsCount; ++i)
        columnCross.push_back(columns_len[i]);
    int** columns = new int*[columnsCount];
    for (int i = 0; i < columnsCount; ++i)
        columns[i] = new int[columns_len[i]];
    nan.getColumns(columns);
    goal = nan.getGoal();
    result.fill('0', rowsCount * columnsCount);
    maxRowLen = 0;
    for (int i = 0; i < rowsCount; ++i) {
        if (rows_len[i] > maxRowLen)
            maxRowLen = rows_len[i];
    }
    maxColumnLen = 0;
    for (int i = 0; i < columnsCount; ++i) {
        if (columns_len[i] > maxColumnLen)
            maxColumnLen = columns_len[i];
    }
    AutomaticCrossingChecker* crossChecker = new AutomaticCrossingChecker(rowCross, columnCross, this);
    connect(crossChecker, SIGNAL(setRowCrosses(int)), SLOT(setRowCrossSlot(int)));
    connect(crossChecker, SIGNAL(setColumnCrosses(int)), SLOT(setColumnCrossSlot(int)));
    backOfGrid *widget = new backOfGrid(this);
    pgrdLayout = new Grid;
    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    QHBoxLayout  *phbxLayout = new QHBoxLayout;
    QPushButton *cmdCheck = new QPushButton("Check answer");
    connect(cmdCheck, SIGNAL(clicked()), SLOT(checkAnswerSlot()));
    QPushButton *cmdClear = new QPushButton("Clear");
    connect(cmdClear, SIGNAL(clicked()), SLOT(clearSlot()));
    phbxLayout->addWidget(cmdClear);
    phbxLayout->addWidget(cmdCheck);
    pgrdLayout->setSpacing(2);
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < columnsCount; ++j) {
            Cell *gridCell = new Cell(i, j);
        gridCell->setMaximumSize(100, 100);
        gridCell->setMinimumSize(10, 10);

        gridCell->resize(15, 15);
        connect(gridCell, SIGNAL(mouseEnterSignal()), widget, SLOT(mouseEnterSlot()));
        connect(gridCell, SIGNAL(mouseLeaveSignal()), widget, SLOT(mouseLeaveSlot()));
        connect(gridCell, SIGNAL(valueChangedSignal()), SLOT(changeResultSlot()));
        connect(gridCell, SIGNAL(lastStateSignal(int)), widget, SLOT(stateSlot(int)));
        //gridCell->setFixedSize(gridCell->size());
        pgrdLayout->addWidget(gridCell, maxColumnLen + i, maxRowLen + j, 1, 1);
        }
        pgrdLayout->setRowStretch(maxColumnLen + i, 0);
    }
    for (int i = 0; i < columnsCount; ++i)
        pgrdLayout->setColumnStretch(maxRowLen + i, 0);
    for (int i = 0; i < columnsCount; ++i) {
        int now_column = columns_len[i] - 1;
        for (int j = maxColumnLen - 1; j >= 0; --j) {
            Cell *gridCell;
            if (now_column >= 0) {
                gridCell = new NumberCell(columns[i][now_column], -1, i);
                connect(gridCell, SIGNAL(lastStateSignal(int)), widget, SLOT(stateSlot(int)));
                connect(gridCell, SIGNAL(valueChangedSignal()), crossChecker, SLOT(crossSlot()));
                --now_column;
            }
            else {
                gridCell = new Cell;
                gridCell->setReadOnly(true);
            }
            gridCell->setMaximumSize(100, 100);
            gridCell->setMinimumSize(10, 10);
            gridCell->resize(20, 20);
            pgrdLayout->addWidget(gridCell, j, maxRowLen + i, 1, 1);
        }
    }
    for (int i = 0; i < rowsCount; ++i) {
        int now_row = rows_len[i] - 1;
        for (int j = maxRowLen - 1; j >= 0; --j) {
            Cell *gridCell;
            if (now_row >= 0) {
                gridCell = new NumberCell(rows[i][now_row], i);
                connect(gridCell, SIGNAL(valueChangedSignal()), crossChecker, SLOT(crossSlot()));
                --now_row;
            }
            else {
                gridCell = new Cell;
                gridCell->setReadOnly(true);
            }
            gridCell->setMaximumSize(100, 100);
            gridCell->setMinimumSize(10, 10);
            gridCell->resize(20, 20);
            pgrdLayout->addWidget(gridCell, i + maxColumnLen, j, 1, 1);
        }
    }
//    for (int i = 0; i < max_column_len; ++i) {
//        for (int j = 0; j < max_row_len; ++j) {
//             Cell *gridCell = new Cell;
//             gridCell->setMaximumSize(100, 100);
//             gridCell->setMinimumSize(10, 10);
//             gridCell->resize(15, 15);
//             pgrdLayout->addWidget(gridCell, i, j, 1, 1);
//        }
//    }
    for (int i = 0; i < maxRowLen; ++i)
        pgrdLayout->setColumnStretch(i, 0);
    for (int i = 0; i < maxColumnLen; ++i)
        pgrdLayout->setRowStretch(i, 0);
    pvbxLayout->addLayout(pgrdLayout);
    pvbxLayout->addLayout(phbxLayout);
    widget->setLayout(pvbxLayout);
    setWidget(widget);
    setWidgetResizable(true);
    QMargins margins = pgrdLayout->contentsMargins();
    resize(margins.left() + margins.right() + (maxRowLen + columnsCount) * 20 + (maxRowLen + columnsCount - 1)* pgrdLayout->spacing(),
           margins.top() + margins.bottom() + (maxColumnLen + rowsCount) * 20 + (maxColumnLen + rowsCount - 1) * pgrdLayout->spacing());
    hide();
    for (int i = 0; i < rowsCount; ++i) {
        delete[] rows[i];
    }
    delete[] rows;
    delete[] rows_len;
    for (int i = 0; i < columnsCount; ++i) {
        delete[] columns[i];
    }
    delete[] columns;
    delete[] columns_len;
}

PlayWindow::~PlayWindow() { };

void PlayWindow::changeResultSlot() {
    Cell* cell = (Cell*)sender();
    result[cell->row() * columnsCount + cell->column()] = cell->value() + '0';
}

void PlayWindow::checkAnswerSlot() {
    if (result == goal) {
        QMessageBox *pmbx =
            new QMessageBox(QMessageBox::Information,
                            "Message", "Well done!",
                            QMessageBox::Ok);
        int n = pmbx->exec();
        delete pmbx;
        if (n == QMessageBox::Ok || n == QMessageBox::No) {
            emit signalAction(Program::MainAction);
            delete this;
        }
    }
    else {
        QMessageBox *pmbx =
            new QMessageBox(QMessageBox::Warning,
                            "Message", "Wrong result!",
                            QMessageBox::Ok);
        int n = pmbx->exec();
        delete pmbx;

    }

}


void PlayWindow::clearSlot() {
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < columnsCount; ++j) {
            Cell* gridCell = (Cell*)pgrdLayout->itemAtPosition(i + maxColumnLen, j + maxRowLen)->widget();
            if (gridCell->getState() != Cell::empty)
                gridCell->setState(Cell::empty);
        }
    }
    for (int i = 0; i < rowsCount; ++i) {
        for (int j = 0; j < maxRowLen; ++j) {
            Cell* gridCell = (Cell*)pgrdLayout->itemAtPosition(i + maxColumnLen, j)->widget();
            if (gridCell->getState() != Cell::empty)
                gridCell->setState(Cell::empty);
        }
    }
    for (int i = 0; i < maxRowLen; ++i) {
        for (int j = 0; j < columnsCount; ++j) {
            Cell* gridCell = (Cell*)pgrdLayout->itemAtPosition(i, j + maxRowLen)->widget();
            if (gridCell->getState() != Cell::empty)
                gridCell->setState(Cell::empty);
        }
    }
}


void PlayWindow::setRowCrossSlot(int row) {
    for (int i = 0; i < columnsCount; ++i) {
        Cell* gridCell = (Cell*)pgrdLayout->itemAtPosition(row + maxColumnLen, i + maxRowLen)->widget();
        if (gridCell->getState() == Cell::empty)
            gridCell->setState(Cell::cross);
    }
}

void PlayWindow::setColumnCrossSlot(int column) {
    for (int i = 0; i < rowsCount; ++i) {
        Cell* gridCell = (Cell*)pgrdLayout->itemAtPosition(i + maxColumnLen, column + maxRowLen)->widget();
        if (gridCell->getState() == Cell::empty)
            gridCell->setState(Cell::cross);
    }
}
