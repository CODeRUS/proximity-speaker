#include "proximitysocket.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

#define OBJECT_NAME "/"
#define SERVICE_NAME "org.coderus.proximityspeaker"

#define PROX_SOCKET "/sys/devices/virtual/input/input10/prx_detect"

ProximitySocket::ProximitySocket(QObject *parent) :
    _isEnabled(false),
    _callActive(false),
    _proxClose(false),
    QObject(parent)
{
    sensor = new QProximitySensor(this);
    connect(sensor, SIGNAL(readingChanged()), this, SLOT(sensorRead()));

    QDBusConnection::systemBus().connect("", "", "org.ofono.VoiceCall",
                                         "PropertyChanged", this, SIGNAL(ofonoPropertyChanged(QString,QDBusVariant)));

    QDBusConnection::sessionBus().registerService(SERVICE_NAME);
    QDBusConnection::sessionBus().registerObject(OBJECT_NAME,
                                                 this,
                                                 QDBusConnection::ExportAllSignals | QDBusConnection::ExportAllSlots);
}

ProximitySocket::~ProximitySocket()
{
}

bool ProximitySocket::setLoudspeaker(bool value)
{
    if (value) {
        return system("pactl set-sink-port sink.primary output-speaker") == 0;
    }
    else {
        return system("pactl set-sink-port sink.primary output-earpiece") == 0;
    }
}

void ProximitySocket::sensorRead()
{
    QFile f(PROX_SOCKET);
    if (f.exists() && f.open(QFile::ReadOnly)) {
        QByteArray data = f.read(1);
        qDebug() << "sensor data:" << data;
        f.close();
        _proxClose = data == "1";
    }
    if (_callActive) {
        setLoudspeaker(!_proxClose);
    }
    Q_EMIT proxClose(_proxClose);
}

void ProximitySocket::ofonoPropertyChanged(const QString &key, const QDBusVariant &value)
{
    if (key == "State") {
        qDebug() << "call state:" << value.variant().toString();
        _callActive = value.variant().toString() != "disconnected";
        if (!_callActive) {
            setLoudspeaker(false);
        }
        else if (!_proxClose) {
            setLoudspeaker(true);
        }
        Q_EMIT callActive(_callActive);
    }
}

void ProximitySocket::enable()
{
    qDebug() << "Client requested sensor enable";

    if (!_isEnabled) {
        sensor->start();
        _isEnabled = sensor->isActive();
        if (_callActive && !_proxClose) {
            setLoudspeaker(true);
        }
    }
    Q_EMIT sensorEnabled(_isEnabled);
}

void ProximitySocket::disable()
{
    qDebug() << "Client requested sensor disable";

    if (_isEnabled) {
        sensor->stop();
        _isEnabled = sensor->isActive();
        setLoudspeaker(false);
    }
    Q_EMIT sensorEnabled(_isEnabled);
}

void ProximitySocket::getInitial()
{
    qDebug() << "Client requested initial data";

    Q_EMIT callActive(_callActive);
    Q_EMIT proxClose(_proxClose);
    Q_EMIT sensorEnabled(_isEnabled);
}
