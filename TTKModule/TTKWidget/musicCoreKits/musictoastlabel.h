#ifndef MUSICTOASTLABEL_H
#define MUSICTOASTLABEL_H

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
#include <QTimer>
#include "musicglobaldefine.h"

/*! @brief The class of the toast widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicToastLabel : public QLabel
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicToastLabel)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicToastLabel(QWidget *parent = nullptr);
    /*!
     * Object contsructor by context text.
     */
    explicit MusicToastLabel(const QString &text, QWidget *parent = nullptr);
    ~MusicToastLabel();

    /*!
     * Set text margin in the body.
     */
    void setFontMargin(int height, int width);
    /*!
     * Get timer interval.
     */
    int timerInterval() const;
    /*!
     * Set context font size.
     */
    void setFontSize(int size);

    /*!
     * Popup the toast widget in parent widget.
     */
    void popup(QWidget *parent = nullptr);
    /*!
     * Create default label.
     */
    static void popup(const QString &text);

Q_SIGNALS:
    /*!
     * Animation close changed.
     */
    void animationCloseChanged();

public Q_SLOTS:
    /*!
     * Set context text.
     */
    void setText(const QString &text);

private Q_SLOTS:
    /*!
     * Close animation when tiem out.
     */
    void closeAnimation();

protected:
    /*!
     * Override the widget event.
     */
    virtual void paintEvent(QPaintEvent *event) override final;

    QTimer m_timer;
    QFont m_font;
    QPoint m_margin;

};

#endif // MUSICTOASTLABEL_H
