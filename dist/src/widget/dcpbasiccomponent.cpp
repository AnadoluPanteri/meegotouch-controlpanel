#include "dcpbasiccomponent.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiimage.h>
#include <duitheme.h>

#include "dcpimageutils.h"
#include "dcpappletmetadata.h"

#include <QDebug>

//DuiButton* DcpBasicComponent::m_TriangleButtonOriginal = NULL;

static const int TRIANGLESIZE = 20;

DcpBasicComponent::DcpBasicComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Metadata(metadata), m_Z(1)
{
  //createContents();
  m_GridLayout = new DuiGridLayout();

  //if (m_TriangleButtonOriginal==NULL) {
  //    m_TriangleButtonOriginal = newButton(TRIANGLESIZE, "TriangleButton");
  //}

}


DcpBasicComponent::~DcpBasicComponent()
{

}

void DcpBasicComponent::initLayout()
{
    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Layout->addItem(m_GridLayout);
    setLayout(m_Layout);
}


void DcpBasicComponent::initRow(int height)
{
    m_GridLayout->setRowMinimumHeight ( 0, height );
    m_GridLayout->setRowMaximumHeight ( 0, height );
}

void DcpBasicComponent::initRow2(int height)
{
    for (int i=0;i<2;i++) {
        m_GridLayout->setRowMinimumHeight ( i, height/2 );
        m_GridLayout->setRowMaximumHeight ( i, height/2 );
    };
}

void DcpBasicComponent::initColumn(int s1, int s2, int s3)
{
    m_GridLayout->setColumnMinimumWidth ( 0, s1 );
    m_GridLayout->setColumnMaximumWidth ( 0, s1 );

    m_GridLayout->setColumnMinimumWidth ( 1, s2 );
    m_GridLayout->setColumnMaximumWidth ( 1, s2 );

    m_GridLayout->setColumnMinimumWidth ( 2, s3 );
    m_GridLayout->setColumnMaximumWidth ( 2, s3 );
}


void DcpBasicComponent::initColumn(int s1, int s2, int s3, int s4, int s5)
{
    m_GridLayout->setColumnMinimumWidth ( 0, s1 );
    m_GridLayout->setColumnMaximumWidth ( 0, s1 );

    m_GridLayout->setColumnMinimumWidth ( 1, s2 );
    m_GridLayout->setColumnMaximumWidth ( 1, s2 );

    m_GridLayout->setColumnMinimumWidth ( 2, s3 );
    m_GridLayout->setColumnMaximumWidth ( 2, s3 );

    m_GridLayout->setColumnMinimumWidth ( 3, s4 );
    m_GridLayout->setColumnMaximumWidth ( 3, s4 );

    m_GridLayout->setColumnMinimumWidth ( 4, s5 );
    m_GridLayout->setColumnMaximumWidth ( 4, s5 );
}

DuiButton* DcpBasicComponent::newButton(int size, const QString &name)
{
    DuiButton *button = new DuiButton;
    button->setObjectName(name);
    button->setMinimumWidth(size);
    button->setMaximumWidth(size);
    button->setMinimumHeight(size);
    button->setMaximumHeight(size);

    button->setZValue(m_Z);
    m_Z++;

    return button;
}

DuiButton* DcpBasicComponent::newButton(int width, int height, const QString &name)
{
    DuiButton *button = new DuiButton;
    button->setObjectName(name);
    button->setMinimumWidth(width);
    button->setMaximumWidth(width);
    button->setMinimumHeight(height);
    button->setMaximumHeight(height);

    button->setZValue(m_Z);
    m_Z++;

    return button;
}


DuiLabel* DcpBasicComponent::newLabel(int height, const QString &text, const QString &objectName, Qt::Alignment alignment)
{
    DuiLabel *label = new DuiLabel(text);
    label->setObjectName(objectName);
//    m_UpLabel->setMinimumWidth(labelWidth);
//    m_UpLabel->setMaximumWidth(labelWidth);
    label->setMinimumHeight(height);
    label->setMaximumHeight(height);
    label->setAlignment(alignment);
    label->setAcceptedMouseButtons(0);

    label->setZValue(m_Z);
    m_Z++;

    return label;
}

DuiImage* DcpBasicComponent::newImage(const QString &name, int size, int borderSize, const QColor &color)
{
    DuiImage *image = new DuiImage(name);
    image->setMinimumWidth(size);
    image->setMaximumWidth(size);
    image->setMinimumHeight(size);
    image->setMaximumHeight(size);
//    m_Image->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    image->setAcceptedMouseButtons(0);

    image->setBorders(borderSize, borderSize, borderSize, borderSize);
    image->setBackgroundColor(color);

    image->setZValue(m_Z);
    m_Z++;

    return image;
}

void DcpBasicComponent::createContents()
{
}

/*
void DcpBasicComponent::setEnable(bool enable) {

    m_Enable = enable;

    if (m_Enable) {
        m_SmallButtonOn->show();
        m_SmallButtonOff->hide();
        m_DisableButton->hide();
    } else {
        m_SmallButtonOn->hide();
        m_SmallButtonOff->hide();
        m_DisableButton->show();
    }

}*/


/*
void DcpButtonComponent::paint (QPainter * painter,
                                     const QStyleOptionGraphicsItem * option,
                                     QWidget * widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);

    // TODO: move to stylesheet
    int borderWidth = 2;
    QColor lineColor = QColor::fromRgb(0x3d, 0x2a, 0x0f);
    QColor bgColor = Qt::black;
    QColor borderColor = Qt::lightGray;
    // --

    if (m_Background.isNull() || m_Background.width() != size().width()){
        m_Background = DcpImageUtils::instance()->scaledPixmap(
                "C2-container-dark-landscape-123px", size().toSize());
        if (m_Background.isNull()) {
            qWarning ("theme lacks bg picture for settings component");
            return;
        }
    }
    painter->drawPixmap(QPoint(0, 0), m_Background);


//    DuiWidget::paint(painter, option, widget);

    // line between the title & description:
    QPen pen = painter->pen();
    pen.setColor(lineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    qreal y = m_Caption->y() + m_Caption->size().height() + 2;
    painter->drawLine(borderWidth, y, size().width()-2*borderWidth, y);

}*/


void DcpBasicComponent::setTitleAlignment(Qt::Alignment align)
{
        Q_UNUSED(align);
 //   m_Caption->setAlignment(align);
}


void DcpBasicComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItem(item);
}

void DcpBasicComponent::switchToSubPage()
{
    emit openSubPage(subPage());
}

void DcpBasicComponent::bigClicked()
{
    switchToSubPage();
}

