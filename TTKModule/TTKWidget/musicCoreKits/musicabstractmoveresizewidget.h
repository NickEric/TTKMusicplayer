#ifndef MUSICABSTRACTMOVERESIZEWIDGET_H
#define MUSICABSTRACTMOVERESIZEWIDGET_H

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

#include <QWidget>
#include "musicglobaldefine.h"

/*! @brief The class of the moving resize struct.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct TTK_MODULE_EXPORT MoveResizeData
{
    bool m_mouseLeftPress;
    bool m_isPressBorder;
    QPoint m_mousePos;
    QPoint m_windowPos;
    QSize m_pressedSize;
}MoveResizeData;

/*! @brief The class of the moving resize widget base.
 * @author Greedysky <greedysky@163.com>
 *         Lverson   <what951006@163.com>
 */
class TTK_MODULE_EXPORT MusicAbstractMoveResizeWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicAbstractMoveResizeWidget)
public:
    enum Direction
    {
        Direction_No = 0,                                           /*!< no direction*/
        Direction_Left = 1,                                         /*!< left direction*/
        Direction_Top = 2,                                          /*!< top direction*/
        Direction_Right = 4,                                        /*!< right direction*/
        Direction_Bottom = 8,                                       /*!< bottom direction*/
        Direction_LeftTop = Direction_Left + Direction_Top,         /*!< left top direction*/
        Direction_LeftBottom = Direction_Left + Direction_Bottom,   /*!< left bottom direction*/
        Direction_RightTop = Direction_Right + Direction_Top,       /*!< right top direction*/
        Direction_RightBottom = Direction_Right + Direction_Bottom  /*!< right bottom direction*/
    };
    /*!
     * Object contsructor.
     */
    explicit MusicAbstractMoveResizeWidget(QWidget *parent = nullptr);

protected:
    /*!
     * Override the widget event.
     */
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override final;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override final;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    /*!
     * Size direction detected.
     */
    void sizeDirection();
    /*!
     * Move direction to be.
     */
    void moveDirection();

    MoveResizeData m_struct;
    Direction m_direction;

};

#endif // MUSICABSTRACTMOVERESIZEWIDGET_H
