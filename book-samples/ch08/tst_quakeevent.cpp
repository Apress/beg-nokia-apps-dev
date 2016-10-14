#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDebug>
#include "quakeevent.h"

class TestQuakeEvent : public QObject
{
    Q_OBJECT

public:
    TestQuakeEvent();

private:
    QuakeEvent *mEvent;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testConstructor();
    void testSetGet();
    void testIsEmpty();
    void testClear();
    void testComparator();

    void testId();
    void testSummary();
    void testWhen();
    void testWhere();
    void testMagnitude();
    void testPosition();
    void testElevation();
    void testHtml();
    void testDistanceTo();

};

TestQuakeEvent::TestQuakeEvent()
{
}

void TestQuakeEvent::initTestCase() {
    mEvent = new QuakeEvent();
}

void TestQuakeEvent::cleanupTestCase() {
    delete mEvent;
}

void TestQuakeEvent::init() {
    mEvent->clear();
    mEvent->set("title",   "M 2.6, Hawaii region, Hawaii");
    mEvent->set("point",   "19.9770 -156.8687");
    mEvent->set("elev",    "-7900");
    mEvent->set("summary", "<img src=\"http://earthquake.usgs.gov/images/globes/20_-155.jpg\" alt=\"19.977&#176;N 156.869&#176;W\" align=\"left\" hspace=\"20\" /><p>Monday, September  6, 2010 15:19:09 UTC<br>Monday, September  6, 2010 05:19:09 AM at epicenter</p><p><strong>Depth</strong>: 7.90 km (4.91 mi)</p>");
}

void TestQuakeEvent::cleanup() {
    mEvent->clear();
}

void TestQuakeEvent::testConstructor() {
    // Use our own here so we override the init
    // and cleanup invocations
    QuakeEvent *e = new QuakeEvent();
    QVERIFY(e->isEmpty());
    delete e;
}

void TestQuakeEvent::testSetGet() {
    mEvent->set("arbitrary", "value");
    QVERIFY(mEvent->get("arbitrary")=="value");
}

// Failures may indicate a problem with either
// isEmpty or clear
void TestQuakeEvent::testIsEmpty() {
    QVERIFY(!mEvent->isEmpty());
    mEvent->clear();
    QVERIFY(mEvent->isEmpty());
}

// Failures may indicate a problem with either
// isEmpty or clear
void TestQuakeEvent::testClear() {
    QVERIFY(!mEvent->isEmpty());
    mEvent->clear();
    QVERIFY(mEvent->isEmpty());
}

void TestQuakeEvent::testComparator() {
    QuakeEvent *e = new QuakeEvent();
    e->set("summary", "<img src=\"http://earthquake.usgs.gov/images/globes/20_-155.jpg\" alt=\"19.977&#176;N 156.869&#176;W\" align=\"left\" hspace=\"20\" /><p>Monday, September  6, 2010 15:19:10 UTC<br>Monday, September  6, 2010 05:19:10 AM at epicenter</p><p><strong>Depth</strong>: 7.90 km (4.91 mi)</p>");
    QVERIFY(*mEvent < *e);
    delete e;
}

void TestQuakeEvent::testId() {
    mEvent->set("arbitrary", "123456789");
    QVERIFY(mEvent->get("arbitrary")=="123456789");
}

void TestQuakeEvent::testSummary() {
    QVERIFY(mEvent->summary() == "M 2.6, Hawaii region, Hawaii");
}

void TestQuakeEvent::testWhen() {
    // Ideally this would test a number of dates and times
    QDateTime when( QDate(2010, 9, 6),
                    QTime(15, 19, 9), Qt::UTC);

    QVERIFY(mEvent->when() == when);
}

void TestQuakeEvent::testWhere() {
    QVERIFY(mEvent->where() == "Hawaii region, Hawaii");
}

void TestQuakeEvent::testMagnitude() {
    float mag = (float)mEvent->magnitude();

    QCOMPARE(mag, (float)2.60);
}

void TestQuakeEvent::testPosition() {
    qDebug() << mEvent->position();
    QCOMPARE((float)mEvent->position().first,  (float)19.977);
    QCOMPARE((float)mEvent->position().second, (float)-156.869);
}

void TestQuakeEvent::testElevation() {
    QVERIFY(qFuzzyCompare(mEvent->elevation(), -7900.0));
}

void TestQuakeEvent::testHtml() {
    QVERIFY(mEvent->html() == "<img src=\"http://earthquake.usgs.gov/images/globes/20_-155.jpg\" alt=\"19.977&#176;N 156.869&#176;W\" align=\"left\" hspace=\"20\" /><p>Monday, September  6, 2010 15:19:09 UTC<br>Monday, September  6, 2010 05:19:09 AM at epicenter</p><p><strong>Depth</strong>: 7.90 km (4.91 mi)</p>");
}

void TestQuakeEvent::testDistanceTo() {
    qreal distance = mEvent->distanceTo(
        QPair<qreal, qreal>(37.0, -122.0));
    QCOMPARE((float)distance, (float)3870.68);
}

QTEST_APPLESS_MAIN(TestQuakeEvent);

#include "tst_quakeevent.moc"
