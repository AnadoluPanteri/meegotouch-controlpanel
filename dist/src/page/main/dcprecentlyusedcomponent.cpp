#include "dcprecentlyusedcomponent.h"

#include "dcpappletdb.h"
#include "maintranslations.h"

#include "dcpmostusedcategory.h"
#include <duicontainer.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>


/*!
 * \class DcpRecentlyUsedComponent
 * \brief A component for the recently used applets
 *
 * It is supplies the background and title for around DcpMostUsedCategory,
 * which contains the buttons. (Actually uses DuiContainer for that.)
 */

DcpRecentlyUsedComponent::DcpRecentlyUsedComponent(
                            DcpCategory *category,
                            QGraphicsWidget *parent)
        : DcpComponent(category, DcpMain::mostRecentUsedTitle, parent)
{
    createContents();
}

void DcpRecentlyUsedComponent::createContents()
{
    DuiContainer *box = new DuiContainer(this);
    box->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
    box->setTitle(title());

    m_MostUsedCategory = new DcpMostUsedCategory("TXT");
    connect(m_MostUsedCategory, SIGNAL(openSubPage(Pages::Handle)),
                this, SIGNAL(openSubPage(Pages::Handle)));

    box->setCentralWidget(m_MostUsedCategory);
 //   box->setCentralWidget(button);

    DuiLayout* layout = new DuiLayout(this);
    layout->setAnimator(NULL);
    layout->setContentsMargins(0,0,0,0);
    DuiLinearLayoutPolicy* layoutPolicy = new DuiLinearLayoutPolicy(layout,
                                                            Qt::Vertical);
    layoutPolicy->addItemAtPosition(box, 0);
    layout->setPolicy(layoutPolicy);
}


void DcpRecentlyUsedComponent::onOrientationChange
                            (const Dui::Orientation &orientation)
{
    m_MostUsedCategory->onOrientationChange(orientation);
}

