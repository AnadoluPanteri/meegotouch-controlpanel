#include "mainwindow.h"
#include "pagefactory.h"
#include "dcppage.h"
#include <duideviceprofile.h>
#include <QtDebug>
#include <duinavigationbar.h>

MainWindow::MainWindow()
{
   Pages::Handle handle = {Pages::MAIN, ""};
  // Pages::Handle handle = {Pages::APPLET, "Language"};
   changePage(handle);
}

void MainWindow::homeClicked()
{
    /*
   Pages::Handle handle = {Pages::MAIN, ""};
   changePage(handle);
*/
   onRotateClicked();
}

void MainWindow::backClicked()
{
    PageFactory::instance()->back();

    /* overrides dui behaviour that it changes to close when switching
       inside a page TODO remove */
    if (PageFactory::instance()->currentPage()->handle().id == Pages::APPLET) {
        navigationBar()->showBackButton();
    }
}

MainWindow::~MainWindow()
{
}

void
MainWindow::changePage(Pages::Handle handle)
{
    DcpPage *page = PageFactory::instance()->create(handle);
    connect (page, SIGNAL(openSubPage(Pages::Handle)), this,
        SLOT(changePage(Pages::Handle)));
    connect(page, SIGNAL(backButtonClicked()), this, SLOT(backClicked()));
    page->appear(DuiSceneWindow::DestroyWhenDone); //TODO
}


void MainWindow::onRotateClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();

    if ( profile->orientation() == Dui::Portrait ) {
        qDebug() << "mode changes to Angle0";
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        qDebug() << "mode changes to Angle90";
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
