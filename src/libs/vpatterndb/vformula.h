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
 **  @file   vformula.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   28 8, 2014
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

#ifndef VFORMULA_H
#define VFORMULA_H

#include <QCoreApplication>
#include <QMetaType>
#include <QString>
#include <QtGlobal>

enum class FormulaType : char{ToUser, FromUser};

class VContainer;

/**
 * @brief The VFormula class represents a mathematical formula used in measurements.
 * 
 * This class provides functionalities to initialize, set, and evaluate a formula. It supports different operations such as 
 * assignment, equality comparison, and translation of formulas. The formula can be represented as a string and evaluated 
 * to obtain a numerical result.
 * 
 * @details
 * - VFormula(): Default constructor.
 * - VFormula(const QString &formula, const VContainer *container): Constructor initializing the formula and its container.
 * - VFormula &operator=(const VFormula &formula): Assignment operator.
 * - VFormula(const VFormula &formula): Copy constructor.
 * - bool operator==(const VFormula &formula) const: Equality comparison operator.
 * - bool operator!=(const VFormula &formula) const: Inequality comparison operator.
 * 
 * The class includes methods to get and set the formula, check for errors, and evaluate the formula:
 * - QString GetFormula(FormulaType type = FormulaType::ToUser) const: Returns the formula string.
 * - void SetFormula(const QString &value, FormulaType type = FormulaType::ToUser): Sets the formula string.
 * - QString getStringValue() const: Gets the string value of the formula.
 * - qreal getDoubleValue() const: Gets the double value of the formula.
 * - bool getCheckZero() const: Gets the checkZero flag.
 * - void setCheckZero(bool value): Sets the checkZero flag.
 * - const VContainer *getData() const: Gets the data container.
 * - void setData(const VContainer *value): Sets the data container.
 * - quint32 getToolId() const: Gets the tool ID.
 * - void setToolId(const quint32 &value): Sets the tool ID.
 * - QString getPostfix() const: Gets the postfix string.
 * - void setPostfix(const QString &value): Sets the postfix string.
 * - bool error() const: Checks if there is an error in the formula.
 * - static int FormulaTypeId(): Returns the formula type ID.
 * - void Eval(): Evaluates the formula.
 * 
 * @note The private members of the class include:
 * - QString formula: The formula string.
 * - QString value: The evaluated value of the formula as a string.
 * - bool checkZero: Flag to check if the result is zero.
 * - const VContainer *data: Pointer to the container holding the data for evaluation.
 * - quint32 toolId: ID of the tool associated with the formula.
 * - QString postfix: Postfix string appended to the result.
 * - bool _error: Flag indicating if there is an error in the formula.
 * - qreal dValue: The evaluated value of the formula as a double.
 */
class VFormula
{
    Q_DECLARE_TR_FUNCTIONS(VFormula)
public:
    VFormula();
    VFormula(const QString &formula, const VContainer *container);
    VFormula &operator=(const VFormula &formula);
    VFormula(const VFormula &formula);
    bool operator==(const VFormula &formula) const;
    bool operator!=(const VFormula &formula) const;

    QString GetFormula(FormulaType type = FormulaType::ToUser) const;
    void SetFormula(const QString &value, FormulaType type = FormulaType::ToUser);

    QString getStringValue() const;
    qreal   getDoubleValue() const;

    bool getCheckZero() const;
    void setCheckZero(bool value);

    const VContainer *getData() const;
    void setData(const VContainer *value);

    quint32 getToolId() const;
    void setToolId(const quint32 &value);

    QString getPostfix() const;
    void setPostfix(const QString &value);

    bool error() const;

    static int FormulaTypeId();
    void Eval();
    
private:
    QString formula;
    QString value;
    bool checkZero;
    const VContainer *data;
    quint32 toolId;
    QString postfix;
    bool _error;
    qreal dValue;


};
Q_DECLARE_METATYPE(VFormula)

#endif // VFORMULA_H
