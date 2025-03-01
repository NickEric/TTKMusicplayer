#ifndef QSYNCLISTDATA_H
#define QSYNCLISTDATA_H

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

#include "qsyncdatainterface.h"

/*! @brief The class of the sync cloud list data.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT QSyncListData : public QSyncDataInterface
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit QSyncListData(QNetworkAccessManager *networkManager, QObject *parent = nullptr);
    /*!
     * List data to operator.
     */
    void listDataOperator(const QString &bucket);

Q_SIGNALS:
    /*!
     * Receive data finshed.
     */
    void receiveFinshed(const QSyncDataItems &items);

protected Q_SLOTS:
    /*!
     * Receive data from server finshed.
     */
    virtual void receiveDataFromServer() override final;

};

#endif
