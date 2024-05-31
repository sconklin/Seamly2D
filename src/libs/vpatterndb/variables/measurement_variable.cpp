/******************************************************************************
 *   @file   measurement_variable.cpp
 **  @author Douglas S Caskey
 **  @date   16 Jul, 2023
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Seamly2D project, a pattern making
 **  program to create and model patterns of clothing.
 **  Copyright (C) 2017-2023 Seamly2D project
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

/************************************************************************
 **
 **  @file   vstandardtablecell.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   November 15, 2013
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2015 Valentina project
 **  <https://bitbucket.org/dismine/valentina> All Rights Reserved.
 **
 **  Valentina is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Valentina is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Valentina.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "measurement_variable.h"

#include <QMap>
#include <QMessageLogger>
#include <QtDebug>

#include "../ifc/ifcdef.h"
#include "vvariable.h"
#include "measurement_variable_p.h"

#ifdef Q_COMPILER_RVALUE_REFS
MeasurementVariable &MeasurementVariable::operator=(MeasurementVariable &&m) Q_DECL_NOTHROW
{ Swap(m); return *this; }
#endif

/**
 * @brief Swap the contents of this MeasurementVariable with another.
 * 
 * This method swaps the contents of the current MeasurementVariable instance with another instance passed as an argument.
 * It ensures that the internal data pointers and attributes are exchanged between the two instances.
 * 
 * @param m A reference to another MeasurementVariable instance to swap contents with.
 * 
 * @details
 * - This method calls the Swap method of the base class VVariable to swap common attributes.
 * - It then uses std::swap to exchange the shared data pointers (d) of the two instances.
 * - This operation is marked as noexcept (Q_DECL_NOTHROW) to indicate that it does not throw exceptions.
 */
void MeasurementVariable::Swap(MeasurementVariable &m) Q_DECL_NOTHROW
{ VVariable::Swap(m); std::swap(d, m.d); }

/**
 * @brief Constructor for MeasurementVariable with specified parameters.
 * 
 * This constructor initializes a MeasurementVariable instance with the provided parameters.
 * 
 * @param index The unique identifier for the measurement variable.
 * @param name The name of the measurement variable.
 * @param baseSize The base size value for the measurement variable.
 * @param baseHeight The base height value for the measurement variable.
 * @param base The base value for the measurement variable.
 * @param ksize The size coefficient for the measurement variable.
 * @param kheight The height coefficient for the measurement variable.
 * @param gui_text The GUI text associated with the measurement variable.
 * @param description A description of the measurement variable.
 * @param tagName A tag name associated with the measurement variable.
 * 
 * @details
 * - The constructor initializes the base class VVariable with the provided name and description.
 * - It allocates a new MeasurementVariableData object with the provided parameters and assigns it to the shared data pointer (d).
 * - The measurement variable type is set to VarType::Measurement.
 * - The base value of the internal variable is set using the VInternalVariable::SetValue method.
 */
MeasurementVariable::MeasurementVariable(quint32 index, const QString &name, qreal baseSize, qreal baseHeight, const qreal &base,
                           const qreal &ksize, const qreal &kheight, const QString &gui_text,
                           const QString &description, const QString &tagName)
    : VVariable(name, description)
    , d(new MeasurementVariableData(index, gui_text, tagName, baseSize, baseHeight, base, ksize, kheight))
{
    SetType(VarType::Measurement);
    VInternalVariable::SetValue(d->base);
}

/**
 * @brief Constructor for MeasurementVariable with data container and specified parameters.
 * 
 * This constructor initializes a MeasurementVariable instance using a data container and other provided parameters.
 * 
 * @param data A pointer to the data container (VContainer) associated with the measurement variable.
 * @param index The unique identifier for the measurement variable.
 * @param name The name of the measurement variable.
 * @param base The base value for the measurement variable.
 * @param formula The formula associated with the measurement variable.
 * @param ok A boolean indicating if the formula is valid.
 * @param gui_text The GUI text associated with the measurement variable.
 * @param description A description of the measurement variable.
 * @param tagName A tag name associated with the measurement variable.
 * 
 * @details
 * - The constructor initializes the base class VVariable with the provided name and description.
 * - It allocates a new MeasurementVariableData object with the provided parameters and assigns it to the shared data pointer (d).
 * - The measurement variable type is set to VarType::Measurement.
 * - The base value of the internal variable is set using the VInternalVariable::SetValue method.
 */
