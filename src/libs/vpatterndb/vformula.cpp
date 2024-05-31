/***************************************************************************
 **  @file   vformula.cpp
 **  @author Douglas S Caskey
 **  @date   17 Sep, 2023
 **
 **  @copyright
 **  Copyright (C) 2017 - 2023 Seamly, LLC
 **  https://github.com/fashionfreedom/seamly2d
 **
 **  @brief
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
 **  along with Seamly2D. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

/************************************************************************
 **
 **  @file   vformula.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   28 8, 2014
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2014 Valentina project
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
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "vformula.h"

#include <qnumeric.h>
#include <QMessageLogger>
#include <QScopedPointer>
#include <QtDebug>

#include "../qmuparser/qmuparsererror.h"
#include "../vgeometry/../ifc/ifcdef.h"
#include "../vmisc/def.h"
#include "../vmisc/vabstractapplication.h"
#include "../vmisc/vcommonsettings.h"
#include "calculator.h"
#include "vcontainer.h"
#include "vtranslatevars.h"

/**
 * @brief Constructor for the VFormula class.
 *
 * This constructor initializes a VFormula object with default values. The initialization ensures that all member variables are set to their initial states.
 *
 * @details
 * The member variables initialized in this constructor include:
 * - formula: Initialized to an empty QString.
 * - value: Initialized to a translated string "Error".
 * - checkZero: Initialized to true, indicating a check for zero values.
 * - data: Initialized to nullptr, indicating no data is associated initially.
 * - toolId: Initialized to NULL_ID, representing a null identifier.
 * - postfix: Initialized to an empty QString.
 * - _error: Initialized to true, indicating an error state.
 * - dValue: Initialized to 0, representing a double value of zero.
 */
VFormula::VFormula()
    : formula(QString()), value(tr("Error")), checkZero(true), data(nullptr), toolId(NULL_ID),
      postfix(QString()), _error(true), dValue(0)
{
}

/**
 * @brief Constructor for the VFormula class with formula and container.
 *
 * This constructor initializes a VFormula object with specified formula and container. It sets up the object with translated formula, initializes member variables, and evaluates the formula.
 *
 * @param formula The formula to be translated and used for initialization.
 * @param container The container associated with the formula.
 *
 * @details
 * The member variables initialized in this constructor include:
 * - formula: Translated using qApp->translateVariables()->FormulaToUser and initialized with the provided formula.
 * - value: Initialized to a translated string "Error".
 * - checkZero: Initialized to true, indicating a check for zero values.
 * - data: Initialized with the provided container.
 * - toolId: Initialized to NULL_ID, representing a null identifier.
 * - postfix: Initialized to an empty QString.
 * - _error: Initialized to true.
 * - dValue: Initialized to 0, representing a double value of zero.
 *
 * The constructor also performs the following actions:
 * - Replaces any newline characters in the formula with spaces.
 * - Calls the Eval() function to evaluate the formula.
 */
VFormula::VFormula(const QString &formula, const VContainer *container)
    : formula(qApp->translateVariables()->FormulaToUser(formula, qApp->Settings()->getOsSeparator())),
      value(tr("Error")),
      checkZero(true),
      data(container),
      toolId(NULL_ID),
      postfix(QString()),
      _error(true),
      dValue(0)
{
    this->formula.replace("\n", " "); // Replace line return with spaces for calc if exist
    Eval();
}

/**
 * @brief Assignment operator for the VFormula class.
 *
 * This operator overload assigns the values from another VFormula object to this object. It ensures all member variables are copied correctly and returns a reference to this object.
 *
 * @param formula The VFormula object to be assigned to this object.
 * @return A reference to this VFormula object.
 *
 * @details
 * The member variables copied in this assignment operator include:
 * - formula: The formula string from the source VFormula object.
 * - value: The string value from the source VFormula object.
 * - checkZero: The boolean indicating if zero check is enabled, from the source VFormula object.
 * - data: The container data from the source VFormula object.
 * - toolId: The tool identifier from the source VFormula object.
 * - postfix: The postfix string from the source VFormula object.
 * - _error: The error state from the source VFormula object.
 * - dValue: The double value from the source VFormula object.
 *
 * The function first checks if the source object is the same as the current object to prevent self-assignment. If not, it performs the member-wise assignment and returns a reference to this object.
 */
