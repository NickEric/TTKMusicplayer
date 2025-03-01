#ifndef MUSICDOWNLOADMANAGER_H
#define MUSICDOWNLOADMANAGER_H

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

#include "ttksingleton.h"
#include "musicnetworkdefines.h"

/*! @brief The class of the download manager pair.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct TTK_MODULE_EXPORT MusicDownLoadPairData
{
    qint64 m_timestamp;
    QObject *m_object;
    MusicObject::RecordType m_type;

    MusicDownLoadPairData()
    {
        m_timestamp = -1;
        m_object = nullptr;
        m_type = MusicObject::RecordNormalDownload;
    }

    MusicDownLoadPairData(qint64 t) : MusicDownLoadPairData()
    {
        m_timestamp = t;
    }

    MusicDownLoadPairData(qint64 t, QObject *object, MusicObject::RecordType type)
    {
        m_timestamp = t;
        m_object = object;
        m_type = type;
    }

    bool operator< (const MusicDownLoadPairData &other) const
    {
        return m_timestamp < other.m_timestamp;
    }

    bool operator== (const MusicDownLoadPairData &other) const
    {
        return m_timestamp == other.m_timestamp;
    }
}MusicDownLoadPairData;

/*! @brief The class of produce the download manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicDownLoadManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicDownLoadManager)
public:
    /*!
     * Set mutiple network connection object.
     */
    void connectNetworkMultiValue(QObject *object);
    /*!
     * Remove mutiple network connection object.
     */
    void removeNetworkMultiValue(QObject *object);

    /*!
     * Set music data network connection object.
     */
    void connectMusicDownload(const MusicDownLoadPairData &pair);
    /*!
     * Reset music data network connection object.
     */
    void reconnectMusicDownload(const MusicDownLoadPairData &pair);
    /*!
     * Remove music data network connection object.
     */
    void removeMusicDownload(const MusicDownLoadPairData &pair);

private Q_SLOTS:
    /*!
     * Update download percent total time and current time progress.
     */
    void downloadProgressChanged(float percent, const QString &total, qint64 time);

protected:
    QList<QObject*> m_queueList;
    QList<MusicDownLoadPairData> m_pairList;

    DECLARE_SINGLETON_CLASS(MusicDownLoadManager)

};

#define G_DOWNLOAD_MANAGER_PTR makeMusicDownLoadManager()
TTK_MODULE_EXPORT MusicDownLoadManager* makeMusicDownLoadManager();

#endif // MUSICDOWNLOADMANAGER_H
