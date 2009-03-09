#include "dcpmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duimultilayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"
#include "pages.h"
#include "maintranslations.h"

#include "dcpbuttoncomponent.h"

DcpMainPage::DcpMainPage() :
	DcpCategoryPage()
{
    m_PageId = Pages::MAIN;
    m_Referer = Pages::NOPAGE;
}


void DcpMainPage::createContent()
{
    DcpCategoryPage::createContent();
    setTitle(DcpMain::settingsTitle);

    m_Category->setMaxColumns(2);

    // most recent used items:
    DcpRecentlyUsedComponent* recentlyComp = new DcpRecentlyUsedComponent(
                                                    m_Category);


    m_Category->add(recentlyComp);

//DcpButtonComponent *tmp = new DcpButtonComponent(m_Category, 
//    DcpAppletDb::instance()->applet("Language"));
//m_Category->append(tmp);

    // category descriptions:

    for (int i=0; true; i++)
       {
        DcpCategoryInfo info = DcpMain::CategoryInfos[i];
        if (info.title == "")
             break;

        DcpDescriptionComponent *component = new DcpDescriptionComponent(
                m_Category, info.title);
        component->setDescription("<span>" + info.description + "</span>");
        component->setSubPageId(info.subPageId);
        connect(component, SIGNAL(openSubPage(Pages::Id, const QString&)),
                this, SIGNAL(openSubPage(Pages::Id, const QString&)));
        m_Category->append(component);
    }

    // reset settings:
    DcpDescriptionComponent *resetSettings = new DcpDescriptionComponent(
            m_Category, DcpMain::resetSettingsTitle);
    resetSettings->setDescription(DcpMain::resetSettingsDescription);
    resetSettings->setFullRowSize ();
 //   connect(resetSettings, SIGNAL(openSubPage(Pages::Id)),
//            this, SLOT(onResetSettingsClicked()));
    m_Category->add(resetSettings);
}



void DcpMainPage::organizeContent(Dui::Orientation ori)
{
    DcpPage::organizeContent(ori);
    m_Category->onOrientationChange(ori);
    qDebug() << "ORI!!";
}


// ----- FOR TESTING -----
#include <duideviceprofile.h>
void DcpMainPage::onResetSettingsClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();
   // m_Category->onOrientationChange(profile->orientation());

    if ( profile->orientation() == Dui::Portrait ) {
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
// --

