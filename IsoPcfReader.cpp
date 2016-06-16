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

#include "IsoPcfReader.h"

using namespace IsoAlgo;

IsoPcfReader::IsoPcfReader(const std::string& thePcfName)
{
    init(thePcfName);
}

IsoPcfReader::~IsoPcfReader(void)
{
}

void IsoPcfReader::init(const std::string &thePcfName)
{
    // set local language environment.
    std::locale::global(std::locale(""));
    std::ifstream aPcfFile(thePcfName.c_str());
    std::locale::global(std::locale("C"));

    // check PCF file read status.
    assert(aPcfFile.good());

    // add the PCF name for the pipeline.
    myPipeline.AddAttribute("IsoPcfName", thePcfName);

    // 1. read config data.
    readConfig(aPcfFile);

    // 2. read pipeline data.
    readPipeline(aPcfFile);

    // 3. read component data.
    readComponent(aPcfFile);

    // 4. read item code data.
    readMaterial(aPcfFile);

    // 5. close the PCF file.
    aPcfFile.close();
}

void IsoPcfReader::readConfig(std::ifstream &thePcfFile)
{
    while (std::getline(thePcfFile, myPcfLine))
    {
        if (myPcfLine.size() > 0 && myPcfLine.at(0) != ' ')
        {
            std::string aKey;
            std::string aValue;

            makeAttribute(myPcfLine, aKey, aValue);

            myPipeline.AddAttribute(aKey, aValue);

            if (myPcfLine.find("PIPELINE-REFERENCE") != std::string::npos)
            {
                return;
            }
        }
    }
}

void IsoPcfReader::readPipeline(std::ifstream &thePcfFile)
{
    while (std::getline(thePcfFile, myPcfLine))
    {
        if (myPcfLine.size() > 0 && myPcfLine.at(0) != ' ')
        {
            return;
        }
        else
        {
            std::string aKey;
            std::string aValue;

            makeAttribute(myPcfLine, aKey, aValue);

            myPipeline.AddAttribute(aKey, aValue);
        }
    }
}

void IsoPcfReader::readComponent(std::ifstream &thePcfFile)
{
    IsoComponent* aComponent = new IsoComponent(myPcfLine);

    while (std::getline(thePcfFile, myPcfLine))
    {
        if ("MATERIALS" == myPcfLine)
        {
            break;
        }

        if (myPcfLine.size() > 0 && myPcfLine.at(0) != ' ')
        {
            myPipeline.AddComponent(aComponent);

            aComponent = new IsoComponent(myPcfLine);
        }
        else
        {
            std::string aKey;
            std::string aValue;

            makeAttribute(myPcfLine, aKey, aValue);

            aComponent->AddAttribute(aKey, aValue);
        }
    }

    myPipeline.AddComponent(aComponent);
}

void IsoPcfReader::readMaterial(std::ifstream &thePcfFile)
{
    IsoItemCode* aItemCode = NULL;

    while (std::getline(thePcfFile, myPcfLine))
    {
        std::string aKey;
        std::string aValue;

        makeAttribute(myPcfLine, aKey, aValue);

        if (myPcfLine.size() > 0 && myPcfLine.at(0) != ' ')
        {
            aItemCode = new IsoItemCode(aValue);

            myPipeline.AddItemCode(aItemCode);
        }
        else
        {
            aItemCode->AddAttribute(aKey, aValue);
        }
    }
}

void IsoPcfReader::makeAttribute(std::string &thePcfLine, std::string& theKey, std::string& theValue)
{
    std::stringstream ss(thePcfLine);
    ss >> theKey;

    theValue = thePcfLine.substr(thePcfLine.find(theKey) + theKey.size());
    theValue.erase(0, theValue.find_first_not_of(" /t/n/r"));
}

const IsoPipeline& IsoPcfReader::GetPipeline() const
{
    return myPipeline;
}