MeasurementVariable::MeasurementVariable(VContainer *data, quint32 index, const QString &name, const qreal &base,
                           const QString &formula, bool ok, const QString &gui_text, const QString &description,
                           const QString &tagName)
    : VVariable(name, description)
    , d(new MeasurementVariableData(data, index, formula, ok, gui_text, tagName, base))
{
    SetType(VarType::Measurement);
    VInternalVariable::SetValue(base);
}

/**
 * @brief Copy constructor for MeasurementVariable.
 * 
 * This constructor initializes a new MeasurementVariable instance as a copy of an existing MeasurementVariable instance.
 * 
 * @param m The MeasurementVariable instance to copy from.
 * 
 * @details
 * - The constructor initializes the base class VVariable with the provided MeasurementVariable instance (m).
 * - It assigns the shared data pointer (d) from the provided MeasurementVariable instance to the new instance.
 * - This ensures that the new MeasurementVariable shares the same data as the original instance.
 */
MeasurementVariable::MeasurementVariable(const MeasurementVariable &m)
    : VVariable(m)
    , d(m.d)
{}

/**
 * @brief Assignment operator for MeasurementVariable.
 * 
 * This operator assigns the values from an existing MeasurementVariable instance to another MeasurementVariable instance.
 * 
 * @param m The MeasurementVariable instance to assign from.
 * @return A reference to the assigned MeasurementVariable instance.
 * 
 * @details
 * - The operator first checks for self-assignment and returns the current instance if the addresses are the same.
 * - It calls the base class assignment operator to assign the base class attributes.
 * - It assigns the shared data pointer (d) from the provided MeasurementVariable instance to the current instance.
 * - This ensures that the current MeasurementVariable shares the same data as the provided instance.
 */
MeasurementVariable &MeasurementVariable::operator=(const MeasurementVariable &m)
{
    if ( &m == this )
    {
        return *this;
    }
    VVariable::operator=(m);
    d = m.d;
    return *this;
}

/**
 * @brief Destructor for MeasurementVariable.
 * 
 * This destructor is responsible for cleaning up resources used by an instance of MeasurementVariable.
 * 
 */
MeasurementVariable::~MeasurementVariable()
{}

/**
 * @brief Generates a list of heights based on specified criteria.
 * 
 * This method creates a QStringList of heights filtered by the provided QMap of GHeights and their corresponding boolean values. 
 * The list is formatted according to the specified pattern unit.
 * 
 * @param heights A QMap where keys are GHeights enumerations and values are booleans indicating whether to include the corresponding height.
 * @param patternUnit The unit used for formatting the heights in the list.
 * @return A QStringList containing the heights that meet the specified criteria.
 * 
 * @details
 * - The method iterates through the provided QMap of heights.
 * - For each height that is included (i.e., has a true value and is not GHeights::ALL), it calls ListValue to add the height to the list.
 * - If no heights are added to the list (i.e., the list remains empty), the method returns a list of all possible heights using WholeListHeights.
 */
QStringList MeasurementVariable::ListHeights(QMap<GHeights, bool> heights, Unit patternUnit)
{
    QStringList list;

    QMap<GHeights, bool>::const_iterator i = heights.constBegin();
    while (i != heights.constEnd())
    {
        if (i.value() && i.key() != GHeights::ALL)
        {
            ListValue(list, static_cast<int>(i.key()), patternUnit);
        }
        ++i;
    }

    if (list.isEmpty())
    {
        list = MeasurementVariable::WholeListHeights(patternUnit);
    }
    return list;
}

/**
 * @brief Generates a list of sizes based on specified criteria.
 * 
 * This method creates a QStringList of sizes filtered by the provided QMap of GSizes and their corresponding boolean values. 
 * The list is formatted according to the specified pattern unit.
 * 
 * @param sizes A QMap where keys are GSizes enumerations and values are booleans indicating whether to include the corresponding size.
 * @param patternUnit The unit used for formatting the sizes in the list.
 * @return A QStringList containing the sizes that meet the specified criteria.
 * 
 * @details
 * - The method iterates through the provided QMap of sizes.
 * - For each size that is included (i.e., has a true value and is not GSizes::ALL), it calls ListValue to add the size to the list.
 * - If no sizes are added to the list (i.e., the list remains empty), the method returns a list of all possible sizes using WholeListSizes.
 */
