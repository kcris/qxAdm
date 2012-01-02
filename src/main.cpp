/*
 * Copyright (c) 2011, DidiSoft, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from DidiSoft,
 * or a written licence from an organisation licenced by DidiSoft
 * to grant such a licence.
 *
 * $Id:$
 * $Date:$
 * $Rev:$
 */


#include <QtGui/QApplication>
#include "MainWindow.h"

#include "AsocData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AsocData asoc;
    asoc.load("../var/qa.json");

    MainWindow w;
    w.show();

    return a.exec();
}
