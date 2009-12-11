#include <cstdio>
#include <DuiApplicationWindow>
#include "service/duicontrolpanelservice.h"
#include "dcpappletdb.h"
#include "appleterrorsdialog.h"
#include <DcpDebug>
#include <DcpRetranslator>
#include <DuiApplication>
#include "dcpwrongapplets.h"

int main(int argc, char *argv[])
{
    DCP_FUNC_START
    qInstallMsgHandler(DcpDebug::dcpMsg);

    // parse for -h option
    for (int i = 1; i < argc; ++i) {
        QString s(argv[i]);
        if (s == "-h" || s == "-help") {
            QTextStream out(stdout);
            out << "Usage: " << argv[0] << 
                " [LIBDUI OPTION]... [-desktopdir DIR]\n\n";
            out << "  -desktopdir DIR     Load .desktop files from DIR";
            out << "\n\n";
            break;
        }
    }

    DuiApplication app(argc, argv);
    app.setAnimator(0);

    DuiControlPanelService* service = new DuiControlPanelService();

    QStringList args = app.arguments();
    int i = args.indexOf("-desktopdir", 1);
    if (i >= 1 && i + 1 < args.size()) {
        const QString &desktopDir = args.at(i + 1);
        qDebug() << "using desktopdir" << desktopDir;
        DcpAppletDb::initInstance(desktopDir);
    } else {
        DcpAppletDb::initInstance();
    }

    DcpRetranslator retranslator;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &retranslator, SLOT(retranslate()));

    DuiApplicationWindow* win = new DuiApplicationWindow;
    service->createStartPage();
    win->show();
    AppletErrorsDialog::showAppletErrors();

    DCP_FUNC_END
    int result = app.exec();

    // destructors
    delete win;
    DcpWrongApplets::destroyInstance();

    return result;
}

