#ifndef GRID_H
#define GRID_H
#include <QtWidgets>

class Grid: public QGridLayout {
    Q_OBJECT
public:
    Grid(QWidget* parent = 0);
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
private:
    //void paintEvent(QPaintEvent *event);
};

#endif // GRID_H
