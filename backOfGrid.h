#ifndef BACKOFGRID_H
#define BACKOFGRID_H
#include <QtWidgets>

class backOfGrid: public QWidget {
    Q_OBJECT
    QPen pen;
    QBrush brush;
    QRect paintRect;
    int valueForChange;
    QWidget* lastClickedWidget;
    bool selectedCell;
public:
    backOfGrid(QWidget *parent = 0);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setPaintRect(const QRect &rect);
protected:
    void paintEvent(QPaintEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
public slots:
    void mouseEnterSlot();
    void mouseLeaveSlot();
    void stateSlot(int);
};

#endif // BACKOFGRID_H
