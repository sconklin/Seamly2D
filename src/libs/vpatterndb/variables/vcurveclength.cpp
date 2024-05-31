/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                             *
 *                                                                         *
 ***************************************************************************
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   24 9, 2016
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2016 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "vcurveclength.h"

#include <QLatin1String>
#include <QMessageLogger>

#include "../vmisc/def.h"
#include "../ifc/ifcdef.h"
#include "../vgeometry/vabstractcurve.h"
#include "../vgeometry/vspline.h"
#include "vcurvevariable.h"

/**
 * @brief Default constructor for VCurveCLength.
 * 
 * Initializes a VCurveCLength object by calling the base class constructor and setting the type to CurveCLength.
 */
VCurveCLength::VCurveCLength()
    : VCurveVariable()
{
    SetType(VarType::CurveCLength);
}

/**
 * @brief Constructor for VCurveCLength with specified parameters.
 * 
 * Initializes a VCurveCLength object using the provided parameters, including an ID, parent ID, a pointer to 
 * a VAbstractBezier curve, a CurveCLength type, and a unit for pattern measurements. 
 * 
 * @param id The unique identifier for the curve length.
 * @param parentId The identifier of the parent object.
 * @param curve Pointer to the VAbstractBezier curve object.
 * @param cType The type of curve length (C1 or C2).
 * @param patternUnit The unit of measurement for the pattern.
 * 
 * @details
 * This constructor sets the type to CurveCLength, asserts that the curve pointer is not null, and initializes the 
 * value and name based on the provided curve length type (C1 or C2). The length is converted from pixels to the 
 * specified pattern unit.
 */
VCurveCLength::VCurveCLength(const quint32 &id, const quint32 &parentId, const VAbstractBezier *curve,
                             CurveCLength cType, Unit patternUnit)
    : VCurveVariable(id, parentId)
{
    SetType(VarType::CurveCLength);
    SCASSERT(curve != nullptr)
    if (cType == CurveCLength::C1)
    {
        SetValue(FromPixel(curve->GetC1Length(), patternUnit));
        SetName(c1Length_V + curve->name());
    }
    else
    {
        SetValue(FromPixel(curve->GetC2Length(), patternUnit));
        SetName(c2Length_V + curve->name());
    }
}

/**
 * @brief Constructor for VCurveCLength with specified parameters for a spline.
 * 
 * Initializes a VCurveCLength object using the provided parameters, including an ID, parent ID, base curve name, 
 * a VSpline object, a CurveCLength type, a unit for pattern measurements, and a segment number.
 * 
 * @param id The unique identifier for the curve length.
 * @param parentId The identifier of the parent object.
 * @param baseCurveName The name of the base curve.
 * @param spl The VSpline object.
 * @param cType The type of curve length (C1 or C2).
 * @param patternUnit The unit of measurement for the pattern.
 * @param segment The segment number of the curve.
 * 
 * @details
 * This constructor sets the type to CurveCLength and initializes the value and name based on the provided curve length 
 * type (C1 or C2) for the spline. The length is converted from pixels to the specified pattern unit and the name 
 * includes the segment number.
 */
VCurveCLength::VCurveCLength(const quint32 &id, const quint32 &parentId, const QString &baseCurveName,
                             const VSpline &spl, CurveCLength cType, Unit patternUnit, qint32 segment)
    : VCurveVariable(id, parentId)
{
    SetType(VarType::CurveCLength);
    if (cType == CurveCLength::C1)
    {
        SetValue(FromPixel(spl.GetC1Length(), patternUnit));
        SetName(c1Length_V + baseCurveName + QLatin1String("_") + seg_ + QString().setNum(segment));
    }
    else
    {
        SetValue(FromPixel(spl.GetC2Length(), patternUnit));
        SetName(c2Length_V + baseCurveName + QLatin1String("_") + seg_ + QString().setNum(segment));
    }
}

/**
 * @brief Copy constructor for VCurveCLength.
 * 
 * Initializes a new instance of VCurveCLength by copying the data from an existing VCurveCLength object.
 * 
 * @param var The VCurveCLength object to copy from.
 * 
 * @details
 * This constructor utilizes the copy constructor of the base class VCurveVariable to perform the copy operation.
 */
VCurveCLength::VCurveCLength(const VCurveCLength &var)
    : VCurveVariable(var)
{
}

/**
 * @brief Assignment operator for VCurveCLength.
 * 
 * Assigns the values from an existing VCurveCLength object to this object.
 * 
 * @param var The VCurveCLength object to assign from.
 * @return A reference to this VCurveCLength object.
 * 
 * @details
 * This operator checks for self-assignment and utilizes the assignment operator of the base class VCurveVariable to perform the assignment.
 */
VCurveCLength &VCurveCLength::operator=(const VCurveCLength &var)
{
    if ( &var == this )
    {
        return *this;
    }
    VCurveVariable::operator=(var);
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
VCurveCLength::~VCurveCLength()
{
}

