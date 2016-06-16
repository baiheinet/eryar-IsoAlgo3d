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

#ifndef _ISOPCFREADER_H_
#define _ISOPCFREADER_H_

#include "IsoPipeline.h"

namespace IsoAlgo
{
    /**
     * @brief PCF reader is used to read piping component data in PCF file.
     * What is a PCF file? http://www.alias.ltd.uk/pcf.asp
     *
     * The Piping Component File (PCF) is the primary input for Personal ISOGEN. PCFs are 
     * text files containing component and routing information. For each component, they will 
     * include various mandatory records to define the basic information of:
     *   + Type ¨C Flange, pipe, or valve, for example
     *   + Coordinates and size of the end-points
     *   + Shape (SKEY) to be used to represent the component on the isometric
     * PCFs are created by the piping design system extracting information from the piping 
     * model. A single PCF can contain the data for a number of pipelines, but generally, the 
     * piping design system extracts piping data for single pipelines only.Then Personal ISOGEN 
     * will produce isometrics for one pipeline at a time.
     *
     */
    class IsoPcfReader
    {
    public:
        //! constructor.
        IsoPcfReader(const std::string& thePcfName);
        ~IsoPcfReader(void);

        //! get the pipeline data.
        const IsoPipeline& GetPipeline(void) const;

    protected:
        void init(const std::string& thePcfName);

        void readConfig(std::ifstream& thePcfFile);

        void readPipeline(std::ifstream& thePcfFile);

        void readComponent(std::ifstream& thePcfFile);

        void readMaterial(std::ifstream& thePcfFile);

        void makeAttribute(std::string& thePcfLine, std::string& theKey, std::string& theValue);

    private:
        //! current line of the PCF.
        std::string myPcfLine;

        //! pipeline contains component data.
        IsoPipeline myPipeline;
    };
}
#endif // _ISOPCFREADER_H_
