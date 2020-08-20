#include "CellExtendedEvent.h"

CellExtendedEvent::CellExtendedEvent(int state/*= 0*/)
    : QEvent((Type)(QEvent::User + 100))
{
    stateToExtend = state;

};

int CellExtendedEvent::getState() {
    return stateToExtend;
}


QEvent::Type CellExtendedEvent::getType()  {
    return type;
}

QEvent::Type CellExtendedEvent::type {
    (Type)(QEvent::User + 100)
};