VFormula &VFormula::operator=(const VFormula &formula)
{
    if (&formula == this)
    {
        return *this;
    }
    this->formula = formula.GetFormula();
    this->value = formula.getStringValue();
    this->checkZero = formula.getCheckZero();
    this->data = formula.getData();
    this->toolId = formula.getToolId();
    this->postfix = formula.getPostfix();
    this->_error = formula.error();
    this->dValue = formula.getDoubleValue();
    return *this;
}

/**
 * @brief Copy constructor for the VFormula class.
 *
 * This constructor initializes a new VFormula object as a copy of an existing VFormula object. It ensures all member variables are copied correctly.
 *
 * @param formula The VFormula object to be copied.
 *
 * @details
 * The member variables copied in this constructor include:
 * - formula: The formula string from the source VFormula object.
 * - value: The string value from the source VFormula object.
 * - checkZero: The boolean indicating if zero check is enabled, from the source VFormula object.
 * - data: The container data from the source VFormula object.
 * - toolId: The tool identifier from the source VFormula object.
 * - postfix: The postfix string from the source VFormula object.
 * - _error: The error state from the source VFormula object.
 * - dValue: The double value from the source VFormula object.
 *
 * This copy constructor ensures that the new object is an exact copy of the given VFormula object, with all member variables initialized to the same values as those in the source object.
 */
VFormula::VFormula(const VFormula &formula)
    : formula(formula.GetFormula()), value(formula.getStringValue()), checkZero(formula.getCheckZero()),
      data(formula.getData()), toolId(formula.getToolId()), postfix(formula.getPostfix()), _error(formula.error()),
      dValue(formula.getDoubleValue())
{
}

/**
 * @brief Equality operator for the VFormula class.
 *
 * This operator checks if two VFormula objects are equal by comparing all their member variables.
 *
 * @param formula The VFormula object to compare with.
 * @return True if all member variables of both objects are equal, false otherwise.
 *
 * @details
 * The comparison checks the following member variables:
 * - formula: Compares the formula strings of both objects.
 * - value: Compares the string values of both objects.
 * - checkZero: Compares the boolean indicating if zero check is enabled in both objects.
 * - data: Compares the container data of both objects.
 * - toolId: Compares the tool identifiers of both objects.
 * - postfix: Compares the postfix strings of both objects.
 * - _error: Compares the error states of both objects.
 * - dValue: Uses the VFuzzyComparePossibleNulls function to compare the double values of both objects.
 *
 * The operator returns true if all these member variables are equal.
 */
bool VFormula::operator==(const VFormula &formula) const
{
    bool isEqual = false;
    if (this->formula == formula.GetFormula() && this->value == formula.getStringValue() &&
        this->checkZero == formula.getCheckZero() && this->data == formula.getData() &&
        this->toolId == formula.getToolId() && this->postfix == formula.getPostfix() &&
        this->_error == formula.error() && VFuzzyComparePossibleNulls(this->dValue, formula.getDoubleValue()))
    {
        isEqual = true;
    }
    return isEqual;
}

/**
 * @brief Inequality operator for the VFormula class.
 *
 * This operator checks if two VFormula objects are not equal by negating the result of the equality operator.
 *
 * @param formula The VFormula object to compare with.
 * @return True if the two VFormula objects are not equal, false otherwise.
 *
 * @details
 * The inequality operator returns the negation of the equality operator (operator==)
 *
 */
bool VFormula::operator!=(const VFormula &formula) const
{
    return !VFormula::operator==(formula);
}

/**
 * @brief Retrieves the formula string in the specified format.
 *
 * This function returns the formula string based on the specified FormulaType.
 *
 * @param type The type indicating the desired format of the formula.
 *             It can be FormulaType::ToUser or another type indicating a translation is needed.
 * @return The formula string in the specified format.
 *
 * @details
 * The function checks the provided FormulaType. If it is FormulaType::ToUser, the function returns the formula as-is.
 * For other types, it uses the application's translation mechanism to convert the formula from the user format,
 * using the operating system's separator settings.
 *
 * This provides flexibility in how the formula is represented, allowing for both direct access and translation as needed.
 */
