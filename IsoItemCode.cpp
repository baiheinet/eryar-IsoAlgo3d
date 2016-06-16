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

#include "IsoItemCode.h"

using namespace IsoAlgo;

IsoItemCode::IsoItemCode(const std::string& theCode)
: myCode(theCode)
{
}

IsoItemCode::~IsoItemCode(void)
{
}

const std::string& IsoItemCode::GetCode() const
{
    return myCode;
}

void IsoItemCode::AddAttribute(const std::string& theKey, const std::string& theValue)
{
    myAttributes.insert(std::make_pair(theKey, theValue));
}
