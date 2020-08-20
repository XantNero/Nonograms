#ifndef AUTOMATICCROSSINGCHECKER_H
#define AUTOMATICCROSSINGCHECKER_H
#include <QtWidgets>

class AutomaticCrossingChecker : public QObject{
    Q_OBJECT
private:
    QVector<int> rows;
    QVector<int> columns;
public:
    AutomaticCrossingChecker(const QVector<int> &rows, const QVector<int> &columns,QWidget *parent = 0);
    void changeEmptyRowCount(int row, int num);
    void changeEmptyColumnCount(int column, int num);
    int getEmptyRowCount(int row);
    int getEmptyColumnCount(int column);
    void setRows(const QVector<int> &rows);
    void setColumns(const QVector<int> &columns);
public slots:
    void crossSlot();
signals:
    void setRowCrosses(int);
    void setColumnCrosses(int);
};

#endif // AUTOMATICCROSSINGCHECKER_H
