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
 **  @file
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   24 9, 2016
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2016 Seamly2D project
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

#ifndef VCURVECLENGTH_H
#define VCURVECLENGTH_H

#include <qcompilerdetection.h>
#include <QString>
#include <QtGlobal>

#include "vcurvevariable.h"

enum class CurveCLength : char { C1, C2 };

class VAbstractBezier;
class VSpline;

/**
 * @brief Class representing the length of a curve segment.
 * 
 * The VCurveCLength class inherits from VCurveVariable and is used to store and manipulate the length of a curve segment.
 * This class includes multiple constructors to initialize instances with different sets of parameters, 
 * such as a curve, segment, and measurement unit. It also provides a copy constructor and an assignment operator 
 * for copying instances. The destructor ensures proper cleanup of resources used by the object.
 * 
 * The key functionalities of this class include:
 * - Storing the unique identifier of the curve length variable.
 * - Storing the unique identifier of the parent of the curve length variable.
 * - Storing and managing the length of various curve types, including Bezier curves and splines.
 * - Supporting both initialization with specific curve segments and general curve lengths.
 * 
 * The constructors enable the creation of VCurveCLength objects with either a VAbstractBezier curve or a VSpline object, 
 * along with specifying the type of curve length and measurement unit.
 * 
 * The class also provides an assignment operator for assigning values from another VCurveCLength object, ensuring 
 * proper copying of the curve length properties.
 */
class VCurveCLength : public VCurveVariable
{
public:
    VCurveCLength();
    VCurveCLength(const quint32 &id, const quint32 &parentId, const VAbstractBezier *curve, CurveCLength cType,
                  Unit patternUnit);
    VCurveCLength(const quint32 &id, const quint32 &parentId, const QString &baseCurveName, const VSpline &spl,
                 CurveCLength cType, Unit patternUnit, qint32 segment);
    VCurveCLength(const VCurveCLength &var);
    VCurveCLength &operator=(const VCurveCLength &var);
    virtual ~VCurveCLength() Q_DECL_OVERRIDE;
};

#endif // VCURVECLENGTH_H
