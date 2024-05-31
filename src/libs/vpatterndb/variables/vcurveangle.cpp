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
 **  @file   vcurveangle.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   1 6, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Seamly2D project
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

#include "vcurveangle.h"

#include <QLatin1String>
#include <QMessageLogger>

#include "../vmisc/def.h"
#include "../ifc/ifcdef.h"
#include "../vgeometry/vabstractcurve.h"
#include "../vgeometry/vspline.h"
#include "vcurvevariable.h"

/**
 * @brief Default constructor for VCurveAngle.
 * 
 * Initializes a VCurveAngle object by calling the base class constructor and setting the variable type to CurveAngle.
 */
VCurveAngle::VCurveAngle()
    :VCurveVariable()
{
    SetType(VarType::CurveAngle);
}

/**
 * @brief Constructor for VCurveAngle with curve information.
 * 
 * Initializes a VCurveAngle object by setting its type to CurveAngle, asserting the curve is not null,
 * and setting the value and name based on the specified CurveAngle (StartAngle or EndAngle).
 * 
 * @param id The unique identifier for the VCurveAngle.
 * @param parentId The parent identifier for the VCurveAngle.
 * @param curve A pointer to the VAbstractCurve object.
 * @param angle The angle type (StartAngle or EndAngle).
 */
VCurveAngle::VCurveAngle(const quint32 &id, const quint32 &parentId, const VAbstractCurve *curve, CurveAngle angle)
    :VCurveVariable(id, parentId)
{
    SetType(VarType::CurveAngle);
    SCASSERT(curve != nullptr)
    if (angle == CurveAngle::StartAngle)
    {
        SetValue(curve->GetStartAngle());
        SetName(angle1_V + curve->name());
    }
    else
    {
        SetValue(curve->GetEndAngle());
        SetName(angle2_V + curve->name());
    }
}

/**
 * @brief Constructor for VCurveAngle with spline information.
 * 
 * Initializes a VCurveAngle object by setting its type to CurveAngle and setting the value and name based on 
 * the specified CurveAngle (StartAngle or EndAngle) for a given segment of a VSpline.
 * 
 * @param id The unique identifier for the VCurveAngle.
 * @param parentId The parent identifier for the VCurveAngle.
 * @param baseCurveName The base name of the curve.
 * @param spl A reference to the VSpline object.
 * @param angle The angle type (StartAngle or EndAngle).
 * @param segment The segment number of the spline.
 */
VCurveAngle::VCurveAngle(const quint32 &id, const quint32 &parentId, const QString &baseCurveName, const VSpline &spl,
                         CurveAngle angle, qint32 segment)
    :VCurveVariable(id, parentId)
{
    SetType(VarType::CurveAngle);
    if (angle == CurveAngle::StartAngle)
    {
        SetValue(spl.GetStartAngle());
        SetName(angle1_V + baseCurveName + QLatin1String("_") + seg_ + QString().setNum(segment));
    }
    else
    {
        SetValue(spl.GetEndAngle());
        SetName(angle2_V + baseCurveName + QLatin1String("_") + seg_ + QString().setNum(segment));
    }
}

/**
 * @brief Copy constructor for VCurveAngle.
 * 
 * Initializes a new instance of VCurveAngle by copying the data from an existing VCurveAngle object.
 * 
 * @param var The VCurveAngle object to copy.
 */
VCurveAngle::VCurveAngle(const VCurveAngle &var)
    :VCurveVariable(var)
{}

/**
 * @brief Assignment operator for VCurveAngle.
 * 
 * Assigns the values from another VCurveAngle object to this instance.
 * 
 * @param var The VCurveAngle object to assign from.
 * @return A reference to this VCurveAngle object.
 */
VCurveAngle &VCurveAngle::operator=(const VCurveAngle &var)
{
    if ( &var == this )
    {
        return *this;
    }
    VCurveVariable::operator=(var);
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
VCurveAngle::~VCurveAngle()
{}
