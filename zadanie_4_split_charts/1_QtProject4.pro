QT += widgets charts

CONFIG += c++17

SOURCES += \
    kalkulyator.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    kalkulyator.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
