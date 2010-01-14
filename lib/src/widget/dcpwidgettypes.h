/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPWIDGETTYPES_H
#define DCPWIDGETTYPES_H
#include <QString>

namespace DcpWidgetType
{
        enum Id {
            BriefInvalid = 0,
            Label,
            Toggle,
            Image,
            IdCount
        };
        const QString  
        names[IdCount] = 
        {
            "DcpBriefWidgetInvalid",
            "DcpLabel",
            "DcpLabelButton",
            "DcpLabelImage",
        };
        bool isIdValid(int id); 
};

static const QString  
Q_DECL_DEPRECATED WIDGETNAME[] = 
{
    "DcpBriefWidgetInvalid",
    "DcpLabel",
    "DcpLabel2",
    "DcpLabelButton",
    "DcpLabel2Button",
    "DcpLabel2Image",
    "DcpLabel2Toggle",
};
enum Q_DECL_DEPRECATED WIDGETTYPEID {
    DCPBRIEFWIDGETINVALID = 0,
    DCPLABEL,           //"DcpLabel"
    DCPLABEL2,          //"DcpLabel2"
    DCPLABELBUTTON,     //"DcpLabelButton"
    DCPLABEL2BUTTON,    //"DcpLabel2Button"
    DCPLABEL2IMAGE,     //"DcpLabel2Image"
    DCPLABEL2TOGGLE,    //"DcpLabel2Toggle"
    WIDGETN
};

#define DCP_WIDGET_TYPE_VALID(type) ((type) >= DCPLABEL && \
                                     (type) <= DCPLABEL2TOGGLE)

#endif // DCPWIDGETTYPES_H
