#ifndef DCPBACKGROUNDCOMPONENT_H
#define DCPBACKGROUNDCOMPONENT_H

#include "dcpcomponent.h"

class DuiLabel;
class DuiLinearLayout;
#include <QPixmap>

class DcpBackgroundComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpBackgroundComponent(DcpCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);
    ~DcpBackgroundComponent();

    virtual void setTitle(const QString& title);
    void setTitleAlignment(Qt::Alignment align);

        // Composite Pattern Interface
    virtual void add(DcpComponent *){}
    virtual void remove(DcpComponent *){}
    virtual void createContents();

protected:
    void addItem ( QGraphicsLayoutItem * item );

    virtual void resizeEvent ( QGraphicsSceneResizeEvent * event );

private:
    const QPixmap *m_Background;
    DuiLinearLayout *m_Layout;
    DuiLabel *m_Caption;
};


#endif // DCPBACKGROUNDCOMPONENT_H
