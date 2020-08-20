#include "grid.h"
Grid::Grid(QWidget* parent/*=0*/) :
    QGridLayout(parent) { };

bool Grid::hasHeightForWidth() const {
    return true;
}

int Grid::heightForWidth(int width) const {
    return width / columnCount() * rowCount();
}


//void Grid::paintEvent(QPaintEvent *event) {
//    QPainter painter((QPaintDevice*)this);
//    painter.setPen(QPen(Qt::black, 10, Qt::SolidLine));
//    for (int i = 0; i < 30; ++i) {
//        for (int j = 0; j < 30; ++j)
//        painter.drawLine(i * 5, this->geometry().left(), i * 5, this->geometry().right());
//    }
//}
