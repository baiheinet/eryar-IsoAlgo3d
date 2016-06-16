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
#include "occView.h"

#include "IsoPcfReader.h"

#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>
#include <QProgressBar>

#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>

#include <GC_MakeArcOfCircle.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>

#include <AIS_Shape.hxx>


occQt::occQt(QWidget *parent)
    : QMainWindow(parent)
    , myProgressBar(new QProgressBar())
{
    ui.setupUi(this);

    myOccView = new OccView(this);

    setCentralWidget(myOccView);

    createActions();
    createMenus();
    createToolBars();
}

occQt::~occQt()
{

}

void occQt::createActions( void )
{
    connect(ui.actionLoadPCF, SIGNAL(triggered()), this, SLOT(loadPcf()));

    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui.actionZoom, SIGNAL(triggered()), myOccView, SLOT(zoom()));

    connect(ui.actionPan, SIGNAL(triggered()), myOccView, SLOT(pan()));

    connect(ui.actionRotate, SIGNAL(triggered()), myOccView, SLOT(rotate()));

    connect(ui.actionHome, SIGNAL(triggered()), myOccView, SLOT(reset()));

    connect(ui.actionFitAll, SIGNAL(triggered()), myOccView, SLOT(fitAll()));

    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void occQt::createMenus( void )
{
}

void occQt::createToolBars( void )
{
    myToolbar = addToolBar(tr("IsoAlgo3d"));
    myToolbar->addAction(ui.actionLoadPCF);
    myToolbar->addSeparator();
    myToolbar->addAction(ui.actionZoom);
    myToolbar->addAction(ui.actionPan);
    myToolbar->addAction(ui.actionRotate);
    myToolbar->addSeparator();
    myToolbar->addAction(ui.actionHome);
    myToolbar->addAction(ui.actionFitAll);
    myToolbar->addSeparator();
    myToolbar->addAction(ui.actionAbout);
}

void occQt::about()
{
    QMessageBox::about(this, tr("About IsoAlgo3d"),
        tr("<h2>IsoAlgo3d - PCF format 3d visualization tool.</h2>"
        "<p>Copyright &copy; 2016 Shing Liu"
        "<p>Feedback: Shing Liu(eryar@163.com)"
        "<p>Version: 1.0"));
}

void occQt::loadPcf()
{
    QStringList aPcfFiles = QFileDialog::getOpenFileNames(this, tr("Load PCF File"), "", tr("PCF Files(*.pcf)"));

    // show progress bar when building the piping model.
    this->statusBar()->addWidget(myProgressBar);
    myProgressBar->setMinimum(0);
    myProgressBar->setMaximum(aPcfFiles.size());

    for (int i = 0; i < aPcfFiles.size(); ++i)
    {
        myProgressBar->setValue(i + 1);

        readPcfFile(aPcfFiles.at(i));
    }

    // hide the progress bar when finished.
    this->statusBar()->removeWidget(myProgressBar);
}

void occQt::readPcfFile(const QString& thePcfName)
{
    if (thePcfName.isEmpty())
    {
        return;
    }

    IsoAlgo::IsoPcfReader aPcfReader(thePcfName.toStdString());

    const IsoAlgo::IsoPipeline& aPipeline = aPcfReader.GetPipeline();

    for (int i = 0; i < aPipeline.GetComponentCount(); ++i)
    {
        const IsoAlgo::IsoComponent* aComponent = aPipeline.GetComponent(i);

        TopoDS_Shape aTopoShape = buildShape(aComponent);
        if (aTopoShape.IsNull() || myOccView->getContext().IsNull())
        {
            continue;
        }

        Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
        myOccView->getContext()->Display(anAisShape, false);
    }

    myOccView->fitAll();
}

TopoDS_Shape occQt::buildShape(const IsoAlgo::IsoComponent *theComponent)
{
    TopoDS_Shape aComponentShape;

    if (theComponent->GetType() == "PIPE")
    {
        buildPipe(theComponent, aComponentShape);
    }
    else if (theComponent->GetType() == "ELBOW")
    {
        buildElbow(theComponent, aComponentShape);
    }

    return aComponentShape;
}

void occQt::buildPipe(const IsoAlgo::IsoComponent *theComponent, TopoDS_Shape &theShape)
{
    Standard_Real aDiameter = theComponent->GetArrivePoint().GetDiameter();
    gp_Pnt aArrivePoint = theComponent->GetArrivePoint().GetPosition();
    gp_Pnt aLeavePoint = theComponent->GetLeavePoint().GetPosition();

    gp_Vec aVector(aArrivePoint, aLeavePoint);
    gp_Ax2 anAxis(aArrivePoint, gp_Dir(aVector));

    theShape = BRepPrimAPI_MakeCylinder(anAxis, aDiameter * 0.5, aVector.Magnitude()).Shape();
}

void occQt::buildElbow(const IsoAlgo::IsoComponent *theComponent, TopoDS_Shape &theShape)
{
    gp_Pnt aArrivePoint = theComponent->GetArrivePoint().GetPosition();
    gp_Pnt aLeavePoint = theComponent->GetLeavePoint().GetPosition();
    gp_Pnt aCentrePoint = theComponent->GetCentrePoint().GetPosition();

    gp_Vec aVector(aArrivePoint, aCentrePoint);
    gp_Ax2 anAxis(aArrivePoint, gp_Dir(aVector));

    GC_MakeArcOfCircle anArcMaker(aArrivePoint, aVector, aLeavePoint);

    TopoDS_Shape aProfile = BRepBuilderAPI_MakeEdge(gp_Circ(anAxis, theComponent->GetArrivePoint().GetDiameter()/2.0)).Shape();
    TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(anArcMaker.Value()).Edge();
    TopoDS_Wire aSpine = BRepBuilderAPI_MakeWire(anEdge).Wire();

    BRepOffsetAPI_MakePipe aPipeMaker(aSpine, aProfile);
    if (aPipeMaker.IsDone())
    {
        theShape = aPipeMaker.Shape();
    }
}
