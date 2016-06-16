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

#ifndef _ISOPIPELINE_H_
#define _ISOPIPELINE_H_

#include "IsoComponent.h"
#include "IsoItemCode.h"

namespace IsoAlgo
{
    /**
     * @brief A single PCF can contain the data for a number of pipelines,
     *        but generally, the piping design system extracts piping data
     *        for single pipeline only. It should be possible to define the
     *        the point where the isometric drawing have to be splited.
     *
     *        A single PCF can contain the data for a number of pipelines,
     *        but generally, the Piping Design System extracts piping data
     *        for a single pipeline only, and the IsoAlgo system will produce
     *        isometrics for one pipeline at a time.
     */
    class IsoPipeline
    {
    public:
        //! default constructor.
        IsoPipeline(void);

        //! default destrcutor.
        ~IsoPipeline(void);

        /**
         * @brief add attribute for the pipeline.
         * @param theKey the description of the attribute.
         * @param theValue the value of the attribute.
         */
        void AddAttribute(const std::string& theKey, const std::string& theValue);

        /**
         * @brief add piping component.
         * @param theComponent the component belong to the pipeline.
         */
        void AddComponent(IsoComponent* theComponent);
        /**
         * @brief get piping component count.
         * @return the component count.
         */
        int GetComponentCount(void) const;
        /**
         * @brief get the component at given index.
         * @param theIndex the index.
         */
        const IsoComponent* GetComponent(int theIndex) const;

        /**
         * @brief add the item code data of the pipeline.
         * @param theCode the item code.
         */
        void AddItemCode(IsoItemCode* theCode);

    private:
        //! pipeline attributes.
        std::map<std::string, std::string> myAttributes;

        //! pipeline components.
        std::vector<IsoComponent*> myComponents;

        //! pipeline item codes for the component.
        std::map<std::string, IsoItemCode*> myItemCodes;
    };
}

#endif // _ISOPIPELINE_H_
