#ifndef TTKRUNOBJECT_H
#define TTKRUNOBJECT_H

/***************************************************************************
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttkprivate.h"

class TTKRunObjectPrivate;

/*! @brief The class of the ttk run object.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT TTKRunObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit TTKRunObject(QObject *parent = nullptr);

    /*!
     * Check current setting file's validation.
     */
    void valid() const;
    /*!
     * To run main window.
     */
    void run(int argc, char **argv) const;

private Q_SLOTS:
    /*!
     * Run finished.
     */
    void finished(int code);

private:
    TTK_DECLARE_PRIVATE(TTKRunObject)

};

#endif // TTKRUNOBJECT_H
