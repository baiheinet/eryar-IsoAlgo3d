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

#ifndef _ISOCOMPONENT_H_
#define _ISOCOMPONENT_H_

#include "IsoAlgoAbs.h"
#include "IsoEndPoint.h"

namespace IsoAlgo
{
    /**
     * @brief piping component data.
     */
    class IsoComponent
    {
    public:
        //! default contructor.
        IsoComponent(const std::string& theType = "");

        //! default destrcutor.
        ~IsoComponent(void);

        void AddAttribute(const std::string& theKey, const std::string& theValue);

        const std::string& GetType(void) const;

        const std::string& GetSkey(void) const;

        const IsoEndPoint& GetArrivePoint(void) const;

        const IsoEndPoint& GetLeavePoint(void) const;

        const IsoEndPoint& GetCentrePoint(void) const;

        const IsoEndPoint& GetBranchPoint1(void) const;

        const IsoEndPoint& GetBranchPoint2(void) const;

    protected:
        void buildDirection(const std::string& theExpression);

    private:
        //! component type.
        std::string myType;

        //! symbol key.
        std::string mySkey;

        //! end point count.
        int myEndPointCount;

        //! component arrive point.
        IsoEndPoint myArrivePoint;

        //! component leave point.
        IsoEndPoint myLeavePoint;

        //! component centre point.
        IsoEndPoint myCentrePoint;

        //! component branch point1, such as tee. etc.
        IsoEndPoint myBranchPoint1;

        //! component branch point2, such as cross. etc.
        IsoEndPoint myBranchPoint2;

        //! flat direction, valve handle direction. etc.
        gp_Dir myDirection;

        //! component attributes.
        std::map<std::string, std::string> myAttributes;
    };
}
#endif // _ISOCOMPONENT_H_