QString VFormula::GetFormula(FormulaType type) const
{
    if (type == FormulaType::ToUser)
    {
        return formula;
    }
    else
    {
        return qApp->translateVariables()->TryFormulaFromUser(formula, qApp->Settings()->getOsSeparator());
    }
}

/**
 * @brief Sets the formula string with optional translation.
 *
 * This function sets the formula string to a new value, with an option to translate it based on the specified FormulaType.
 * If the type is FormulaType::ToUser, it translates the value to the user format before storing it.
 * After setting the new formula, it replaces any line returns with spaces for proper calculation and evaluates the formula.
 *
 * @param value The new formula string to be set.
 * @param type The type indicating the format of the provided formula.
 *             It can be FormulaType::ToUser or another type indicating no translation is needed.
 *
 * @details
 * The function first checks if the new value differs from the current formula. If so, it proceeds to set the formula.
 * - For FormulaType::ToUser, it uses the application's translation mechanism to convert the value to the user format,
 *   considering the operating system's separator settings.
 * - For other types, it directly assigns the value to the formula.
 *
 * After setting the formula, it replaces any newline characters with spaces to ensure correct calculation.
 * Finally, it calls the Eval() function to evaluate the new formula.
 */
void VFormula::SetFormula(const QString &value, FormulaType type)
{
    if (formula != value)
    {
        if (type == FormulaType::ToUser)
        {
            formula = qApp->translateVariables()->FormulaToUser(value, qApp->Settings()->getOsSeparator());
        }
        else
        {
            formula = value;
        }
        formula.replace("\n", " "); // Replace line return with spaces for calc if exist
        Eval();
    }
}

/**
 * @brief Retrieves the string value of the formula.
 *
 * This function returns the current string value of the formula.
 *
 * @return The string value of the formula.
 *
 * @details
 * The string value represents the evaluated result of the formula as a QString.
 */
QString VFormula::getStringValue() const
{
    return value;
}

/**
 * @brief Retrieves the double value of the formula.
 * 
 * This function returns the current double value of the formula.
 * 
 * @return The double value of the formula.
 * 
 * @details
 * The double value represents the evaluated result of the formula as a qreal.
 */
