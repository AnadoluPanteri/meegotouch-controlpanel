/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <MApplicationPage>
#include "pages.h"

class QGraphicsLinearLayout;
class MLabel;
class MHelpButton;

class DcpPage : public MApplicationPage
{
    Q_OBJECT
    Q_PROPERTY (bool isStandalone READ isStandalone);

public:
    DcpPage();
    ~DcpPage();

    virtual void createContent();

    PageHandle handle () const;
    virtual void setHandle (const PageHandle &handle);
    virtual void setHandle (
                    PageHandle::PageTypeId id, 
                    const QString &param = "");

    PageHandle referer () const;
    virtual void setReferer (const PageHandle &referer);
    virtual void setReferer (
                    PageHandle::PageTypeId id, 
                    const QString &param = "");

    QGraphicsLinearLayout *mainLayout();

    virtual void reload();

    void addMAction (MAction* action);

    virtual bool preventQuit ();
    void setPreventQuit (bool prevent) { m_PreventQuit = prevent; }
    bool isStandalone () const;

signals:
    void openSubPage (PageHandle handle);
    void openSubPageWithReferer (const PageHandle &, const QString &, int);
    void mainPageIconClicked ();

protected:
    void setTitleLabel (const QString& helpId = QString());
    void appendWidget (QGraphicsWidget *widget);
    void setTitleStyleName (const QString& style);
    virtual void dismissEvent (MDismissEvent *event);

private:
    void createLayout();
    MAction* createSpacerAction();

    MLabel* m_TitleLabel;
    MHelpButton* m_HelpButton;
    PageHandle m_Handle;
    PageHandle m_Referer;
    MAction* m_ActionHack;
    bool m_PreventQuit;
    friend class Ut_DcpPage;
};

#endif

