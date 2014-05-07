#ifndef PROXIMITYCLIENT_H
#define PROXIMITYCLIENT_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>

class ProximityClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool sensorActive READ sensorActive WRITE setSensorActive NOTIFY sensorActiveChanged)
    Q_PROPERTY(bool callActive READ callActive NOTIFY callActiveChanged)
    Q_PROPERTY(bool proxClose READ proxClose NOTIFY proxCloseChanged)
public:
    explicit ProximityClient(QObject *parent = 0);

private:
    QDBusInterface *iface;

    bool sensorActive();
    bool _sensorActive;
    void setSensorActive(bool value);

    bool callActive();
    bool _callActive;

    bool proxClose();
    bool _proxClose;

signals:
    void sensorActiveChanged();
    void callActiveChanged();
    void proxCloseChanged();

public slots:
    Q_INVOKABLE void enable();
    Q_INVOKABLE void disable();

private slots:
    void onCallActive(bool value);
    void onProxClose(bool value);
    void onSensorActive(bool value);

};

#endif // PROXIMITYCLIENT_H
