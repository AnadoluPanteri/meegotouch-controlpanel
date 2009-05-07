#include "languagelabel.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duiseparator.h>

const int height = 88;
const int devide = 35;

LanguageLabel::LanguageLabel(const QString &upText,
                            const QString &downText,
                            DuiWidget *parent)
              :DuiWidget(parent),
               m_UpText(upText),
               m_DownText(downText)
{
    initWidget();
}

LanguageLabel::LanguageLabel(const QString &text,
                             DuiWidget *parent)
              :DuiWidget(parent),
               m_UpText(text),
               m_DownText(QString(""))
{
    initWidget();
}

LanguageLabel::~LanguageLabel()
{
}

void LanguageLabel::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(2);
    this->setAcceptedMouseButtons(0);
    
    // greySeparator
    m_GreySeparator = new DuiSeparator(this);
    m_GreySeparator->setObjectName("GreySeparator");
    m_GreySeparator->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);

    QString space("    ");

    if (m_DownText.isEmpty()) {
        // single label
        DuiLabel *label = new DuiLabel(space + m_UpText, this);
        label->setObjectName("LanguageLeftLabel");
        label->setAcceptedMouseButtons(0);
        mainLayoutPolicy->addItemAtPosition(
                     new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                     0, Qt::AlignCenter);
        mainLayoutPolicy->addItemAtPosition(label, 1, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayoutPolicy->addItemAtPosition(
                     new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                     2, Qt::AlignCenter);
        mainLayoutPolicy->addItemAtPosition(m_GreySeparator, 3, Qt::AlignCenter);   
    } else {
        // upLabel
        DuiLabel *upLabel = new DuiLabel(space + m_UpText, this);
        upLabel->setObjectName("LanguageUpLabel");
        upLabel->setAcceptedMouseButtons(0);

        // downLabel
        DuiLabel *downLabel = new DuiLabel(space + m_DownText, this);
        downLabel->setObjectName("LanguageDownLabel");
        downLabel->setAcceptedMouseButtons(0);

        mainLayoutPolicy->addItemAtPosition(
                        new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                        0, Qt::AlignCenter);
        mainLayoutPolicy->addItemAtPosition(upLabel, 1, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayoutPolicy->addItemAtPosition(downLabel, 2, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayoutPolicy->addItemAtPosition(
                        new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                        3, Qt::AlignCenter);
        mainLayoutPolicy->addItemAtPosition(m_GreySeparator, 4, Qt::AlignCenter);
    }
    this->setLayout(mainLayout);

    // fixed sizes
    setMinimumHeight(height);
    setMaximumHeight(height);

    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}


void LanguageLabel::onOrientationAngleChanged()
{
    switch(DuiDeviceProfile::instance()->orientation()) {
        case Dui::Landscape:
            m_GreySeparator->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
            m_GreySeparator->setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
            break;
        case Dui::Portrait:
            m_GreySeparator->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
            m_GreySeparator->setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - devide);
            break;
        default:
            break;
    }
}
