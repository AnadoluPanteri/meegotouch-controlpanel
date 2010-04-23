#include <QObject>

#include <QGraphicsSceneMouseEvent>

#include <dcpsinglecomponent.h>


#include "ut_dcpsinglecomponent.h"
#include "dcppage.h"
#include "pagefactory.h"

void Ut_DcpSingleComponent::init()
{
    m_subject = new DcpSingleComponent(0, "Logical ID", "title1", "title2");
    m_subject->setSubPage(PageHandle::LOOKANDFEEL, "Look & Feel");
}

void Ut_DcpSingleComponent::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpSingleComponent::initTestCase()
{
}

void Ut_DcpSingleComponent::cleanupTestCase()
{
}

void Ut_DcpSingleComponent::testCreation()
{
    QVERIFY(m_subject);
}

void Ut_DcpSingleComponent::testTitle()
{
    QCOMPARE(m_subject->title(), QString("title1"));
    m_subject->setTitle("another title");
    QCOMPARE(m_subject->title(), QString("another title"));
}

void Ut_DcpSingleComponent::testSubtitle()
{
    QVERIFY(m_subject->subtitle() == "title2");
    m_subject->setSubtitle("another subtitle");
    QVERIFY(m_subject->subtitle() == "another subtitle");
}

void Ut_DcpSingleComponent::testActivate()
{
    DcpPage *page = PageFactory::instance()->currentPage();
    QVERIFY(page == 0);
    m_subject->activate();
    page = PageFactory::instance()->currentPage();
    QVERIFY(page->handle().id == PageHandle::LOOKANDFEEL);
    QVERIFY(page->handle().param == "Look & Feel");
}


QTEST_APPLESS_MAIN(Ut_DcpSingleComponent)