QStringList MeasurementVariable::ListSizes(QMap<GSizes, bool> sizes, Unit patternUnit)
{
    QStringList list;

    QMap<GSizes, bool>::const_iterator i = sizes.constBegin();
    while (i != sizes.constEnd())
    {
        if (i.value() && i.key() != GSizes::ALL)
        {
            ListValue(list, static_cast<int>(i.key()), patternUnit);
        }
        ++i;
    }

    if (list.isEmpty())
    {
        list = MeasurementVariable::WholeListSizes(patternUnit);
    }
    return list;
}

/**
 * @brief Generates a complete list of heights.
 * 
 * This method creates a QStringList containing all possible height values formatted according to the specified pattern unit.
 * 
 * @param patternUnit The unit used for formatting the heights in the list.
 * @return A QStringList containing all height values from GHeights::H50 to GHeights::H200.
 * 
 * @details
 * - The method iterates through height values from GHeights::H50 to GHeights::H200.
 * - For each height, it calls ListValue to add the height value to the list in the specified unit.
 * - The height values are incremented by the heightStep constant in each iteration.
 */
QStringList MeasurementVariable::WholeListHeights(Unit patternUnit)
{
    QStringList list;

    for (int i = static_cast<int>(GHeights::H50); i<= static_cast<int>(GHeights::H200); i = i+heightStep)
    {
        ListValue(list, i, patternUnit);
    }

    return list;
}

/**
 * @brief Generates a complete list of sizes.
 * 
 * This method creates a QStringList containing all possible size values formatted according to the specified pattern unit.
 * 
 * @param patternUnit The unit used for formatting the sizes in the list.
 * @return A QStringList containing all size values from GSizes::S22 to GSizes::S72.
 * 
 * @details
 * - The method iterates through size values from GSizes::S22 to GSizes::S72.
 * - For each size, it calls ListValue to add the size value to the list in the specified unit.
 * - The size values are incremented by the sizeStep constant in each iteration.
 */
QStringList MeasurementVariable::WholeListSizes(Unit patternUnit)
{
    QStringList list;

    for (int i = static_cast<int>(GSizes::S22); i<= static_cast<int>(GSizes::S72); i = i+sizeStep)
    {
       ListValue(list, i, patternUnit);
    }

    return list;
}

/**
 * @brief Checks the validity of a given gradation size.
 * 
 * This method verifies if a specified size is a valid gradation size by checking its presence in the complete list of sizes.
 * 
 * @param size The size value to be validated as a QString.
 * @return A boolean value indicating whether the specified size is valid (true) or not (false).
 * 
 * @details
 * - If the size string is not empty, the method generates a complete list of sizes using WholeListSizes with Unit::Cm.
 * - It then checks if the specified size is present in the list of valid sizes.
 * - If the size string is empty, the method returns false.
 */
bool MeasurementVariable::IsGradationSizeValid(const QString &size)
{
    if (not size.isEmpty())
    {
        const QStringList sizes = MeasurementVariable::WholeListSizes(Unit::Cm);
        return sizes.contains(size);
    }
    else
    {
        return false;
    }
}

/**
 * @brief Checks the validity of a given gradation height.
 * 
 * This method verifies if a specified height is a valid gradation height by checking its presence in the complete list of heights.
 * 
 * @param height The height value to be validated as a QString.
 * @return A boolean value indicating whether the specified height is valid (true) or not (false).
 * 
 * @details
 * - If the height string is not empty, the method generates a complete list of heights using WholeListHeights with Unit::Cm.
 * - It then checks if the specified height is present in the list of valid heights.
 * - If the height string is empty, the method returns false.
 */
bool MeasurementVariable::IsGradationHeightValid(const QString &height)
{
    if (not height.isEmpty())
    {
        const QStringList heights = MeasurementVariable::WholeListHeights(Unit::Cm);
        return heights.contains(height);
    }
    else
    {
        return false;
    }
}

/**
 * @brief Calculates the value of the measurement variable.
 * 
 * This method computes the value of the measurement variable based on its current unit, size, and height.
 * 
 * @return The calculated value as a qreal.
 * 
 * @details
 * - If the current unit, size, or height is not set, it returns the internal value of the variable.
 * - If the current unit is in inches, a warning is issued, and the method returns 0 since gradation does not support inches.
 * - The method uses size and height increments (2.0 cm and 6.0 cm, respectively) for calculation, converted to the current unit.
 * - It calculates the size and height factors (k_size and k_height) based on the difference between the current and base values.
 * - The final value is computed using the base value, size factor, and height factor, adjusted by their respective increments.
 */
