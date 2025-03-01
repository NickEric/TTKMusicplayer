#ifndef MUSICABSTRACTFLOATWIDGET_H
#define MUSICABSTRACTFLOATWIDGET_H

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

#include <QLabel>
#include <QPropertyAnimation>

#include "musicglobaldefine.h"

/*! @brief The class of the float widget base.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicAbstractFloatWidget : public QLabel
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicAbstractFloatWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicAbstractFloatWidget(QWidget *parent = nullptr);
    ~MusicAbstractFloatWidget();

    /*!
     * Set block animation state or not.
     */
    inline void setBlockAnimation(bool b) { m_blockAnimation = b; }
    /*!
     * Resize window bound by given width and height.
     * Subclass should implement this function.
     */
    virtual void resizeWindow(int width, int height) = 0;

protected:
    /*!
     * Override the widget event.
     */
#if TTK_QT_VERSION_CHECK(6,0,0)
    virtual void enterEvent(QEnterEvent *event) override;
#else
    virtual void enterEvent(QEvent *event) override;
#endif
    virtual void leaveEvent(QEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *) override final {}
    virtual void mousePressEvent(QMouseEvent *) override final {}
    virtual void mouseMoveEvent(QMouseEvent *) override final {}
    virtual void mouseReleaseEvent(QMouseEvent *) override final {}
    /*!
     * Show animation in case.
     */
    void animationIn();
    /*!
     * Show animation out case.
     */
    void animationOut();

    QPropertyAnimation *m_animation;
    QRect m_rectIn, m_rectOut;
    bool m_blockAnimation;

};

#endif // MUSICABSTRACTFLOATWIDGET_H
