#include <QGuiApplication>
#include <sailfishapp.h>

#include "proximitysocket.h"

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

Q_DECL_EXPORT
int main(int argc, char *argv[])
{
    setuid(getpwnam("nemo")->pw_uid);
    setgid(getgrnam("privileged")->gr_gid);

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    app->setOrganizationName("coderus");
    app->setApplicationName("proximity-speaker");
    QScopedPointer<ProximitySocket> socket(new ProximitySocket(app.data()));
    app->exec();
}


