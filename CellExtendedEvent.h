#ifndef CELLEXTENDEDEVENT_H
#define CELLEXTENDEDEVENT_H
#include <QtWidgets>

class CellExtendedEvent: public QEvent {
private:
    int stateToExtend;
    static Type type;
public:
    CellExtendedEvent(int state = 0);
    int getState();
    static Type getType();
};

#endif // CELLEXTENDEDEVENT_H
