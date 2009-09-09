#ifndef TIMEZONEVIEW_H
#define TIMEZONEVIEW_H

#include "dcpwidget.h"

class DuiTextEdit;
class TimeZoneContainer;

class TimeZoneView : public DcpWidget
{
    Q_OBJECT

public:
    TimeZoneView(QGraphicsWidget *parent = 0);
    virtual ~TimeZoneView();
    virtual bool back();

protected:
    void initWidget();

private:
    DuiTextEdit *m_TextEdit;
    TimeZoneContainer *m_TimeZoneContainer;

private slots:
    virtual void orientationChanged();
    virtual void clearTextEdit(DuiTextEdit *textEdit);
    virtual void filteringListItems();
    virtual void addMoreListItems();
};
#endif // TIMEZONEVIEW_H
