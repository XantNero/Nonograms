#ifndef CELL_H
#define CELL_H
#include <QtWidgets>

class Cell : public QLabel {
    Q_OBJECT
    //QPushButton *pcmd;

    int cellColumn;
    int cellRow;
    bool readOnly;
    bool tempBlock;
public:
    enum state{empty, cross, colored};
    Cell(QWidget *parent = 0);
    Cell(int row, int column, QWidget* parent = 0);
    void setRow(int row);
    void setColumn(int column);
    int row();
    int column();
    int value();
    state getState();
    void setReadOnly(bool);
    bool isReadOnly();
     void setState(state);
    //Cell(QString text, QWidget *parent = 0);
    //QSize sizeHint() const;

    //~Cell();
private:
    enum state cellState;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void customEvent(QEvent* event) override;
    int heightForWidth(int width) const override;
    bool hasHeightForWidth() const override;
    void setTempBlock(bool);
    bool isTempBlock();
    //bool event(QEvent* event) override;
signals:
    void mouseEnterSignal();
    void mouseLeaveSignal();
    void valueChangedSignal();
    void lastStateSignal(int);
};

#endif // CELL_H
