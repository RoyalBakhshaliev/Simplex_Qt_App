QT += core gui widgets charts

CONFIG += c++17

SOURCES += \
    drob.cpp \
    main.cpp \
    mainwindow.cpp \
    simplexmetod.cpp

HEADERS += \
    drob.h \
    mainwindow.h \
    simplexmetod.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
