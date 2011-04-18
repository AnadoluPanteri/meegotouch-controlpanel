include(../common_top.pri)

CONFIG += meegotouch duicontrolpanel

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpappletmanager

TEST_SOURCES = \
    $$SRCDIR/appletmanager/dcpappletmanager.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/qdir-fake.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletmanager.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletmanager.h \
    $$SRCDIR/appletmanager/dcpappletmanager.h \
    $$STUBSDIR/qdir-fake.h \
