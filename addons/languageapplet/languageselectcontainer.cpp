#include "languageselectcontainer.h"
#include "languagelistitem.h"
#include "grouptitlewidget.h"
#include "dcplanguageconf.h"

#include <QDebug>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>

LanguageSelectContainer::LanguageSelectContainer(const QString &title,
                                                 QStringList itemList,
                                                 DuiWidget *parent)
                        :DuiWidget(parent),
                         m_titleText(title),
                         m_itemList(itemList)
{
    initWidget();
    this->selectItem(DcpLanguageConf::instance()->displayLanguage());
}

LanguageSelectContainer::~LanguageSelectContainer()
{
}

void LanguageSelectContainer::selectItem(const QString &text)
{
    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        if (text == m_listItemVector[i]->langCode())
        {
            m_listItemVector[i]->checked(true);
        }
    }
}

void LanguageSelectContainer::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    GroupTitleWidget *titleLabel = new GroupTitleWidget(m_titleText, this);
    mainLayoutPolicy->addItemAtPosition(titleLabel, 0);

    // gridLayout
    DuiLayout *gridLayout = new DuiLayout(NULL);
    gridLayout->setAnimator(NULL);
    DuiGridLayoutPolicy *itemLayout = new DuiGridLayoutPolicy(gridLayout);
    gridLayout->setPolicy(itemLayout);
    
    QStringListIterator iterator(m_itemList);
    while (iterator.hasNext())
    {
        QString langCode = iterator.next();
        m_listItemVector.append(new LanguageListItem(langCode,
                                DcpLanguageConf::fullName(langCode), this));
    }

    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        itemLayout->addItemAtPosition(m_listItemVector[i], i / 2, i % 2);
        connect(m_listItemVector[i], SIGNAL(clicked(LanguageListItem *)), 
                this, SLOT(itemClicked(LanguageListItem *)));
    }

    mainLayoutPolicy->addItemAtPosition(gridLayout, 1);
}

void LanguageSelectContainer::itemClicked(LanguageListItem *item)
{
    item->checked(true);
    DcpLanguageConf::instance()->setDisplayLanguage(item->langCode());
    emit changeBackToMain();
}

