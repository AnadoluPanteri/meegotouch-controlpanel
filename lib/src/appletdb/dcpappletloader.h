#ifndef DCPAPPLETLOADER_H
#define DCPAPPLETLOADER_H

#include <QObject>
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletLoader : QObject
{
    Q_OBJECT
public:
    DcpAppletLoader(const DcpAppletMetadata* metadata);
    virtual ~DcpAppletLoader();
    DcpAppletIf* applet() const {return m_Applet;};
    const DcpAppletMetadata* metadata() const {return m_Metadata;};
    const QString errorMsg() const {return m_ErrorMsg;};
protected:
    virtual void load();
private:
    const DcpAppletMetadata* m_Metadata;
    DcpAppletIf *m_Applet;
    QString m_ErrorMsg;
};

#endif // DCPAPPLETLOADER_H