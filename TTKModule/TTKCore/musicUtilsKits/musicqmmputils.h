#ifndef MUSICQMMPUTILS_H
#define MUSICQMMPUTILS_H

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

#include "musicglobaldefine.h"

/*! @brief The namespace of the utils qmmp.
 * @author Greedysky <greedysky@163.com>
 */
namespace MusicUtils
{
    namespace QMMP
    {
        /*!
         * Get qmmp plugin dir path.
         */
        TTK_MODULE_EXPORT QString pluginPath(const QString &module, const QString &format);
        /*!
         * Update qmmp config file transfer.
         */
        TTK_MODULE_EXPORT void updateQmmpConfigFile();

        /*!
         * Enable visual module control.
         */
        TTK_MODULE_EXPORT void enabledVisualPlugin(const QString &name, bool enable);
        /*!
         * Enable effect module control.
         */
        TTK_MODULE_EXPORT void enabledEffectPlugin(bool enable);
        /*!
         * Enable effect module control.
         */
        TTK_MODULE_EXPORT void enabledEffectPlugin(const QString &name, bool enable);

        /*!
         * Check effect is valid.
         */
        TTK_MODULE_EXPORT QStringList effectPlugins();
        /*!
         * Check effect has setting.
         */
        TTK_MODULE_EXPORT bool effectHasSetting(const QString &name);
        /*!
         * Show effect setting control.
         */
        TTK_MODULE_EXPORT void showEffectSetting(const QString &name, QWidget *parent);

        /*!
         * Update ripple spectrum config file transfer.
         */
        TTK_MODULE_EXPORT void updateRippleSpectrumConfigFile();
    }
}

#endif // MUSICQMMPUTILS_H
