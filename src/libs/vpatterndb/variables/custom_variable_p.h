//  @file   custom_variable_p.h
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
 **  @file   vincrement_p.h
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   20 8, 2014
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

#ifndef CUSTOM_VARIABLE_P_H
#define CUSTOM_VARIABLE_P_H

#include <QSharedData>

#include "../ifc/ifcdef.h"
#include "../vcontainer.h"
#include "../vmisc/diagnostic.h"

QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Weffc++")
QT_WARNING_DISABLE_GCC("-Wnon-virtual-dtor")

/**
 * @brief CustomVariableData class for managing variable data with shared ownership.
 * 
 * This class inherits from QSharedData and is used to manage the data associated with a custom variable.
 * It supports shared ownership semantics, which allows multiple instances to share the same data efficiently.
 * 
 * @details
 * The CustomVariableData class includes:
 * - Default constructor to initialize an empty variable with default values.
 * - Parameterized constructor to initialize the variable with specific data, index, formula, and status.
 * - Copy constructor for creating a copy of an existing CustomVariableData instance.
 * - Destructor to clean up resources.
 * - Public attributes to store the variable's index, formula, formula validity status, and associated data container.
 * - Private assignment operator declared as deleted to prevent assignment.
 * 
 * Attributes:
 * - quint32 index: A unique identifier for each variable.
 * - QString formula: A string representing the formula associated with the variable.
 * - bool formulaOk: A boolean indicating whether the formula is valid.
 * - VContainer data: A container object holding the data associated with the variable.
 * 
 * Note: The assignment operator is deleted to prevent copying of the instance using the assignment operator.
 */
class CustomVariableData : public QSharedData
{
public:

    CustomVariableData()
        : index(NULL_ID)
        , formula(QString())
        , formulaOk(false)
        , data(VContainer(nullptr, nullptr))
    {}

    CustomVariableData(VContainer *data, quint32 index, const QString &formula, bool ok)
        : index(index)
        , formula(formula)
        , formulaOk(ok)
        , data(*data)
    {}

    CustomVariableData(const CustomVariableData &variable)
        : QSharedData(variable)
        , index(variable.index)
        , formula(variable.formula)
        , formulaOk(variable.formulaOk)
        , data(variable.data)
    {}

    virtual  ~CustomVariableData();

    /** @brief id each variable have unique identificator */
    quint32    index;
    QString    formula;
    bool       formulaOk;
    VContainer data;

private:
    CustomVariableData &operator=(const CustomVariableData &) Q_DECL_EQ_DELETE;
};

CustomVariableData::~CustomVariableData()
{}

QT_WARNING_POP

#endif // CUSTOM_VARIABLE_P_H
