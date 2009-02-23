#ifndef DUISETTINGSPAGE_H
#define DUISETTINGSPAGE_H

#include <DuiApplicationPage>
#include "pages.h"
class DuiPannableViewport;
class DuiSettingsPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DuiSettingsPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    Pages::Id pageId() const {return m_PageId;};
    void setPageId(Pages::Id pageId) {m_PageId = pageId;};
    Pages::Id referer() const {return m_Referer;};
    void setReferer(Pages::Id referer) {m_Referer = referer;};
signals:
    void openSubPage(Pages::Id subPageId);
protected:
   DuiPannableViewport *m_DesktopViewport;
   Pages::Id m_PageId;
   Pages::Id m_Referer;
private:
};

#endif // DUISETTINGSPAGE_H