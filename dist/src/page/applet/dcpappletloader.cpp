#include "dcpappletloader.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include <QPluginLoader>

DcpAppletLoader::DcpAppletLoader(DcpAppletMetadata *metadata):
    m_Metadata(metadata)
{
    load();
}

DcpAppletLoader::~DcpAppletLoader()
{
    if (m_Applet)
        delete m_Applet;
}
 
void DcpAppletLoader::load()
{
    QPluginLoader loader(m_Metadata->fullBinary());
    if (!loader.load())
    {
        m_ErrorMsg = "Loading applet failed: " + loader.errorString();
        m_Applet = NULL;
    } else
    {
        QObject *object = loader.instance();
        m_Applet = qobject_cast<DcpAppletIf*>(object);
        if (m_Applet)
            m_ErrorMsg = "Can't convert object to ExampleAppletInterface.";
       
    }

}