qreal MeasurementVariable::CalcValue() const
{
    if (d->currentUnit == nullptr || d->currentSize == nullptr || d->currentHeight == nullptr)
    {
        return VInternalVariable::GetValue();
    }

    if (*d->currentUnit == Unit::Inch)
    {
        qWarning("Gradation doesn't support inches");
        return 0;
    }

    const qreal sizeIncrement = UnitConvertor(2.0, Unit::Cm, *d->currentUnit);
    const qreal heightIncrement = UnitConvertor(6.0, Unit::Cm, *d->currentUnit);

    // Formula for calculation gradation
    const qreal k_size    = ( *d->currentSize - d->baseSize ) / sizeIncrement;
    const qreal k_height  = ( *d->currentHeight - d->baseHeight ) / heightIncrement;
    return d->base + k_size * d->ksize + k_height * d->kheight;
}

/**
 * @brief Adds a value to a QStringList after converting it to the specified unit.
 * 
 * This method converts a given value from centimeters to the specified
 * pattern unit and appends the resulting value as a string to the provided QStringList.
 * 
 * @param list The QStringList to which the converted value will be appended.
 * @param value The value in centimeters to be converted.
 * @param patternUnit The unit to which the value will be converted.
 * 
 * @details
 * - The value is converted from centimeters to the specified pattern unit using the UnitConvertor function.
 * - The converted value is formatted as a string and appended to the provided QStringList.
 */
void MeasurementVariable::ListValue(QStringList &list, qreal value, Unit patternUnit)
{
    const qreal val = UnitConvertor(value, Unit::Cm, patternUnit);
    const QString strVal = QString("%1").arg(val);
    list.append(strVal);
}

/**
 * @brief Retrieves the GUI text associated with the measurement variable.
 * 
 * This method returns the GUI text that is stored within the measurement variable data.
 * The GUI text is used for display purposes in the user interface.
 * 
 * @return A QString containing the GUI text.
 */
QString MeasurementVariable::getGuiText() const
{
    return d->gui_text;
}

/**
 * @brief Retrieves the tag name associated with the measurement variable.
 * 
 * This method returns the tag name that is stored within the measurement variable data.
 * The tag name is used to uniquely identify the variable in the system.
 * 
 * @return A QString containing the tag name.
 */
QString MeasurementVariable::TagName() const
{
    return d->_tagName;
}

/**
 * @brief Sets the tag name for the measurement variable.
 * 
 * This method assigns a new tag name to the measurement variable.
 * The tag name is used to uniquely identify the variable in the system.
 * 
 * @param tagName The new tag name to be assigned to the measurement variable.
 */
void MeasurementVariable::setTagName(const QString &tagName)
{
    d->_tagName = tagName;
}

/**
 * @brief Retrieves the formula associated with the measurement variable.
 * 
 * This method returns the formula used for calculating the value of the measurement variable. 
 * 
 * @return The formula as a QString.
 */
QString MeasurementVariable::GetFormula() const
{
    return d->formula;
}

/**
 * @brief Checks if the measurement variable is custom.
 * 
 * This method determines if the measurement variable is custom by checking if its name 
 * starts with a specific custom measurement sign (`CustomMSign`).
 * 
 * @return `true` if the measurement variable is custom, `false` otherwise.
 */
bool MeasurementVariable::isCustom() const
{
    return GetName().indexOf(CustomMSign) == 0;
}

/**
 * @brief Gets the index of the measurement variable.
 * 
 * This method returns the unique index of the measurement variable.
 * 
 * @return The index of the measurement variable as an integer.
 */
int MeasurementVariable::Index() const
{
    return static_cast<int>(d->index);
}

/**
 * @brief Checks if the formula associated with the measurement variable is valid.
 * 
 * This method returns a boolean value indicating whether the formula
 * associated with the measurement variable is valid. A valid formula
 * means that it has been correctly parsed and can be used for calculations.
 * 
 * @return True if the formula is valid, false otherwise.
 */
bool MeasurementVariable::IsFormulaOk() const
{
    return d->formulaOk;
}

