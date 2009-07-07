#ifndef TIMEZONELISTITEM_H
#define TIMEZONELISTITEM_H

#include <DuiWidget>

class DuiLabel;
class DuiButton;
class DuiSeparator;

class TimeZoneListItem : public DuiWidget
{
    Q_OBJECT

public:
    TimeZoneListItem(QString timezone, QString country, QString gmt, QString city,
                     DuiWidget *parent = 0);
    virtual ~TimeZoneListItem();
    QString timeZone();
    QString country();
    QString gmt();
    QString city();
    void checked(bool ok);
    bool isChecked();
    void filtered(bool ok);
    bool isFiltered();
    void setVisibleSeparator(bool enable);

protected:
    void initWidget();
    //! \reimp
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //! \reimp_end

private:
    QString m_TimeZone;
    QString m_Country;
    QString m_Gmt;
    QString m_City;
    bool m_Checked;
    bool m_Filtered;
    DuiLabel *m_CountryLabel;
    DuiLabel *m_GmtCityLabel;
    DuiButton *m_CheckMark;
    DuiSeparator *m_GraySeparator;

signals:
    void clicked(TimeZoneListItem *item);
};
#endif // TIMEZONELISTITEM_H

