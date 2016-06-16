/**
 * IsoAlgo - piping Isometric drawing generation Algorithm.
 * Copyright (C) 2013 to current year Shing Liu
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Homepage:
 *  http://www.cppblog.com/eryar/
 * 
 * Feedback:
 *   IsoAlgo@gmail.com
 *   eryar@163.com
 */

#include "IsoAlgoAbs.h"
#include "IsoEndPoint.h"

using namespace IsoAlgo;

IsoEndPoint::IsoEndPoint(void)
: myDiameter(0.0)
{
}

IsoEndPoint::~IsoEndPoint(void)
{
}

void IsoEndPoint::Fill(const std::string &theBuffer)
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    std::stringstream ss(theBuffer);
    ss >> x >> y >> z >> myDiameter >> myConnectType;

    myPosition.SetCoord(x, y, z);
}

const gp_Pnt& IsoEndPoint::GetPosition() const
{
    return myPosition;
}

double IsoEndPoint::GetDiameter() const
{
    return myDiameter;
}
