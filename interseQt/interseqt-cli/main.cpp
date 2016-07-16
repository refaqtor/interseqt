/****************************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright (c) 2016, shannon.mackey@refaqtory.com
* ***************************************************************************/
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("refaqtory");
    QCoreApplication::setOrganizationDomain("refaqtory.com");
    QCoreApplication::setApplicationName("interseqt");
    QCoreApplication::setApplicationVersion("0.1");

    QCoreApplication a(argc, argv);

    return a.exec();
}
