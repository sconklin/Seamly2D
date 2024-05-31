//  @file   custom_variable.cpp
//  @author Douglas S Caskey
//  @date   2  Apr, 2024
//
//  @copyright
//  Copyright (C) 2017 - 2024 Seamly, LLC
//  https://github.com/fashionfreedom/seamly2d
//
//  @brief
//  Seamly2D is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Seamly2D is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Seamly2D. If not, see <http://www.gnu.org/licenses/>.

/************************************************************************
 **
 **  @file   vincrementtablerow.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   November 15, 2013
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

#include "custom_variable.h"
#include "custom_variable_p.h"

#include "../vmisc/def.h"
#include "vvariable.h"

#ifdef Q_COMPILER_RVALUE_REFS
CustomVariable &CustomVariable::operator=(CustomVariable &&variable) Q_DECL_NOTHROW { Swap(variable); return *this; }
#endif

/**
 * @brief Swaps the contents of this CustomVariable with another.
 * 
 * This function exchanges the contents of this CustomVariable with another instance provided as a parameter. 
 * The swap operation is noexcept, ensuring it doesn't throw exceptions.
 * 
 * @param variable Reference to another CustomVariable instance to swap with.
 * 
 * @details
 * The function performs the following steps:
 * - Calls the Swap method of the base class VVariable to swap base class members.
 * - Uses std::swap to exchange the custom data member `d` between the two CustomVariable instances.
 */
void CustomVariable::Swap(CustomVariable &variable) Q_DECL_NOTHROW
{ VVariable::Swap(variable); std::swap(d, variable.d); }

/**
 * @brief Constructs an empty CustomVariable.
 * 
 * This constructor initializes a new instance of CustomVariable with default values.
 * 
 * @details
 * The constructor performs the following steps:
 * - Calls the default constructor of the base class VVariable to initialize base class members.
 * - Initializes the custom data member `d` with a new instance of CustomVariableData.
 * - Sets the type of the variable to `VarType::Variable` using the SetType method.
 */
CustomVariable::CustomVariable()
    : VVariable()
    , d(new CustomVariableData)
{
    SetType(VarType::Variable);
}

/**
 * @brief Constructs a CustomVariable with specified parameters.
 * 
 * This constructor initializes a new instance of CustomVariable using the provided data, name, index, base value, formula,
 * status, and description.
 * 
 * @param data Pointer to a VContainer object containing related data.
 * @param name The name of the custom variable.
 * @param index The index associated with the custom variable.
 * @param base The base value for the variable.
 * @param formula The formula associated with the variable.
 * @param ok Boolean indicating the status of the variable (e.g., valid or not).
 * @param description A brief description of the variable.
 * 
 * @details
 * The constructor performs the following steps:
 * - Calls the parameterized constructor of the base class VVariable to initialize the name and description.
 * - Initializes the custom data member `d` with a new instance of CustomVariableData, passing the data, index, formula, and status.
 * - Sets the type of the variable to `VarType::Variable` using the SetType method.
 * - Sets the value of the variable to the provided base value using VInternalVariable::SetValue.
 */
CustomVariable::CustomVariable(VContainer *data, const QString &name, quint32 index, qreal base, const QString &formula,
                       bool ok, const QString &description)
    : VVariable(name, description)
    , d(new CustomVariableData(data, index, formula, ok))
{
    SetType(VarType::Variable);
    VInternalVariable::SetValue(base);
}

/**
 * @brief Copy constructor for CustomVariable.
 * 
 * This constructor creates a new instance of CustomVariable by copying an existing CustomVariable instance.
 * 
 * @param variable The CustomVariable instance to be copied.
 * 
 * @details
 * The constructor performs the following steps:
 * - Calls the copy constructor of the base class VVariable to copy the name and description.
 * - Copies the custom data member `d` from the provided variable.
 */
CustomVariable::CustomVariable(const CustomVariable &variable)
    : VVariable(variable)
    , d(variable.d)
{}

/**
 * @brief Assignment operator for CustomVariable.
 * 
 * This operator allows assigning the values of one CustomVariable instance to another.
 * 
 * @param variable The CustomVariable instance to be assigned.
 * @return A reference to the assigned CustomVariable instance.
 * 
 * @details
 * The operator performs the following steps:
 * - Checks for self-assignment and returns the current instance if true.
 * - Calls the assignment operator of the base class VVariable to copy base class members.
 * - Copies the custom data member `d` from the provided variable.
 */
CustomVariable &CustomVariable::operator=(const CustomVariable &variable)
{
    if ( &variable == this )
    {
        return *this;
    }
    VVariable::operator=(variable);
    d = variable.d;
    return *this;
}

/**
 * @brief Destructor for CustomVariable.
 * 
 * This destructor is responsible for cleaning up resources used by the CustomVariable instance.
 * 
 */
CustomVariable::~CustomVariable()
{}

/**
 * @brief Retrieves the index of the CustomVariable.
 * 
 * This function returns the index value associated with the CustomVariable.
 * 
 * @return quint32 The index of the CustomVariable.
 */
quint32 CustomVariable::getIndex() const
{
    return d->index;
}

/**
 * @brief Retrieves the formula of the CustomVariable.
 * 
 * This function returns the formula string associated with the CustomVariable.
 * 
 * @return QString The formula of the CustomVariable.
 */
QString CustomVariable::GetFormula() const
{
    return d->formula;
}

/**
 * @brief Checks if the formula of the CustomVariable is valid.
 * 
 * This function returns a boolean indicating whether the formula associated with the CustomVariable is valid.
 * 
 * @return bool True if the formula is valid, false otherwise.
 */
bool CustomVariable::IsFormulaOk() const
{
    return d->formulaOk;
}

/**
 * @brief Retrieves the data associated with the CustomVariable.
 * 
 * This function returns a pointer to the data in the VContainer object.
 * 
 * @return VContainer* Pointer to the data container.
 */
VContainer *CustomVariable::GetData()
{
    return &d->data;
}
