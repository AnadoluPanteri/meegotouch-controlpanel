#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H
#include <QList>
#include <QMap>
#include <QString>
#include "dcpapplet.h"
/*!
    \class DcpAppletMetadata    
    \brief This singleton class keeps track of all installed applets of Conrol Panel
    \details  Applet database can be filled with desktop files and then can
     be queried by category, usage, by applet name.
     The database is live, so any changes in the desktop files are applied on refresg
*/
class DcpAppletMetadata;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;
typedef QMap<QString, DcpAppletMetadata*> DcpAppletMetadataMap;


class DcpAppletDb
{
public:
    /*! \brief Gives back the db instance
        \param pathName the initial path where the desktop files are found, 
         needed only first time*/
    static DcpAppletDb *instance(const QString &pathName=DcpApplet::DefaultPath);
    /*! \brief adds files at a specified path pathName to the db */
    void addPath(const QString &pathName);
 
    /*! \brief Database destructor */
    virtual ~DcpAppletDb();

    /*! \brief Queries the db for a specified applet category
        \param category the name of the category
        \return the metadata list of the matching applets
    */
    DcpAppletMetadataList listByCategory(const QString& category);

    /*! \brief List the six most used applets
        \details gives backt the most used componnents but six*/
    DcpAppletMetadataList listMostUsed();

    /*! \reaturn metadata of an applet by name*/
    DcpAppletMetadata *applet(const QString& name);

    /*! \brief add one file to the db */
    void addFile(const QString& filename);

    /*! \brief erase metadata from the db */
    void eraseEntry(DcpAppletMetadata *metadata);

    /*! \brief checks all the deskop files and reloads or erases them if needed*/
    void refresh();

    /*! \brief destroys all the contents (metadata) of the db */
	void destroy(void);
protected:
    /*! \brief protected constructor for singleton*/
    DcpAppletDb(const QString &pathName);
    /*! \brief refresh a specified path*/
    void refreshPath(const QString &pathName);
private:
    DcpAppletMetadataMap m_AppletsByName;  
    DcpAppletMetadataMap m_AppletsByFile; 
    QList<QString> m_Paths; 
    static DcpAppletDb *sm_Instance;
};
#endif // DCPAPPLETDB_H
