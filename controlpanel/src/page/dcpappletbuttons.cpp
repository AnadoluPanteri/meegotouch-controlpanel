#include "dcpappletbuttons.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpBriefComponent>
#include <DcpAppletMetadata>
#include <DcpApplet>

#include <QtDebug>
#include <DuiSceneManager>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>
#include "maintranslations.h"

#define DEBUG
#include "../../../lib/src/dcpdebug.h"
/*!
 * \class DcpAppletButtons
 * \brief A container which contains buttons that represents the
 * applets.
 */

DcpAppletButtons::DcpAppletButtons(const QString& logicalId,
                                   const QString& categoryName,
                                         const QString& title,
                                         QGraphicsWidget *parent) :
  DcpMainCategory(title, parent, logicalId), m_CategoryName(categoryName)
{
    setCreateSeparators(true);
    setMaxColumns(2);
    createContents();
    setMattiID("DcpAppletButtons::"+logicalId+"::"+categoryName);
}

void DcpAppletButtons::createContents()
{
    DcpAppletMetadataList list;
    if (logicalId() == DcpMain::mostRecentUsedTitleId)
        list = DcpAppletDb::instance()->listMostUsed();
    else
        list = DcpAppletDb::instance()->listByCategory(m_CategoryName);

	int cnt = 0;
	foreach (DcpAppletMetadata *item, list) {
		cnt++;
		if (cnt == list.count() && cnt % 2 == 1) //last item is impaired
			addComponent(item, true);
		else
			addComponent(item, false);
    }

    m_PortraitLayout->setObjectName("MostUsedItems");
    m_LandscapeLayout->setObjectName("MostUsedItems");
    setVerticalSpacing(0);
}

void DcpAppletButtons::addComponent(DcpAppletMetadata *metadata, bool fullLine)
{
    DcpBriefComponent *component = new DcpBriefComponent(metadata, this, logicalId());

	component->setSubPage (PageHandle::APPLET, metadata->name());

    connect (component, SIGNAL(openSubPage(PageHandle)), 
		    this, SIGNAL(openSubPage(PageHandle)));
    connect (component, SIGNAL(openSubPageWithReferer(const PageHandle &, const QString &, int)), 
        this, SIGNAL(openSubPageWithReferer(const PageHandle &, const QString &, int)));

    if (fullLine)
        add(component);
    else
        append(component);
}

void DcpAppletButtons::reload()
{
    deleteItems();
    createContents();
}

QString DcpAppletButtons::mattiID()
{
    return m_mattiID;
}

void DcpAppletButtons::setMattiID(const QString &mattiID)
{
    m_mattiID=mattiID;
}

