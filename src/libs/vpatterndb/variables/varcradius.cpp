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
 **  @file   varcradius.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   30 5, 2015
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

#include "varcradius.h"

#include <QMessageLogger>
#include <QString>

#include "../ifc/ifcdef.h"
#include "../vgeometry/varc.h"
#include "../vgeometry/vellipticalarc.h"

/**
 * @brief Default constructor for the VArcRadius class.
 * 
 * This constructor calls the default constructor of the base class VCurveVariable.
 * It also sets the type of the variable to VarType::ArcRadius.
 */
VArcRadius::VArcRadius()
    :VCurveVariable()
{
    SetType(VarType::ArcRadius);
}

/**
 * @brief Constructor for the VArcRadius class.
 * 
 * This constructor initializes a VArcRadius object using the given arc information and pattern unit.
 * 
 * @param id The unique identifier for the arc radius.
 * @param parentId The unique identifier for the parent.
 * @param arc Pointer to the VArc object used to initialize the radius.
 * @param patternUnit The unit of measurement for the pattern.
 * 
 * @details
 * - Asserts that the arc pointer is not null.
 * - Sets the type of the variable to VarType::ArcRadius.
 * - Sets the name of the variable to include the arc's name.
 * - Converts the radius from pixels to the specified pattern unit and sets the value.
 */
VArcRadius::VArcRadius(const quint32 &id, const quint32 &parentId, const VArc *arc, Unit patternUnit)
    :VCurveVariable(id, parentId)
{
    SCASSERT(arc != nullptr)

    SetType(VarType::ArcRadius);
    SetName(radius_V + QString("%1").arg(arc->name()));
    SetValue(FromPixel(arc->GetRadius(), patternUnit));
}

/**
 * @brief Constructor for the VArcRadius class for elliptical arcs.
 * 
 * This constructor initializes a VArcRadius object using the given elliptical arc information, 
 * the radius number, and the pattern unit.
 * 
 * @param id The unique identifier for the arc radius.
 * @param parentId The unique identifier for the parent.
 * @param elArc Pointer to the VEllipticalArc object used to initialize the radius.
 * @param numberRadius The number of the radius (1 or 2) to be used.
 * @param patternUnit The unit of measurement for the pattern.
 * 
 * @details
 * - Asserts that the elArc pointer is not null.
 * - Sets the type of the variable to VarType::ArcRadius.
 * - Sets the name of the variable to include the radius number and the elliptical arc's name.
 * - Converts the specified radius (Radius1 or Radius2) from pixels to the specified pattern unit and sets the value.
 */
VArcRadius::VArcRadius(const quint32 &id, const quint32 &parentId, const VEllipticalArc *elArc, const int numberRadius,
                       Unit patternUnit)
    : VCurveVariable(id, parentId)
{
    SCASSERT(elArc != nullptr)

    SetType(VarType::ArcRadius);
    SetName(radius_V + QString("%1%2").arg(numberRadius).arg(elArc->name()));
    if (numberRadius == 1)
    {
        SetValue(FromPixel(elArc->GetRadius1(), patternUnit));
    }
    else
    {
        SetValue(FromPixel(elArc->GetRadius2(), patternUnit));
    }
}

/**
 * @brief Copy constructor for the VArcRadius class.
 * 
 * This constructor initializes a new VArcRadius object as a copy of an existing VArcRadius object.
 * 
 * @param var The VArcRadius object to be copied.
 * 
 * @details
 * - Calls the copy constructor of the base class VCurveVariable.
 */
VArcRadius::VArcRadius(const VArcRadius &var)
    :VCurveVariable(var)
{}

/**
 * @brief Assignment operator for the VArcRadius class.
 * 
 * This operator assigns the values from one VArcRadius object to another.
 * 
 * @param var The VArcRadius object to be assigned.
 * @return A reference to the assigned VArcRadius object.
 * 
 * @details
 * - Checks for self-assignment and returns *this if true.
 * - Calls the assignment operator of the base class VCurveVariable.
 */
VArcRadius &VArcRadius::operator=(const VArcRadius &var)
{
    if ( &var == this )
    {
        return *this;
    }
    VCurveVariable::operator=(var);
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
VArcRadius::~VArcRadius()
{}
