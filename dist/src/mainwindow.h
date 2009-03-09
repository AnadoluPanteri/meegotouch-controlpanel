#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DuiApplicationWindow>
#include "pages.h"
class MainWindow : public DuiApplicationWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void changePage(Pages::Id pageId, const QString &param="");
    void homeClicked();
    void backClicked();
    void onRotateClicked();
private:
    Pages::Id m_Referer;
};

#endif // MAINWINDOW_H
