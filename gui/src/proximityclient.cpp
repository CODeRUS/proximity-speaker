#include "proximityclient.h"

#include <QDebug>

#define OBJECT_NAME "/"
#define SERVICE_NAME "org.coderus.proximityspeaker"
#define INTERFACE_NAME "org.coderus.proximityspeaker"

ProximityClient::ProximityClient(QObject *parent) :
    _sensorActive(false),
    _callActive(false),
    _proxClose(false),
    QObject(parent)
{
    qDebug() << "client constructor";

    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_NAME, INTERFACE_NAME,
                                          "callActive", this, SIGNAL(onCallActive(bool)));
    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_NAME, INTERFACE_NAME,
                                          "proxClose", this, SIGNAL(onProxClose(bool)));
    QDBusConnection::sessionBus().connect(SERVICE_NAME, OBJECT_NAME, INTERFACE_NAME,
                                          "sensorEnabled", this, SIGNAL(onSensorActive(bool)));

    iface = new QDBusInterface(SERVICE_NAME, OBJECT_NAME, INTERFACE_NAME, QDBusConnection::sessionBus(), this);
    if (iface) {
        iface->call(QDBus::NoBlock, "getInitial");
    }
}

bool ProximityClient::sensorActive()
{
    return _sensorActive;
}

void ProximityClient::setSensorActive(bool value)
{
    qDebug() << "setSensorActive" << value;
    if (iface) {
        if (value) {
            iface->call(QDBus::NoBlock, "enable");
        }
        else {
            iface->call(QDBus::NoBlock, "disable");
        }
    }
}

bool ProximityClient::callActive()
{
    return _callActive;
}

bool ProximityClient::proxClose()
{
    return _proxClose;
}

void ProximityClient::enable()
{
    if (iface) {
        iface->call(QDBus::NoBlock, "enable");
    }
}

void ProximityClient::disable()
{
    if (iface) {
        iface->call(QDBus::NoBlock, "disable");
    }
}

void ProximityClient::onCallActive(bool value)
{
    _callActive = value;
    Q_EMIT callActiveChanged();
}

void ProximityClient::onProxClose(bool value)
{
    _proxClose = value;
    Q_EMIT proxCloseChanged();
}

void ProximityClient::onSensorActive(bool value)
{
    _sensorActive = value;
    Q_EMIT sensorActiveChanged();
}
