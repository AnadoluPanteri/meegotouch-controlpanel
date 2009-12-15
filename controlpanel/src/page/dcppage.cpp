/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtDebug>

#include "dcppage.h"
#include <QGraphicsLinearLayout>
#include <DuiSceneManager>
#include <DuiApplication>
#include <DuiApplicationWindow>

//#define DEBUG
#include "dcpdebug.h"


DcpPage::DcpPage() : DuiApplicationPage()
{
    setEscapeButtonMode(DuiEscapeButtonPanelModel::BackMode);
}

DcpPage::~DcpPage()
{
}

void DcpPage::createContent()
{
    DuiApplicationPage::createContent();
    setObjectName("DcpPage");

    setEscapeButtonMode(DuiEscapeButtonPanelModel::BackMode);
    createLayout();
}

void DcpPage::createLayout()
{
    new QGraphicsLinearLayout(Qt::Vertical, centralWidget());
}

void DcpPage::organizeContent(const Dui::Orientation& ori)
{
    Q_UNUSED(ori);
}

void DcpPage::append (QGraphicsWidget* widget)
{
    Q_ASSERT(mainLayout());
    mainLayout()->addItem(widget);
}

void DcpPage::remove (QGraphicsWidget* widget)
{
    widget->deleteLater();
}

void DcpPage::connectSignals()
{
   connect(this, SIGNAL(backButtonClicked()), this, SLOT(back()));
   connectOrientation();
}

void DcpPage::connectOrientation()
{
//   DuiSceneManager* manager = sceneManager();
   DuiSceneManager* manager =
       DuiApplication::activeApplicationWindow()->sceneManager();
   if (manager) {
       // handle orientation change:
       connect(manager, SIGNAL(orientationChanged (Dui::Orientation)),
               this, SLOT(organizeContent(Dui::Orientation)));
   } else {
       qWarning("orientation connect fails");
   }
}

void DcpPage::disconnectSignals()
{
    DuiSceneManager* manager = sceneManager();
    if (manager) {
        disconnect(manager, SIGNAL(orientationChanged (Dui::Orientation)),
                this, SLOT(organizeContent(Dui::Orientation)));
    }

    disconnect(this, SIGNAL(backButtonClicked()), this, SLOT(back()));
}

Pages::Handle 
DcpPage::handle () const 
{
    return m_Handle;
}

/*!
 *
 * Please note that we can not allow a handle that has no name in it, because
 * we have to iodentify the 
 */
void 
DcpPage::setHandle (
        const Pages::Handle &handle) 
{
    m_Handle = handle;
    
    DCP_DEBUG ("*** m_Handle  = '%s'/%d", 
            DCP_STR (m_Handle.param), m_Handle.id);
    DCP_DEBUG ("*** m_Referer = '%s'/%d", 
            DCP_STR (m_Referer.param), m_Referer.id);
}

void 
DcpPage::setHandle (
        Pages::Id       id, 
        const QString  &param)
{
    m_Handle.id = id; 
    m_Handle.param = param;
    
    DCP_DEBUG ("*** m_Handle  = '%s'/%d", 
            DCP_STR (m_Handle.param), m_Handle.id);
    DCP_DEBUG ("*** m_Referer = '%s'/%d", 
            DCP_STR (m_Referer.param), m_Referer.id);
}

Pages::Handle 
DcpPage::referer () const 
{
    return m_Referer;
}

void 
DcpPage::setReferer (
        const Pages::Handle &referer) 
{
    m_Referer = referer;
   
    DCP_DEBUG ("*** m_Handle  = '%s'/%d", 
            DCP_STR (m_Handle.param), m_Handle.id);
    DCP_DEBUG ("*** m_Referer = '%s'/%d", 
            DCP_STR (m_Referer.param), m_Referer.id);
    #if 0
    Q_ASSERT (
            m_Handle.id == Pages::NOPAGE ||
            m_Handle.id != m_Referer.id || m_Handle.param != m_Referer.param);
    #endif
}

void 
DcpPage::setReferer (
        Pages::Id         id, 
        const QString    &param)
{
    m_Referer.id = id; 
    m_Referer.param = param;
    
    DCP_DEBUG ("*** m_Handle  = '%s'/%d", 
            DCP_STR (m_Handle.param), m_Handle.id);
    DCP_DEBUG ("*** m_Referer = '%s'/%d", 
            DCP_STR (m_Referer.param), m_Referer.id);
}

void 
DcpPage::back ()
{
    DCP_DEBUG ("Emitting openSubPage('%s'/%d)",
            DCP_STR (referer().param),
            referer().id);
    emit openSubPage (referer());
}


/* this is where pages optimize their open up times
 * default implementation sets the correct orientation */
void DcpPage::reload()
{
    if (sceneManager()) {
        organizeContent(sceneManager()->orientation());
    }
}

QGraphicsLinearLayout* DcpPage::mainLayout()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}

