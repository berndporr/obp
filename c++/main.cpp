/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *             (C) 2013 by Bernd Porr                                      *
 *             (C) 2020 by Belinda Kneubühler                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "obp.h"
#include <iostream>
#include <QApplication>

#include "Processing.h"

int main(int argc, char **argv) {
//    QApplication app(argc, argv);
//    MainWindow mainWindow;
//
//    mainWindow.show();
//    mainWindow.resize(1400, 400);
//    return app.exec();
    Processing *procThread = new Processing();

    std::cout << "create thread" << std::endl;
    procThread->start();
    std::cout << "process started" << std::endl;
    procThread->startMeasurement();

    std::cout << "user input stops program (press ENTER)..." << std::endl;
    std::cin.get();
    procThread->stopMeasurement();
    procThread->stopThread();
    procThread->join();
    return 0;

}


