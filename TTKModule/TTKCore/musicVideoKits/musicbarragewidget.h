#ifndef MUSICBARRAGEWIDGET_H
#define MUSICBARRAGEWIDGET_H

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

#include "musicwidgetheaders.h"
#include "musicbarragerecord.h"

#include <QPropertyAnimation>

/*! @brief The class of the barrage animation.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicBarrageAnimation : public QPropertyAnimation
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicBarrageAnimation)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicBarrageAnimation(QObject *parent = nullptr);
    /*!
     * Object contsructor by tagrget and name.
     */
    MusicBarrageAnimation(QObject *target, const QByteArray &name, QObject *parent = nullptr);

    /*!
     * Set animation region size.
     */
    void setSize(const QSize &size);

public Q_SLOTS:
    /*!
     * Current animation is finished.
     */   void animationFinished();

protected:
    /*!
     * Init parameters.
     */
    void initialize();

    QSize m_parentSize;

};


/*! @brief The class of the barrage widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicBarrageWidget : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicBarrageWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicBarrageWidget(QObject *parent = nullptr);
    ~MusicBarrageWidget();

    /*!
     * Start barrage animation.
     */
    void start();
    /*!
     * Pause barrage animation.
     */
    void pause();
    /*!
     * Stop barrage animation.
     */
    void stop();

    /*!
     * Set animation region size.
     */
    void setSize(const QSize &size);
    /*!
     * Set current barrage animation on or not.
     */
    void barrageStateChanged(bool on);
    /*!
     * Add barrage record.
     */
    void addBarrage(const MusicBarrageRecord &record);

protected:
    /*!
     * Clear all items.
     */
    void deleteItems();
    /*!
     * Create barrage item label.
     */
    void createLabel();
    /*!
     * Create barrage item label by object.
     */
    QLabel *createLabel(const MusicBarrageRecord &record);
    /*!
     * Create barrage animation.
     */
    void createAnimation();
    /*!
     * Create barrage animation by object.
     */
    void createAnimation(QLabel *label);

    bool m_barrageState;
    QSize m_parentSize;
    QWidget *m_parentClass;
    QList<QLabel*> m_labels;
    QList<MusicBarrageAnimation*> m_animations;
    MusicBarrageRecords m_barrageRecords;

};

#endif // MUSICBARRAGEWIDGET_H
