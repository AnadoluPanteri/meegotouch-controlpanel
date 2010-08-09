/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of mcontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef MCPCONTENTWIDGETPRIVATE_H
#define MCPCONTENTWIDGETPRIVATE_H

#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"

#include <MImageWidget>
#include <MButton>
#include <MLabel>

/******************************************************************************
 * Private data class for the McpContentWidget class.
 */
class McpContentWidgetPrivate {
public:
    McpContentWidgetPrivate ();

    DcpAppletObject *m_Applet;
    bool m_Hidden;

    QString m_MattiID;

    // for the image widget:
    QString m_ImageName; // either the image id or path

    bool m_LayoutIsToBeChanged;

    // widgets:
    MImageWidget* m_ImageW;
    MLabel* m_Text1W;
    MLabel* m_Text2W;
    MButton* m_ButtonW;
};

#endif // MCPCONTENTWIDGETPRIVATE_H
