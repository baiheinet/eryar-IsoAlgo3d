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

#ifndef OCCQT_H
#define OCCQT_H


#include "ui_occQt.h"

#include "IsoComponent.h"

#include <TopoDS_Shape.hxx>

class QProgressBar;

class OccView;

//! Qt main window which include OpenCASCADE for its central widget.
class occQt : public QMainWindow
{
    Q_OBJECT

public:
    //! constructor/destructor.
    occQt(QWidget *parent = 0);
    ~occQt();

protected:
    //! create all the actions.
    void createActions(void);

    //! create all the menus.
    void createMenus(void);

    //! create the toolbar.
    void createToolBars(void);

protected:
    //! read PCF file.
    void readPcfFile(const QString& thePcfName);

    //! build component shape.
    TopoDS_Shape buildShape(const IsoAlgo::IsoComponent* theComponent);

    //! build pipe model.
    void buildPipe(const IsoAlgo::IsoComponent* theComponent, TopoDS_Shape& theShape);

    //! build elbow model.
    void buildElbow(const IsoAlgo::IsoComponent* theComponent, TopoDS_Shape& theShape);

private slots:
    //! load PCF file.
    void loadPcf(void);

    //! show about box.
    void about(void);

private:
    Ui::occQtClass ui;

private:
    //! the toolbars of IsoAlgo3d.
    QToolBar* myToolbar;

    //! the progress bar.
    QProgressBar* myProgressBar;

    // wrapped the widget for occ.
    OccView* myOccView;
};

#endif // OCCQT_H
