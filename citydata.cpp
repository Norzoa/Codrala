/*     Copyright (C) 2015 Le Dévic Trystan

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include "citydata.h"

CData::CData(QString gCp, QString gVille)
{
    cp.append(gCp);
    ville.append(gVille);
}

CData::CData()
{
    cp = QString();
    ville  = QString();
}

void CData::setCP(const QString & str)
{
    cp.append(str);
}

void CData::setVille(const QString &str)
{
    ville.append(str);
}

void CData::clear()
{
    cp = QString();
    ville = QString();
}

QString CData::getCP() const
{
    return cp;
}

QString CData::getVille() const
{
    return ville;
}
