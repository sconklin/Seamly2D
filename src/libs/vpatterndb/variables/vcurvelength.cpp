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
 **  @file   vcurvelength.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   15 8, 2014
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Seamly2D project
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

#include "vcurvelength.h"

#include <QLatin1String>
#include <QMessageLogger>

#include "../ifc/ifcdef.h"
#include "../vgeometry/vabstractcurve.h"
#include "../vgeometry/vspline.h"
#include "vcurvevariable.h"

/**
 * @brief Default constructor for the VCurveLength class.
 * 
 * This constructor initializes a VCurveLength object by calling the default constructor of the base class VCurveVariable. 
 * It also sets the type of the variable to VarType::CurveLength.
 */
VCurveLength::VCurveLength()
    :VCurveVariable()
{
    SetType(VarType::CurveLength);
}

/**
 * @brief Constructs a VCurveLength object with specified parameters.
 * 
 * This constructor initializes a VCurveLength object with the given id, parentId, and VAbstractCurve pointer. 
 * It sets the type of the variable to VarType::CurveLength, assigns the curve's name to the variable, 
 * and converts the curve's length from pixels to the specified unit.
 * 
 * @param id The unique identifier for the VCurveLength object.
 * @param parentId The identifier of the parent object.
 * @param curve Pointer to the VAbstractCurve object whose length is to be represented.
 * @param patternUnit The unit to which the curve's length will be converted.
 */
VCurveLength::VCurveLength(const quint32 &id, const quint32 &parentId, const VAbstractCurve *curve, Unit patternUnit)
    :VCurveVariable(id, parentId)
{
    SetType(VarType::CurveLength);
    SCASSERT(curve != nullptr)
    SetName(curve->name());
    SetValue(FromPixel(curve->GetLength(), patternUnit));
}

/**
 * @brief Constructs a VCurveLength object with specified parameters.
 * 
 * This constructor initializes a VCurveLength object with the given id, parentId, baseCurveName, VSpline object, 
 * patternUnit, and segment. It sets the type of the variable to VarType::CurveLength, creates a name by combining 
 * the baseCurveName and segment, and converts the spline's length from pixels to the specified unit.
 * 
 * @param id The unique identifier for the VCurveLength object.
 * @param parentId The identifier of the parent object.
 * @param baseCurveName The base name of the curve.
 * @param spl The VSpline object whose length is to be represented.
 * @param patternUnit The unit to which the spline's length will be converted.
 * @param segment The segment number used in creating the name.
 */
VCurveLength::VCurveLength(const quint32 &id, const quint32 &parentId, const QString &baseCurveName, const VSpline &spl,
                           Unit patternUnit, qint32 segment)
    :VCurveVariable(id, parentId)
{
    SCASSERT(not baseCurveName.isEmpty())

    SetType(VarType::CurveLength);
    SetName(baseCurveName + QLatin1String("_") + seg_ + QString().setNum(segment));
    SetValue(FromPixel(spl.GetLength(), patternUnit));
}

/**
 * @brief Copy constructor for VCurveLength.
 * 
 * This constructor creates a new VCurveLength object by copying the data from an existing VCurveLength object.
 * 
 * @param var The VCurveLength object to be copied.
 */
VCurveLength::VCurveLength(const VCurveLength &var)
    :VCurveVariable(var)
{}

/**
 * @brief Assignment operator for VCurveLength.
 * 
 * This operator assigns the values from one VCurveLength object to another. It checks for self-assignment and 
 * then copies the data from the source object.
 * 
 * @param var The VCurveLength object to be assigned.
 * @return A reference to the assigned VCurveLength object.
 */
VCurveLength &VCurveLength::operator=(const VCurveLength &var)
{
    if ( &var == this )
    {
        return *this;
    }
    VCurveVariable::operator=(var);
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
VCurveLength::~VCurveLength()
{}
