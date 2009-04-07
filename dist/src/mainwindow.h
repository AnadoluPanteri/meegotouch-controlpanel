#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DuiApplicationWindow>
#include "pages.h"

class DcpPage;
class MainWindow : public DuiApplicationWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();
public slots:
    void changePage(Pages::Handle handle);
    void homeClicked();
    void backClicked();
    void onRotateClicked();
    void appletChangePage(DcpPage *page);
private:
    class DcpPage* m_CurrentPage;
};

#endif // MAINWINDOW_H
