/*
IsoAlgo3d - PCF format 3d visualization tool.
Copyright (C) 2016 Shing Liu

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2 of the License, or any later
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

Copy of the GNU General Public License is in LICENSE.txt and  
on <http://www.gnu.org/licenses/>.
*/

#include "occQt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    occQt w;
    w.show();

    return a.exec();
}