/**
 * @brief Checks if the measurement variable is not used.
 * 
 * This method determines whether the measurement variable is effectively unused
 * by checking if its base value, size coefficient, and height coefficient
 * are all approximately zero.
 * 
 * @return True if the measurement variable is not used, false otherwise.
 */
bool MeasurementVariable::isNotUsed() const
{
    return qFuzzyIsNull(d->base) && qFuzzyIsNull(d->ksize) && qFuzzyIsNull(d->kheight);
}

/**
 * @brief Retrieves the value of the measurement variable.
 * 
 * This method calculates and returns the value of the measurement variable
 * based on its current configuration, including unit, size, and height.
 * 
 * @return The calculated value of the measurement variable.
 */
qreal MeasurementVariable::GetValue() const
{
    return CalcValue();
}

/**
 * @brief Calculates and retrieves the value of the measurement variable by pointer.
 * 
 * This method calculates the value of the measurement variable based on its current configuration, 
 * including unit, size, and height. It then updates the internal value and returns a pointer to it.
 * 
 * @return Pointer to the calculated value of the measurement variable.
 */
qreal *MeasurementVariable::GetValue()
{
    VInternalVariable::SetValue(CalcValue());
    return VInternalVariable::GetValue();
}

/**
 * @brief Retrieves the data container associated with the measurement variable.
 * 
 * This method returns a pointer to the VContainer object that holds the data
 * for the measurement variable.
 * 
 * @return Pointer to the VContainer data.
 */
VContainer *MeasurementVariable::GetData()
{
    return &d->data;
}

/**
 * @brief Sets the current size for the measurement variable.
 * 
 * This method assigns a pointer to the current size value for the measurement variable.
 * 
 * @param size Pointer to the current size value.
 */
void MeasurementVariable::setSize(qreal *size)
{
    d->currentSize = size;
}

/**
 * @brief Sets the current height for the measurement variable.
 * 
 * @param height Pointer to the current height value.
 */
void MeasurementVariable::setHeight(qreal *height)
{
    d->currentHeight = height;
}

/**
 * @brief Sets the current unit for the measurement variable.
 * 
 * This method assigns a pointer to the current unit, which determines the unit of measurement (e.g., cm, inch)
 * used in the calculation of the variable's value.
 * 
 * @param unit Pointer to the current unit.
 */
void MeasurementVariable::SetUnit(const Unit *unit)
{
    d->currentUnit = unit;
}

/**
 * @brief Retrieves the base value of the measurement variable.
 * 
 * @return qreal The base value of the measurement variable.
 */
qreal MeasurementVariable::GetBase() const
{
    return d->base;
}

/**
 * @brief Sets the base value of the measurement variable.
 * 
 * This method assigns a new base value to the measurement variable.
 * 
 * @param value The new base value to be set.
 */
void MeasurementVariable::SetBase(const qreal &value)
{
    d->base = value;
}

/**
 * @brief Retrieves the ksize value of the measurement variable.
 * 
 * This method returns the ksize value, which is used in the formula for calculating the 
 * measurement variable's final value. The ksize represents the size-related coefficient.
 * 
 * @return The ksize value.
 */
qreal MeasurementVariable::GetKsize() const
{
    return d->ksize;
}

/**
 * @brief Sets the ksize value of the measurement variable.
 * 
 * This method assigns a new value to the ksize, which is used in the formula for calculating the 
 * measurement variable's final value. The ksize represents the size-related coefficient.
 * 
 * @param value The new ksize value to be set.
 */
// cppcheck-suppress unusedFunction
void MeasurementVariable::SetKsize(const qreal &value)
{
    d->ksize = value;
}

/**
 * @brief Retrieves the kheight value of the measurement variable.
 * 
 * This method returns the kheight, which is used in the formula for calculating the measurement 
 * variable's final value. The kheight represents the height-related coefficient.
 * 
 * @return The current kheight value.
 */
qreal MeasurementVariable::GetKheight() const
{
    return d->kheight;
}

/**
 * @brief Sets the kheight value of the measurement variable.
 * 
 * This method sets the kheight, which is used in the formula for calculating the measurement 
 * variable's final value. The kheight represents the height-related coefficient.
 * 
 * @param value The new kheight value to be set.
 */
// cppcheck-suppress unusedFunction
void MeasurementVariable::SetKheight(const qreal &value)
{
    d->kheight = value;
}
