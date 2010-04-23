include(../common_top.pri)
CONFIG += meegotouch
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += ../doubles 
INCLUDEPATH += $$LIBDCPSRC
INCLUDEPATH += $$LIBDCPSRC/appletdb 

TARGET = ut_dcpsinglecomponent

TEST_SOURCES = \
    $$SRCDIR/component/dcpsinglecomponent.cpp \
    $$SRCDIR/page/pages.cpp \
    ../doubles/pagefactory-fake.cpp \
    ../doubles/dcppage-fake.cpp \
    ../doubles/dcpcomponent-fake.cpp \
    ../doubles/dcpappletplugin-fake.cpp \
    ../doubles/mdesktopentry-fake.cpp \
    ../doubles/mgconfitem-fake.cpp \
    ../doubles/mcontentitem-fake.cpp \
    ../doubles/mapplication-fake.cpp \
    ../doubles/mapplicationpage-fake.cpp \
    ../doubles/mapplicationwindow-fake.cpp \

# unit test and unit
SOURCES += \
    ut_dcpsinglecomponent.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpsinglecomponent.h \
    $$SRCDIR/component/dcpsinglecomponent.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/page/pages.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pagefactory.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

