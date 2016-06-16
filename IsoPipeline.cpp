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

#include "IsoPipeline.h"

using namespace IsoAlgo;

IsoPipeline::IsoPipeline(void)
{
}

IsoPipeline::~IsoPipeline(void)
{
    // free the memory.
    for (std::vector<IsoComponent*>::iterator ic = myComponents.begin(); ic != myComponents.end(); ++ic)
    {
        delete *ic;

        *ic = NULL;
    }

    for (std::map<std::string, IsoItemCode*>::iterator ii = myItemCodes.begin(); ii != myItemCodes.end(); ++ii)
    {
        delete ii->second;

        ii->second = NULL;
    }
}

void IsoPipeline::AddAttribute(const std::string &theKey, const std::string &theValue)
{
    myAttributes.insert(std::make_pair(theKey, theValue));
}

void IsoPipeline::AddComponent(IsoComponent *theComponent)
{
    myComponents.push_back(theComponent);
}

int IsoPipeline::GetComponentCount() const
{
    return static_cast<int> (myComponents.size());
}

const IsoComponent* IsoPipeline::GetComponent(int theIndex) const
{
    assert(theIndex >= 0 && theIndex < GetComponentCount());

    return myComponents.at(theIndex);
}

void IsoPipeline::AddItemCode(IsoAlgo::IsoItemCode *theCode)
{
    myItemCodes.insert(std::make_pair(theCode->GetCode(), theCode));
}
