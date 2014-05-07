#include <QGuiApplication>
#include <sailfishapp.h>

#include "proximitysocket.h"

Q_DECL_EXPORT
int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setOrganizationName("coderus");
    app->setApplicationName("proximity-speaker");
    QScopedPointer<ProximitySocket> socket(new ProximitySocket(app.data()));
    app->exec();
}


