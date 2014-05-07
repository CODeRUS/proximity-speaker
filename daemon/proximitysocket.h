#ifndef PROXIMITYSOCKET_H
#define PROXIMITYSOCKET_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QProximitySensor>
#include <QProximityReading>
#include <QDBusVariant>

class ProximitySocket : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.coderus.proximityspeaker")
public:
    explicit ProximitySocket(QObject *parent = 0);
    virtual ~ProximitySocket();

private:
    bool setLoudspeaker(bool value);

    QProximitySensor *sensor;

    bool _isEnabled;
    bool _callActive;
    bool _proxClose;

signals:
    void callActive(bool value);
    void proxClose(bool value);
    void sensorEnabled(bool value);

private slots:
    void sensorRead();
    void ofonoPropertyChanged(const QString &key, const QDBusVariant &value);

public slots:
    void enable();
    void disable();
    void getInitial();

};

#endif // PROXIMITYSOCKET_H
