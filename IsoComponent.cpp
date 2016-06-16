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

#include "IsoComponent.h"

using namespace IsoAlgo;

IsoComponent::IsoComponent(const std::string& theType/*=""*/)
: myType(theType)
, myEndPointCount(0)
{
}

IsoComponent::~IsoComponent(void)
{
}

void IsoComponent::AddAttribute(const std::string &theKey, const std::string &theValue)
{
    if ("END-POINT" == theKey)
    {
        switch (myEndPointCount)
        {
        case 0: /* arrive point */
            myArrivePoint.Fill(theValue);
            myAttributes.insert(std::make_pair(theKey + "1", theValue));
            break;

        case 1: /* leave point */
            myLeavePoint.Fill(theValue);
            myAttributes.insert(std::make_pair(theKey + "2", theValue));
            break;
        }

        ++myEndPointCount;

        return;
    }
    else if ("CENTRE-POINT" == theKey)
    {
        /* centre point */
        myCentrePoint.Fill(theValue);
    }
    else if ("BRANCH1-POINT" == theKey)
    {
        /* branch point 1 */
        myBranchPoint1.Fill(theValue);
    }
    else if ("BRANCH2-POINT" == theKey)
    {
        /* branch point 2 */
        myBranchPoint2.Fill(theValue);
    }
    else if ("SKEY" == theKey)
    {
        mySkey = theValue;
    }
    else if ("FLAT-DIRECTION" == theKey)
    {
        // set flat direction for eccentric reducer.
        // valve handle direction. etc.
        buildDirection(theValue);
    }

    myAttributes.insert(std::make_pair(theKey, theValue));
}

const std::string& IsoComponent::GetType() const
{
    return myType;
}

const std::string& IsoComponent::GetSkey() const
{
    return mySkey;
}

const IsoEndPoint& IsoComponent::GetArrivePoint() const
{
    return myArrivePoint;
}

const IsoEndPoint& IsoComponent::GetLeavePoint() const
{
    return myLeavePoint;
}

const IsoEndPoint& IsoComponent::GetCentrePoint() const
{
    return myCentrePoint;
}

void IsoComponent::buildDirection(const std::string &theExpression)
{
    static std::map<std::string, gp_Dir> aDirectionMap;

    aDirectionMap.insert(std::make_pair("E",  gp::DX()));
    aDirectionMap.insert(std::make_pair("W", -gp::DX()));
    aDirectionMap.insert(std::make_pair("N",  gp::DY()));
    aDirectionMap.insert(std::make_pair("S", -gp::DY()));
    aDirectionMap.insert(std::make_pair("U",  gp::DZ()));
    aDirectionMap.insert(std::make_pair("D", -gp::DZ()));

    std::map<std::string, gp_Dir>::const_iterator i = aDirectionMap.find(theExpression);
    if (i != aDirectionMap.end())
    {
        myDirection = i->second;
    }
}
