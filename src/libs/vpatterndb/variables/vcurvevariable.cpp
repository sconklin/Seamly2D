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

#include "vcurvevariable.h"

#include "../vmisc/def.h"
#include "../ifc/ifcdef.h"
#include "vinternalvariable.h"
#include "vcurvevariable_p.h"

/**
 * @brief Move assignment operator for VCurveVariable.
 *
 * This operator allows for the efficient transfer of resources from one VCurveVariable object to another
 * using move semantics. It swaps the contents of the current object with the given object.
 *
 * @param var The VCurveVariable object to be moved.
 * @return A reference to the current VCurveVariable object after the move.
 *
 * @note This operator is only available if the compiler supports rvalue references.
 */
#ifdef Q_COMPILER_RVALUE_REFS
VCurveVariable &VCurveVariable::operator=(VCurveVariable &&var) Q_DECL_NOTHROW
{ Swap(var); return *this; }
#endif

/**
 * @brief Swap the contents of two VCurveVariable objects.
 *
 * This function exchanges the contents of the current VCurveVariable object with another VCurveVariable object.
 * It is used to implement efficient assignment and move operations.
 *
 * @param var The VCurveVariable object to swap with.
 *
 * @note This function is declared noexcept, indicating that it does not throw exceptions.
 */
void VCurveVariable::Swap(VCurveVariable &var) Q_DECL_NOTHROW
{ VInternalVariable::Swap(var); std::swap(d, var.d); }

/**
 * @brief Default constructor for the VCurveVariable class.
 *
 * This constructor initializes a new instance of the VCurveVariable class, setting its type to VarType::Unknown.
 * It also initializes the internal data pointer to a new instance of VCurveVariableData.
 */
VCurveVariable::VCurveVariable()
    :VInternalVariable(), d(new VCurveVariableData)
{
    SetType(VarType::Unknown);
}

/**
 * @brief Parameterized constructor for the VCurveVariable class.
 *
 * This constructor initializes a new instance of the VCurveVariable class with specified identifiers for the curve and its parent.
 * It sets the type of the variable to VarType::Unknown and initializes the internal data pointer with the given IDs.
 *
 * @param id The unique identifier for the curve.
 * @param parentId The unique identifier for the parent of the curve.
 */
VCurveVariable::VCurveVariable(const quint32 &id, const quint32 &parentId)
    :VInternalVariable(), d(new VCurveVariableData(id, parentId))
{
    SetType(VarType::Unknown);
}

/**
 * @brief Copy constructor for the VCurveVariable class.
 *
 * This constructor creates a new instance of the VCurveVariable class by copying the data from another VCurveVariable instance.
 * It initializes the base VInternalVariable with the given variable and copies the shared data pointer.
 *
 * @param var The VCurveVariable instance to copy.
 */
VCurveVariable::VCurveVariable(const VCurveVariable &var)
    :VInternalVariable(var), d(var.d)
{}

/**
 * @brief Assignment operator for the VCurveVariable class.
 *
 * This operator assigns the values from one VCurveVariable instance to another.
 * It checks for self-assignment, copies the base VInternalVariable properties,
 * and updates the shared data pointer.
 *
 * @param var The VCurveVariable instance to copy from.
 * @return A reference to the updated VCurveVariable instance.
 */
VCurveVariable &VCurveVariable::operator=(const VCurveVariable &var)
{
    if ( &var == this )
    {
        return *this;
    }
    VInternalVariable::operator=(var);
    d = var.d;
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
VCurveVariable::~VCurveVariable()
{}

/**
 * @brief Filters VCurveVariable instances by ID.
 *
 * This method checks if the given ID matches the instance's ID or its parent ID.
 * If the instance's ID is NULL_ID, it returns false. If the instance has a valid
 * parent ID, it compares both the instance's ID and the parent ID with the given ID.
 * If the parent ID is not set, it only compares the instance's ID with the given ID.
 *
 * @param id The ID to filter by.
 * @return True if the given ID matches the instance's ID or parent ID; otherwise, false.
 */
bool VCurveVariable::Filter(quint32 id)
{
    if (id == NULL_ID)
    {
        return false;
    }

    if (d->parentId != NULL_ID)//Do not check if value zero
    {// Not all curves have parents. Only those who was created after cutting the parent curve.
        return d->id == id || d->parentId == id;
    }
    else
    {
        return d->id == id;
    }
}

/**
 * @brief Retrieves the ID of the VCurveVariable instance.
 *
 * This method returns the unique identifier of the VCurveVariable instance.
 *
 * @return The ID of the VCurveVariable.
 */
// cppcheck-suppress unusedFunction
quint32 VCurveVariable::GetId() const
{
    return d->id;
}

/**
 * @brief Sets the ID of the VCurveVariable instance.
 *
 * This method assigns a unique identifier to the VCurveVariable instance.
 *
 * @param id The unique identifier to be assigned.
 */
void VCurveVariable::SetId(const quint32 &id)
{
    d->id = id;
}

/**
 * @brief Retrieves the parent ID of the VCurveVariable instance.
 *
 * This method returns the unique identifier of the parent VCurveVariable instance.
 *
 * @return The unique identifier of the parent VCurveVariable instance.
 */
// cppcheck-suppress unusedFunction
quint32 VCurveVariable::GetParentId() const
{
    return d->parentId;
}

/**
 * @brief Sets the parent ID of the VCurveVariable instance.
 *
 * This method assigns a unique identifier to the parent VCurveVariable instance.
 *
 * @param value The unique identifier to be assigned to the parent VCurveVariable instance.
 */
void VCurveVariable::SetParentId(const quint32 &value)
{
    d->parentId = value;
}
