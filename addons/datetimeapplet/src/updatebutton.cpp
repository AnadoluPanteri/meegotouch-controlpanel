#include "updatebutton.h"
#include "dcpspaceritem.h"
#include "datetimetranslation.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>

int height = 88;

UpdateButton::UpdateButton(DuiWidget *parent)
             :DuiWidget(parent)
{
    initWidget();
}

UpdateButton::~UpdateButton()
{
}

void UpdateButton::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(5);

    // lineLayout
    DuiLayout *lineLayout = new DuiLayout(0);
    lineLayout->setAnimator(0);
    lineLayout->setContentsMargins(20.0, 0.0, 20.0, 0.0);
    DuiGridLayoutPolicy *lineLayoutPolicy = new DuiGridLayoutPolicy(lineLayout);
    lineLayout->setPolicy(lineLayoutPolicy);
    lineLayoutPolicy->setSpacing(3);

    // automaticLabel
    DuiLabel *automaticLabel = new DuiLabel(DcpDateTime::AutomaticUpdateText, this);
    automaticLabel->setObjectName("AutomaticLabel");
    automaticLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    automaticLabel->setAcceptedMouseButtons(0);
    automaticLabel->setMinimumWidth(
            DuiSceneManager::instance()->visibleSceneRect().width() - 130);

    // toggleButton
    DuiButton *toggleButton = new DuiButton(this);
    toggleButton->setObjectName("ToggleButton");
    toggleButton->setMinimumSize(QSize(48, 48));
    toggleButton->setMaximumSize(QSize(48, 48));
    toggleButton->setCheckable(true);
    toggleButton->setTextVisible(false);
    
    // add items to lineLayoutPolicy
    lineLayoutPolicy->addItemAtPosition(automaticLabel, 0, 0);
    lineLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            0, 1);
    lineLayoutPolicy->addItemAtPosition(toggleButton, 0, 2);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(lineLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            2, Qt::AlignCenter);

    // set fixed height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(onOrientationChanged()));
    onOrientationChanged();
}

void UpdateButton::onOrientationChanged()
{
    DuiSceneManager* manager = DuiSceneManager::instance();
    if (manager == 0) return;

    switch (manager->orientation()) {
        case Dui::Landscape:
            this->setMinimumWidth(manager->visibleSceneRect().width() - 30);
            this->setMaximumWidth(manager->visibleSceneRect().width() - 30);
            break;
        case Dui::Portrait:
            this->setMinimumWidth(manager->visibleSceneRect().width() / 2 - 30);
            this->setMaximumWidth(manager->visibleSceneRect().width() / 2 - 30);
            break;
        default:
            break;
    }
}

