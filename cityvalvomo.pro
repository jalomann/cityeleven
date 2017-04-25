TEMPLATE      = app
CONFIG       += console
HEADERS       = annotation.h \
                cityblock.h \
                cityscape.h \
                cityvalve.h \
                citymotor.h \
                cityline1.h \
                citypool.h \
                cityswitch.h \
                cityview.h \
                cell.h \
                spreadsheet.h \
    countryline1.h \
    countryline2.h \
    socketcomm.h \
    motordialog.h \
    citypump.h

SOURCES       = annotation.cpp \
                cityblock.cpp \
                cityscape.cpp \
                cityvalve.cpp \
                citymotor.cpp \
                cityline1.cpp \
                citypool.cpp \
                cityswitch.cpp \
                cityview.cpp \
                main.cpp \
    spreadsheet.cpp \
    cell.cpp \
    countryline1.cpp \
    countryline2.cpp \
    socketcomm.cpp \
    motordialog.cpp \
    citypump.cpp

RESOURCES += cityvalvomo.qrc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network
