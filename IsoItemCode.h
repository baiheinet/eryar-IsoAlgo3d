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

#ifndef _ISOITEMCODE_H_
#define _ISOITEMCODE_H_

#include "IsoAlgoAbs.h"

namespace IsoAlgo
{
    class IsoItemCode
    {
    public:
        IsoItemCode(const std::string& theCode);
        ~IsoItemCode(void);

        const std::string& GetCode(void) const;

        void AddAttribute(const std::string& theKey, const std::string& theValue);

    private:
        std::string myCode;

        std::string myNullString;

        std::map<std::string, std::string> myAttributes;
    };
}
#endif // _ISOITEMCODE_H_