qreal VFormula::getDoubleValue() const
{
    return dValue;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Checks if the zero-check flag is set.
 * 
 * This function returns the state of the zero-check flag for the formula.
 * 
 * @return True if zero-check is enabled, false otherwise.
 * 
 */
bool VFormula::getCheckZero() const
{
    return checkZero;
}

/**
 * @brief Sets the zero-check flag.
 * 
 * This function sets the zero-check flag to the specified value. If the flag is changed,
 * it re-evaluates the formula.
 * 
 * @param value The new value for the zero-check flag.
 * 
 * @details
 * The zero-check flag determines whether the formula should check for zero values in its calculations.
 * When this flag is changed, the formula is re-evaluated to reflect the new setting.
 */
void VFormula::setCheckZero(bool value)
{
    if (checkZero != value)
    {
        checkZero = value;
        Eval();
    }
}

/**
 * @brief Gets the associated data container.
 * 
 * This function returns a pointer to the VContainer object associated with this formula.
 * 
 * @return A pointer to the VContainer object.
 * 
 * @details
 * The data container holds additional data required for evaluating the formula. This function provides
 * access to that container for further use or inspection.
 */
const VContainer *VFormula::getData() const
{
    return data;
}

/**
 * @brief Sets the data container for the formula.
 * 
 * This function assigns a new VContainer object to the formula and triggers re-evaluation if the new data container is different from the current one and is not null.
 * 
 * @param value A pointer to the new VContainer object.
 * 
 * @details
 * The data container holds additional data required for evaluating the formula. Changing the data container
 * will cause the formula to be re-evaluated with the new data.
 */
void VFormula::setData(const VContainer *value)
{
    if (data != value && value != nullptr)
    {
        data = value;
        Eval();
    }
}

/**
 * @brief Gets the tool ID associated with the formula.
 * 
 * This function returns the tool ID that is associated with the formula.
 * 
 * @return The tool ID as a quint32 value.
 * 
 * @details
 * The tool ID uniquely identifies the tool that uses this formula.
 */
quint32 VFormula::getToolId() const
{
    return toolId;
}

/**
 * @brief Sets the tool ID for the formula.
 * 
 * This function assigns a new tool ID to the formula.
 * 
 * @param value The new tool ID as a quint32 value.
 * 
 * @details
 * This ID links the formula to the specific tool it is intended for.
 */
void VFormula::setToolId(const quint32 &value)
{
    toolId = value;
}

/**
 * @brief Retrieves the postfix notation of the formula.
 * 
 * This function returns the postfix notation of the formula.
 * 
 * @return QString The postfix notation of the formula.
 * 
 */
QString VFormula::getPostfix() const
{
    return postfix;
}

/**
 * @brief Sets the postfix notation for the formula.
 * 
 * This function assigns a new postfix notation to the formula and reevaluates it if the new postfix is different from the current one.
 * 
 * @param value The new postfix notation to be set.
 * 
 */
void VFormula::setPostfix(const QString &value)
{
    if (postfix != value)
    {
        postfix = value;
        Eval();
    }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Checks if error is set in the formula.
 * 
 * This function returns the current error status of the formula evaluation.
 * 
 * @return A boolean value indicating the error status.
 * 
 */
bool VFormula::error() const
{
    return _error;
}

/**
 * @brief Gets the MetaType ID for VFormula.
 * 
 * This function returns the MetaType ID associated with the VFormula class.
 * 
 * @return An integer representing the MetaType ID for VFormula.
 * 
 * @details
 * The MetaType ID is a unique identifier for the VFormula class, which is used by the Qt Meta-Object system. This ID allows 
 * for runtime type information and dynamic casting within the Qt framework.
 */
int VFormula::FormulaTypeId()
{
    return qMetaTypeId<VFormula>();
}

/**
 * @brief Evaluates the formula and updates the value and error status.
 * 
 * This function evaluates the mathematical formula stored in the VFormula object. It translates the formula from the user
 * format to the internal format, calculates the result using the provided data container, and updates the value and error 
 * status accordingly.
 * 
 * @details
 * The evaluation process involves several steps:
 * - If the data container is null or the formula is empty, the value is set to "Error" and the error flag is set to true.
 * - If the formula is valid, a Calculator object is used to evaluate the formula with the data variables from the data container.
 * - If the result of the evaluation is infinite or NaN, the value is set to "Error" and the error flag is set to true.
 * - If the result is zero and the checkZero flag is true, the value is set to "0" and the error flag is set to true.
 * - If the result is valid and non-zero, the value is updated with the calculated result and the postfix string, and the error flag is set to false.
 * - In case of a mathematical parser error, the value is set to "Error", the error flag is set to true, and the error message is logged for debugging.
 * 
 * Note: The formula is translated from the user format to the internal format before evaluation, and the result is converted 
 * to a string representation using the application's locale settings.
 */
void VFormula::Eval()
{
    if (data == nullptr)
    {
        return;
    }
    if (formula.isEmpty())
    {
        value = tr("Error");
        _error = true;
        dValue = 0;
    }
    else
    {
        try
        {
            QScopedPointer<Calculator> cal(new Calculator());
            QString expression = qApp->translateVariables()->FormulaFromUser(formula, qApp->Settings()->getOsSeparator());
            const qreal result = cal->EvalFormula(data->DataVariables(), expression);

            if (qIsInf(result) || qIsNaN(result))
            {
                value = tr("Error");
                _error = true;
                dValue = 0;
            }
            else
            {
                // if result equal 0
                if (checkZero && qFuzzyIsNull(result))
                {
                    value = QString("0");
                    _error = true;
                    dValue = 0;
                }
                else
                {
                    dValue = result;
                    value = QString(qApp->LocaleToString(result) + " " + postfix);
                    _error = false;
                }
            }
        }
        catch (qmu::QmuParserError &error)
        {
            value = tr("Error");
            _error = true;
            dValue = 0;
            qDebug() << "\nMath parser error:\n"
                     << "--------------------------------------\n"
                     << "Message:     " << error.GetMsg() << "\n"
                     << "Expression:  " << error.GetExpr() << "\n"
                     << "--------------------------------------";
        }
    }
}
