QT *= core qml quick

CONFIG += thread exceptions rtti stl

include(qt-breakpad/qt-breakpad.pri)

RESOURCES += \
    $$PWD/react-qml-breakpad.qrc

HEADERS += \
    $$PWD/rqcrashhandler.h \
    $$PWD/QBreakpadHttpUploader.h

SOURCES += \
    $$PWD/rqcrashhandler.cpp \
    $$PWD/QBreakpadHttpUploader.cpp
