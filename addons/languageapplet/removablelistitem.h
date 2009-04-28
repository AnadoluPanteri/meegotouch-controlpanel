#ifndef REMOVABLELISTITEM_H
#define REMOVABLELISTITEM_H

#include <duiwidget.h>

class DuiButton;

class RemovableListItem : public DuiWidget
{
    Q_OBJECT

public:
    RemovableListItem(const QString &upText,
                      const QString &downText,
                      DuiWidget *parent = 0);
    RemovableListItem(const QString &text,
                      DuiWidget *parent = 0);
    virtual ~RemovableListItem();

protected:
    void initWidget();

private:
    QString m_UpText;
    QString m_DownText;
    DuiButton *m_RemoveButton;

private slots:
    virtual void removeClicked();

signals:
    void clicked(RemovableListItem*);
};
#endif // REMOVABLELISTITEM_H
