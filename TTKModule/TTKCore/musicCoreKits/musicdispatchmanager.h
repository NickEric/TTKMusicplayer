#ifndef MUSICDISPATCHMANAGER_H
#define MUSICDISPATCHMANAGER_H

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

#include <QMutex>
#include "ttksingleton.h"

class QTimer;

/*! @brief The class of the functions dispatch item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct TTK_MODULE_EXPORT MusicDispatchItem
{
    int m_type;
    int m_times;
    TTKVariantList m_args;
    MusicDispatchItem()
    {
        m_times = 0;
        m_type = -1;
    }

    inline bool isEmpty() const
    {
        return m_args.isEmpty();
    }

    inline bool isValid() const
    {
        return m_times <= 5;
    }

}MusicDispatchItem;


/*! @brief The class of the functions dispatch manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicDispatchManager : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicDispatchManager)
public:
    /*!
     * Set dispatch.
     */
    void dispatch(int type);
    void dispatch(int type, void *funcs);
    void dispatch(int type, const TTKVariantList &args);

public:
    /*!
     * Set dispatch.
     */
    void dispatch(int type, const QVariant &arg1);
    void dispatch(int type, const QVariant &arg1, const QVariant &arg2);
    void dispatch(int type, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3);
    void dispatch(int type, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3, const QVariant &arg4);

private Q_SLOTS:
    /*!
     * Active functions.
     */
    void activeFunctions();

protected:
    /*!
     * Object contsructor.
     */
    MusicDispatchManager();
    ~MusicDispatchManager();

    QMutex m_mutex;
    QTimer *m_timer;
    QList<MusicDispatchItem*> m_observer;

    DECLARE_SINGLETON_CLASS(MusicDispatchManager)

};

#define G_DISPATCH_PTR makeMusicDispatchManager()
TTK_MODULE_EXPORT MusicDispatchManager* makeMusicDispatchManager();

#endif // MUSICDISPATCHMANAGER_H
