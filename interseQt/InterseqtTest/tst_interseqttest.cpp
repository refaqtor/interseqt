/****************************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright (c) 2016, shannon.mackey@refaqtory.com
* ***************************************************************************/
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
    QCoreApplication::setOrganizationName("refaqtory");
    QCoreApplication::setOrganizationDomain("refaqtory.com");
    QCoreApplication::setApplicationName("interseqt");
    QCoreApplication::setApplicationVersion("0.1");
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
