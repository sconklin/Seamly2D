//  @file   custom_variable.h
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
 **  @file   vincrementtablerow.h
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

#ifndef CUSTOM_VARIABLE_H
#define CUSTOM_VARIABLE_H

#include <qcompilerdetection.h>
#include <QSharedDataPointer>
#include <QString>
#include <QTypeInfo>
#include <QtGlobal>

#include "vvariable.h"

class CustomVariableData;
class VContainer;

/**
 * @brief The CustomVariable class represents a custom variable with associated data, formula, and properties.
 * 
 * This class extends the VVariable class and includes additional attributes and methods specific to custom variables. 
 * It manages a formula, an index, and other properties related to a custom measurement variable.
 * 
 * @details
 * - Default constructor initializes an empty CustomVariable.
 * - Parameterized constructor initializes a CustomVariable with specified data, name, index, base value, formula, status, and description.
 * - Copy constructor initializes a CustomVariable by copying another CustomVariable.
 * - Destructor cleans up any resources used by the CustomVariable.
 * - Assignment operator assigns the values from another CustomVariable to this CustomVariable.
 * - Move assignment operator moves the values from another CustomVariable to this CustomVariable without copying.
 * - Swap method swaps the values of this CustomVariable with another CustomVariable.
 * - getIndex() returns the index of the CustomVariable.
 * - GetFormula() returns the formula associated with the CustomVariable.
 * - IsFormulaOk() checks if the formula of the CustomVariable is valid.
 * - GetData() returns the data container associated with the CustomVariable.
 * 
 * @note The class uses a shared data pointer for managing the CustomVariableData.
 */
class CustomVariable :public VVariable
{
public:
                CustomVariable();
                CustomVariable(VContainer *data, const QString &name, quint32 index, qreal base, const QString &formula, bool ok,
                               const QString &description = QString());
                CustomVariable(const CustomVariable &variable);

    virtual    ~CustomVariable() override;

                CustomVariable &operator=(const CustomVariable &variable);

#ifdef Q_COMPILER_RVALUE_REFS
	            CustomVariable &operator=(CustomVariable &&variable) Q_DECL_NOTHROW;
#endif

    void        Swap(CustomVariable &variable) Q_DECL_NOTHROW;
    quint32     getIndex() const;
    QString     GetFormula() const;
    bool        IsFormulaOk() const;
    VContainer *GetData();

private:
    QSharedDataPointer<CustomVariableData> d;
};

Q_DECLARE_TYPEINFO(CustomVariable, Q_MOVABLE_TYPE);

#endif // CUSTOM_VARIABLE_H
