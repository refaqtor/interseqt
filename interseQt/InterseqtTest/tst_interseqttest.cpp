#include <QString>
#include <QtTest>

class InterseqtTest : public QObject
{
    Q_OBJECT

public:
    InterseqtTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void initRepo();
};

InterseqtTest::InterseqtTest()
{
}

void InterseqtTest::initTestCase()
{
}

void InterseqtTest::cleanupTestCase()
{
}

void InterseqtTest::initRepo()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(InterseqtTest)

#include "tst_interseqttest.moc"
