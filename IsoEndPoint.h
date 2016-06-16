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

#ifndef _ISOENDPOINT_H_
#define _ISOENDPOINT_H_

#include <gp_Pnt.hxx>

namespace IsoAlgo
{
    /**
     * @brief component end point data.
     */
    class IsoEndPoint
    {
    public:
        //! default constructor.
        IsoEndPoint(void);

        //! default destructor.
        ~IsoEndPoint(void);

        //! fill data from string.
        void Fill(const std::string& theBuffer);

        //! set model position.
        void SetPosition(const gp_Pnt& thePosition);

        //! set nominal diameter.
        void SetDiameter(const double theDiameter);

        //! get model position.
        const gp_Pnt& GetPosition(void) const;

        //! get nominal diameter.
        double GetDiameter(void) const;

    private:
        //! end point in 3d space.
        gp_Pnt myPosition;

        //! connection type.
        std::string myConnectType;

        //! nominal diameter.
        double myDiameter;
    };

}
#endif // _ISOENDPOINT_H_
