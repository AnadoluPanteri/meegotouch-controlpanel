/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#include "dcpappletplugin.h"
#include "dcpappletplugin_p.h"
#include "dcpappletif.h"
#include "dcpappletmetadata.h"
#include <QPluginLoader>
#include "dcpwrongapplets.h"

#define DEBUG
#define WARNING
#include "dcpdebug.h"

DcpAppletPlugin::DcpAppletPlugin(DcpAppletMetadata *metadata):
   d_ptr(new DcpAppletPluginPrivate(metadata))
{
    load();
}

DcpAppletPluginPrivate::DcpAppletPluginPrivate(DcpAppletMetadata* metadata):
    appletMetadata(metadata),
    appletInstance(0)
{
}

DcpAppletPluginPrivate::~DcpAppletPluginPrivate ()
{}

DcpAppletPlugin::~DcpAppletPlugin()
{
    if (d_ptr->appletInstance)
        delete d_ptr->appletInstance;

    d_ptr->appletInstance = 0;
}

/*!
 * \returns The applet interface of the applet loader.
 *
 * Returns the applet interface, the interface object created by the applet if
 * the applet loaded successfully. Returns NULL if the applet was not loaded.
 * Please note that this method might return NULL!
 */
DcpAppletIf *
DcpAppletPlugin::applet() const
{
    /*
     * It is possible that the applet was disabled before, but it is enabled
     * now. 
     */
  /*  DCP_DEBUG ("The applet is %s",
            metadata()->isDisabled() ? "disabled" : "enabled");
    if (d_ptr->appletInstance == 0 && 
            metadata() && metadata()->isDisabled())
        loadPluginFile (metadata()->fullBinary());
*/
    return d_ptr->appletInstance; 
}

bool
DcpAppletPlugin::isAppletLoaded() const
{
    return d_ptr->appletInstance != 0;
}

/*!
 * \returns the metadata of the applet
 */
DcpAppletMetadata*
DcpAppletPlugin::metadata () const 
{ 
    return d_ptr->appletMetadata;
}

/*!
 * \returns the error message string describes the problem why the applet was
 *   not loaded. Returns the empty string if the applet was loaded 
 *   successfully.
 */
const QString 
DcpAppletPlugin::errorMsg () const
{ 
    return d_ptr->errorMsg; 
}

/*
 * Loads the applet from a binary file (a shared object file) stores the 
 * DcpAppletIf plugin object and initializes it by calling the init() virtual 
 * function. Returns true if the object was loaded and initialized.
 */
bool 
DcpAppletPlugin::loadPluginFile (
        const QString &binaryPath)
{
    /*
     * The external program applets does not use binary file to load. Here is a
     * protection for them, but I'm not sure this is how we should handle the
     * issue.
     */
    if (binaryPath.isEmpty())
        return true;
    /*
     * We only check that the applet is blacklicted or not (due for example to a
     * previous segfault), if the applet is disabled. This way the application
     * can re-enable the applet. We currently re-enable the applet when the user
     * explicitly clicks on the applet brief.
     */
    if (metadata() && metadata()->isDisabled ()) {
        /*if (DcpWrongApplets::instance()->isAppletRecentlyCrashed (binaryPath)) 
            d_ptr->errorMsg =  "The '" + binaryPath + "/" +
                metadata()->name() +
                "' is a blacklisted applet";
        else
            d_ptr->errorMsg =  "The '" + binaryPath + "/" +
                metadata()->name() +
                "' is a disabled applet";

        DCP_WARNING ("%s", DCP_STR (d_ptr->errorMsg));
        qCritical() << d_ptr->errorMsg;
        */
        d_ptr->appletInstance = 0;
        return false;
    }

    QPluginLoader loader (binaryPath);
    if (!loader.load ()) {
        d_ptr->errorMsg = "Loading of the '" + binaryPath + "/" +
            d_ptr->appletMetadata->name() +
            "' applet failed: " + loader.errorString();
        DCP_WARNING ("%s", DCP_STR (d_ptr->errorMsg));
        qCritical () << d_ptr->errorMsg;
    } else {
        QObject *object = loader.instance();
        d_ptr->appletInstance = qobject_cast<DcpAppletIf*>(object);

        if (!d_ptr->appletInstance) {
            d_ptr->errorMsg = "Loading of the '" + binaryPath + "/" +
                metadata()->name() +
                "' applet failed: Invalid ExampleAppletInterface object.";
            DCP_WARNING ("%s", DCP_STR (d_ptr->errorMsg));
            qCritical() << d_ptr->errorMsg;
            return false;
        } else {
            DCP_DEBUG ("Initializing %s", DCP_STR (binaryPath));
            d_ptr->appletInstance->init ();
        }
    }

    return true;
}

/*
 * Loads a DSL (Declarative Settings Language) file.
 * Not implemented yet.
 */
bool 
DcpAppletPlugin::loadDslFile (
        const QString &binaryPath)
{
    Q_UNUSED (binaryPath);
    DCP_WARNING ("Loading of the DSL file is not implemented yet.");

    return false;
}

void 
DcpAppletPlugin::load ()
{
    QString binaryPath = d_ptr->appletMetadata->fullBinary();
    QString dslFilename = d_ptr->appletMetadata->dslFilename ();

    DCP_DEBUG ("*** binaryPath          = '%s'", DCP_STR (binaryPath));
    DCP_DEBUG ("*** dslFilename         = '%s'", DCP_STR (dslFilename));
    DCP_DEBUG ("*** applicationCommand  = '%s'", 
            DCP_STR (d_ptr->appletMetadata->applicationCommand ()));

    if (!binaryPath.isEmpty()) {
        loadPluginFile (binaryPath);
    } else if (!dslFilename.isEmpty()) {
        loadDslFile (dslFilename);
    }
}
