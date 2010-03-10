/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "pagefactory.h"
#include "dcpsinglecomponent.h"
#include "pages.h"

#include <QGraphicsLinearLayout>
#include <DuiContentItem>


#define DEBUG
#include "../../../lib/src/dcpdebug.h"


DcpSingleComponent::DcpSingleComponent (
        DcpComponent        *category,
        const QString       &logicalId,
        const QString       &title,
        const QString       &subTitle)
: DcpComponent (category, "", 0, logicalId)
{

    QGraphicsLinearLayout* layout;
    
    m_Item = new DuiContentItem(subTitle.isEmpty() ? DuiContentItem::SingleTextLabel:
                                DuiContentItem::TwoTextLabels);
    setTitle(title);
    if (!subTitle.isEmpty())
        setSubtitle(subTitle);
    layout = new QGraphicsLinearLayout (this);
    layout->addItem (m_Item);

    connect(m_Item, SIGNAL (clicked()),
            this, SLOT (activate()));
    
    setMattiID ("DcpSingleComponent::" + logicalId);
}

DcpSingleComponent::~DcpSingleComponent()
{
}

void
DcpSingleComponent::activate ()
{
    PageFactory *pageFactory = PageFactory::instance();
    pageFactory->changePage (subPage());
}

void
DcpSingleComponent::setTitle (const QString& title)
{
    m_Item->setTitle(title);
}

void
DcpSingleComponent::setSubtitle (const QString& subTitle)
{
    m_Item->setSubtitle(subTitle);
}
