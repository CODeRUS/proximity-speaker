TARGET = proximity-speaker

QT += dbus
CONFIG += sailfishapp

SOURCES += src/proximity-speaker.cpp \
    src/proximityclient.cpp

OTHER_FILES += qml/proximity-speaker.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    proximity-speaker.desktop

HEADERS += \
    src/proximityclient.h
