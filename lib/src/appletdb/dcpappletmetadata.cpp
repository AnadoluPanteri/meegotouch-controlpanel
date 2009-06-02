#include <QDateTime>
#include "dcpappletmetadata.h"
#include "dcpapplet.h"
#include <duilocale.h>
#include <QDebug>
#include "dcpappletmetadata_p.h"
#include "dcpwidgettypes.h"
#include <DuiDesktopEntry>
#include "dcpappletloader.h"
#include "dcpbrief.h"
#include "dcpappletif.h"

enum  {
    KeyCategory = 0,
    KeyOrder,
    KeyOnPicture,
    KeyOffPicture,
    KeyDisabledPicture,

    KeyWidgetType,
    KeyAlign,
    KeyToggle,
    KeySmallToggle,

    KeyText2,
    KeyImage,
    KeyButtonCSS,
    KeyLabel1CSS,
    KeyLabel2CSS,
    KeyUsage,
    KeyBinary,

    KeyName,
    KeyNameId,
    KeyNameCatalog,

    KeyValuePath,
    KeyCount,
};

const QString Keys[KeyCount] = {
    "DCP/Category",
    "DCP/Order",
    "DCP/OnPicture",
    "DCP/OffPicture",
    "DCP/DisabledPicture",

    "DCP/WidgetType",
    "DCP/Align",
    "DCP/Toggle",
    "DCP/SmallToggle",

    "DCP/Text2",
    "DCP/Image",
    "DCP/ButtonCSS",
    "DCP/Label1CSS",
    "DCP/Label2CSS",
    "DCP/Usage",
    "DUI/X-DUIApplet-Applet",

    "Desktop Entry/Name",
    "Desktop Entry/X-logical-id",
    "Desktop Entry/X-translation-catalog",
    "DCP/ValuePath"
};


DcpAppletMetadataPrivate::DcpAppletMetadataPrivate()
    : m_AppletLoader(0),
      m_Brief(0),
      m_DesktopEntry(0)
{
}

DcpAppletMetadataPrivate::~DcpAppletMetadataPrivate()
{
    if (m_AppletLoader) delete m_AppletLoader;
    if (m_Brief) delete m_Brief;
    if (m_DesktopEntry) delete m_DesktopEntry;
}


DcpAppletMetadata::DcpAppletMetadata(const QString& filename)
    : d (new DcpAppletMetadataPrivate)
{
    d->m_DesktopEntry = new DuiDesktopEntry(filename);
}

DcpAppletMetadata::~DcpAppletMetadata()
{
    delete d;
}

// TODO XXX rename
bool
DcpAppletMetadata::isValid() const
{
    return desktopEntry()->isValid();
}

// TODO XXX rename
bool
DcpAppletMetadata::isModified() const
{
    QFileInfo info(d->m_FileInfo.fileName());
    bool modified = info.lastModified() >  d->m_FileInfo.lastModified();
    d->m_FileInfo = info;
    return modified;
}

QString
DcpAppletMetadata::category() const
{
    return desktopEntryStr(KeyCategory);
}

/*
QString
DcpAppletMetadata::icon() const
{
    return brief()->icon();
}
*/

QString
DcpAppletMetadata::binary() const
{
    return desktopEntryStr(KeyBinary);
}

QString
DcpAppletMetadata::fullBinary() const
{
    return DcpApplet::Lib + binary();
}

int DcpAppletMetadata::widgetTypeID() const
{
    if (brief() != 0) {
        return brief()->widgetTypeID();
    }

  // old way, TODO consider removing it and forcing the applets to supply a widgettype
  QString type = desktopEntryStr(KeyWidgetType);

  for(int i=0; i<WIDGETN; i++)
    if (WIDGETNAME[i]==type) {
      return i;
    }

  qWarning() << "widgettype unspecified for " << name();
  return DCPLABEL2;  //default
}

Qt::Alignment DcpAppletMetadata::align() const
{
    if (brief()){
        return brief()->align();
    }

    // old way, try desktop file
    QString align = desktopEntryStr(KeyAlign).toUpper();
    if (align == "LEFT")
        return Qt::AlignLeft;
    if (align == "RIGHT")
        return Qt::AlignRight;

    qWarning() << Q_FUNC_INFO << "no data"; // default
    return Qt::AlignLeft; 
}

bool DcpAppletMetadata::toggle() const
{
    if (brief()){
        return brief()->toggle();
    }

    qWarning() << Q_FUNC_INFO << "no brief"; // default
    return false;
}

QString DcpAppletMetadata::text1() const
{
    QString id = desktopEntryStr(KeyNameId);
    QString name = desktopEntryStr(KeyName);
//    QString catalog = value(Keys[KeyNameCatalog]).toString();
    return DuiLocale::trid(qPrintable(id), qPrintable(name));
}

QString DcpAppletMetadata::text2() const
{
    if (brief())
        return brief()->valueText();

    // old way, TODO change it to return QString() if test data is not needed
    return desktopEntryStr(KeyText2);
}

QString DcpAppletMetadata::image() const
{
    if (brief())
        return brief()->image();

    // old way
    return desktopEntryStr(KeyImage);
}

int DcpAppletMetadata::usage() const
{
    // TODO implement
    return desktopEntry()->value(Keys[KeyUsage]).toInt();
}

int DcpAppletMetadata::order() const
{
    return desktopEntry()->value(Keys[KeyOrder]).toInt();
}

DcpAppletIf* DcpAppletMetadata::applet() const
{
    if (d->m_AppletLoader == 0){
        d->m_AppletLoader = new DcpAppletLoader(this);
    }
//    qDebug() << Q_FUNC_INFO << d->m_AppletLoader->errorMsg() << fullBinary();
    return d->m_AppletLoader->applet();
}

DuiDesktopEntry* DcpAppletMetadata::desktopEntry() const
{
    Q_ASSERT (d->m_DesktopEntry);
    return d->m_DesktopEntry;
}

DcpBrief* DcpAppletMetadata::brief() const
{
    if (d->m_Brief == 0) {
        if (applet() != 0) {
            d->m_Brief = applet()->constructBrief();
            if (d->m_Brief != 0){
                connect (d->m_Brief, SIGNAL(valuesChanged()),
                         this, SIGNAL(briefChanged()));
            }
        }
    }
    return d->m_Brief;
}

// TODO XXX rename
QString DcpAppletMetadata::name() const
{
    return desktopEntry()->name();
}

// TODO XXX rename
QString DcpAppletMetadata::fileName() const
{
    return desktopEntry()->fileName();
}

QString DcpAppletMetadata::desktopEntryStr(int id) const
{
    return desktopEntry()->value(Keys[id]).toString().trimmed();
}


