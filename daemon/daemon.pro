TARGET = proximity-speaker-daemon
target.path = /usr/bin

QT += dbus sensors
CONFIG += link_pkgconfig
PKGCONFIG += sailfishapp
INCLUDEPATH += /usr/include/sailfishapp

service.files = org.coderus.proximityspeaker.service
service.path = /usr/share/dbus-1/services

INSTALLS += target service

SOURCES += \
    main.cpp \
    proximitysocket.cpp

HEADERS += \
    proximitysocket.h
