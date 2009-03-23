#include "pages.h"

#include <QtDebug>


#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcprecentlyusedcomponent.h"

#include "dcpbuttoncomponent.h"
#include "dcplabelcomponent.h"
#include "dcplabel2component.h"
#include "dcpimagecomponent.h"
#include "dcplabel2buttoncomponent.h"
#include "dcplabel2imagecomponent.h"
#include "dcplabelbuttoncomponent.h"

#include "dcpmostusedcategory.h"

#include "dcpappletmetadata.h"
#include "dcpapplet.h"

#include "duilinearlayout.h"
#include "duigridlayout.h"

const static int SIZEWIDTH = 760;
const static int SIZEHEIGHT = 400;


DcpMostUsedCategory::DcpMostUsedCategory(const QString& title, QGraphicsWidget *parent) :
  DcpMainCategory(title, parent)
{
  createContents();

   //m_Background = new QPixmap("images/backgroundP.png");

}

void DcpMostUsedCategory::createContents()
{
    setMaxColumns(2);

    //dummy code
    /*   addWidget(DcpApplet::DefaultPath + "language.desktop");
    addWidget(DcpApplet::DefaultPath + "profile.desktop");
    
    addWidget(DcpApplet::DefaultPath + "region_format.desktop");
    addWidget(DcpApplet::DefaultPath + "ringtone.desktop");
  
    addWidget(DcpApplet::DefaultPath + "theme.desktop");
    addWidget(DcpApplet::DefaultPath + "wallpaper.desktop");*/

/*
    addWidget("browser.desktop");
    addWidget("wallpaper.desktop");
    addWidget("positioning.desktop");
    addWidget("display.desktop");
    addWidget("datetime.desktop");
    addWidget("passcode.desktop");
*/
   
    addComponent(DcpAppletDb::instance()->applet("Browser"));
    addComponent(DcpAppletDb::instance()->applet("Wallpaper"));
    addComponent(DcpAppletDb::instance()->applet("Positioning"));
    addComponent(DcpAppletDb::instance()->applet("Display"));
    addComponent(DcpAppletDb::instance()->applet("DateTime"));
    addComponent(DcpAppletDb::instance()->applet("Passcode"));
}

void DcpMostUsedCategory::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{
  DuiWidget::paint(painter, option, widget);
}

void DcpMostUsedCategory::addComponent(DcpAppletMetadata *metadata)
{
  DcpComponent *component = 0; 
  if (metadata->widgetType() == "DcpLabel") {
    component = new DcpLabelComponent(this, metadata);
  } else if (metadata->widgetType() == "DcpLabel2") {
    component = new DcpLabel2Component(this, metadata);
  } else if (metadata->widgetType() == "DcpButton") {
  } else if (metadata->widgetType() == "DcpImage") {
    component = new DcpImageComponent(this, metadata);
  } else if (metadata->widgetType() == "DcpSpec") {
  } else if (metadata->widgetType() == "DcpLabelButton") {
    component = new DcpLabelButtonComponent(this, metadata);
  } else if (metadata->widgetType() == "DcpLabel2Button") {
    component = new DcpLabel2ButtonComponent(this, metadata);
  } else if (metadata->widgetType() == "DcpLabel2Image") {
    component = new DcpLabel2ImageComponent(this, metadata);
  }
  if (component)
    {
        qDebug() << "DCP: connecting to " << metadata->name();
        component->setSubPage(Pages::APPLETFROMMOSTUSED, metadata->name());
        connect(component, SIGNAL(openSubPage(Pages::Handle)),                  
                this, SIGNAL(openSubPage(Pages::Handle)));
        append(component);
    }
}

void 
DcpMostUsedCategory::onOrientationChange (const Dui::Orientation &orientation)
{

    if (orientation == Dui::Portrait) {

        m_ColCount = 0;
        m_RowCount = 0;

        foreach(DcpComponent *component, m_Children) {
            m_Layout->removeAt(0);
        }

        setMaxColumns(1);

        foreach(DcpComponent *component, m_Children) {
            add(component);
        }


    }
    else {

        m_ColCount = 0;
        m_RowCount = 0;

         foreach(DcpComponent *component, m_Children) {
            m_Layout->removeAt(0);
        }

        setMaxColumns(2);

        foreach(DcpComponent *component, m_Children) {
            add(component);
        }
   }

return;
//DcpMainCategory::onOrientationChange (orientation);

//return;

    if (orientation == Dui::Portrait) {

        DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical);

int cnt = 0;

        foreach(DcpComponent *component, m_Children) {

        qDebug() << "CNT: " << cnt++;

            component->onOrientationChange(orientation);
            layout->addItem(component);
        }

        setLayout(layout);

        //delete m_Layout;
        //m_Layout = 0;

    }
    else {
   /*
      qDebug() << "  ----------------------------------------------  DcpMostUsedCategory   other";
       //DuiLinearLayout *layout = (DuiLinearLayout*)(this->layout());
        m_Layout = new DuiGridLayout();
        foreach(DcpComponent *component, m_Children)
        {
            component->onOrientationChange(orientation);
            if (m_ColSpans[component] == m_MaxColumns)
                add(component);
            else
                append(component);
        }
        //delete layout;
*/
        setLayout(m_Layout);
        qDebug() << "Changing orientation to Dui::Landscape";
   }
}   
