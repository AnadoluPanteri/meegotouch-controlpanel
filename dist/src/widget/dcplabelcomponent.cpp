#include "dcplabelcomponent.h"

#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include <QDebug>

#include <duigridlayoutpolicy.h>

#include <duiabstractlayoutanimator.h>


DcpLabelComponent::DcpLabelComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{
    createContents();
    m_EnableToggle = metadata->toggle();
}

DcpLabelComponent::~DcpLabelComponent()
{
}


void DcpLabelComponent::createContents()
{

    //dummy, must modify constructor
    //dummy data
    QString upLabel = metadata()->text1();
 
    //dummy, must modify constructor  
    int smallWidth = 20;    //0,1
   
   // int width = smallWidth*2 + m_LabelWidth2;

    //initColumn(smallWidth, smallWidth, m_LabelWidth2 );

    initColumn(smallWidth, 0, 0);

    initRow(m_Height);
  
    m_BigButton = newButton(m_Width, m_Height, CSS_BIGBUTTON);
    m_UpLabel = newLabel(m_Height, upLabel, CSS_UPLABEL, Qt::AlignLeft|Qt::AlignVCenter);
    m_TriangleButton = newButton(m_TriangleSize, CSS_TRIANGLEBUTTON);

    //m_GridLayout->addItem(m_BigButton, 0, 0, 2, 3, Qt::AlignLeft);
    //m_GridLayout->addItem(m_TriangleButton, 0, 1, Qt::AlignCenter);
    //m_GridLayout->addItem(m_UpLabel, 0, 2, Qt::AlignCenter);

    //m_buttonLayoutPolicy->addItemAtPosition

    m_WidgetLayoutPolicy->addItemAtPosition(m_BigButton, 0, 0, 2, 3, Qt::AlignLeft);
    m_WidgetLayoutPolicy->addItemAtPosition(m_TriangleButton, 0, 1, 1, 1,Qt::AlignCenter);
    m_WidgetLayoutPolicy->addItemAtPosition(m_UpLabel, 0, 2, 1, 1,Qt::AlignCenter);

    connect(m_BigButton, SIGNAL(clicked()), this, SLOT(bigClicked()));

    initLayout();
}
