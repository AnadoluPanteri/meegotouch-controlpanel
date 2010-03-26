#ifndef FT_DCPAPPLETOBJECT_H
#define FT_DCPAPPLETOBJECT_H

#include <QtTest/QtTest>
#include <QObject>
#include <DuiApplication>

// the real unit/DcpAppletObject class declaration
#include "dcpappletobject.h"

Q_DECLARE_METATYPE(DcpAppletObject*);

class Ft_DcpAppletObject : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testLoad();
    void testLoadManyTimes();

    

private:
    void testApplet(const char *desktopfile);
    void doAppletTest (const char *desktopfile);

    DuiApplication*  m_app;
};

#endif
