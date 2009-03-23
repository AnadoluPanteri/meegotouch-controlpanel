#ifndef DCPCATEGORYPAGE_H
#define DCPCATEGORYPAGE_H

#include "dcppage.h"
class DcpMainCategory;
class QGraphicsSceneResizeEvent;

class DcpCategoryPage : public DcpPage
{
    Q_OBJECT
public:
    DcpCategoryPage();
    virtual void createContent();

protected:
//    virtual void resizeEvent ( QGraphicsSceneResizeEvent * event );

protected:
    DcpMainCategory *m_Category;

};

#endif // DCPCATEGORYPAGE_H
