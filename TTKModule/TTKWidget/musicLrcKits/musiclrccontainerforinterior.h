#ifndef MUSICLRCCCONTAINERFORINTERIOR_H
#define MUSICLRCCCONTAINERFORINTERIOR_H

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

#include "musiclrccontainer.h"

class MusicLrcFloatWidget;
class MusicLrcFloatPlayWidget;
class MusicClickedLabel;
class MusicLrcCommentsWidget;
class MusicLrcTranslatedWidget;
class MusicVLayoutAnimationWidget;

/*! @brief The class of the interior lrc container.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLrcContainerForInterior : public MusicLrcContainer
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLrcContainerForInterior)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLrcContainerForInterior(QWidget *parent = nullptr);
    ~MusicLrcContainerForInterior();

    /*!
     * Start timer clock to draw lrc.
     */
    virtual void startDrawLrc() override final;
    /*!
     * Stop timer clock to draw lrc.
     */
    virtual void stopDrawLrc() override final;
    /*!
     * Set setting parameter.
     */
    virtual void applySettingParameter() override final;

    /*!
     * Update current lrc by given time.
     */
    void updateCurrentLrc(qint64 time);
    /*!
     * Update current lrc by given state.
     */
    void updateCurrentLrc(int state);
    /*!
     * Get current lrc text in middle.
     */
    QString text() const;
    /*!
     * Set song speed by given time, return new time.
     */
    qint64 setSongSpeedChanged(qint64 time);
    /*!
     * Init function label widget.
     */
    void initFunctionLabel();

    /*!
     * Get state of background is artist shown.
     */
    inline void setLrcDisplayExpand(bool expand) { m_lrcDisplayAll = expand; }
    /*!
     * Get state of background is artist shown.
     */
    inline bool lrcDisplayExpand() const { return m_lrcDisplayAll; }
    /*!
     * Get state of background is artist shown.
     */
    inline bool artistBackgroundIsShow() const { return m_showArtistBackground; }

    /*!
     * Set current lrc size.
     */
    void setLrcSize(int size);
    /*!
     * Get current lrc size.
     */
    int lrcSize() const;
    /*!
     * Resize window bound by widget resize called.
     */
    void resizeWindow();

    /*!
     * Create float play widget.
     */
    void createFloatPlayWidget();
    /*!
     * Show full container or not.
     */
    void lrcWidgetShowFullScreen();

Q_SIGNALS:
    /*!
     * Update current play time when user adjust the progress.
     */
    void updateCurrentTime(qint64 time);
    /*!
     * The art background state has changed emit.
     */
    void artistBackgroundHasChanged();

public Q_SLOTS:
    /*!
     * Set current lrc size by action.
     */
    void lrcSizeChanged(QAction *action);
    /*!
     * Set lrc time speed changed by action.
     */
    void lrcTimeSpeedChanged(QAction *action);
    /*!
     * Revert lrc time speed.
     */
    void revertLrcTimeSpeed();
    /*!
     * Save lrc time changed to current lrc file.
     */
    void saveLrcTimeChanged();
    /*!
     * The artist background state has changed.
     */
    void artistBackgroundChanged();
    /*!
     * The artist background has uploaded.
     */
    void showArtistBackgroundUploadedWidget();
    /*!
     * Open current lrc file location.
     */
    void lrcOpenFileDir() const;
    /*!
     * Copy all lrcs to clipboard.
     */
    void lrcCopyClipboard() const;
    /*!
     * Show local link widget.
     */
    void showLocalLinkWidget();
    /*!
     * Show song comments widget.
     */
    void showSongCommentsWidget();
    /*!
     * Show song KMicro widget.
     */
    void showSoundKMicroWidget();
    /*!
     * Show lrc poster widget.
     */
    void showLrcPosterWidget();

private Q_SLOTS:
    /*!
     * Get translated lrc finished.
     */
    void queryTranslatedLrcFinished(const QString &bytes);
    /*!
     * Video button clicked.
     */
    void musicSongMovieClicked();
    /*!
     * Animation finished.
     */
    void updateAnimationLrc();
    /*!
     * Get all lrcs from tr container.
     */
    void translatedLrcData();

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    virtual void mousePressEvent(QMouseEvent *event) override final;
    virtual void mouseMoveEvent(QMouseEvent *event) override final;
    virtual void mouseReleaseEvent(QMouseEvent *event) override final;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override final;
    virtual void paintEvent(QPaintEvent *event) override final;
    virtual void resizeEvent(QResizeEvent *event) override final;
    /*!
     * Create color menu.
     */
    void createColorMenu(QMenu &menu);
    /*!
     * Revert lrc time speed by pos.
     */
    void revertLrcTimeSpeed(qint64 pos);
    /*!
     * Create no lrc current information.
     */
    void createNoLrcCurrentInfo();
    /*!
     * Show no lrc current information.
     */
    void showNoLrcCurrentInfo();
    /*!
     * Init current lrc when the first show.
     */
    void initCurrentLrc(const QString &str);
    /*!
     * Set per lrc line style sheet.
     */
    void setItemStyleSheet();
    /*!
     * Set per lrc line style sheet by index and size and transparent.
     */
    void setItemStyleSheet(int index, int size, int transparent);
    /*!
     * Map lrc size property to line index.
     */
    int mapLrcSizeProperty(int size);
    /*!
     * Set current lrc size property.
     */
    void setLrcSizeProperty(int property);
    /*!
     * Resize width bound by given width.
     */
    void resizeWidth(int w, int h);

    QPoint m_mousePressedAt;
    bool m_mouseLeftPressed, m_lrcChangeState, m_mouseMoved;
    int m_lrcChangeOffset, m_lrcChangeDelta;

    bool m_lrcDisplayAll, m_showArtistBackground;
    int m_animationFreshTime, m_lrcSizeProperty;

    qint64 m_changeSpeedValue;
    QWidget *m_functionLabel;
    MusicLrcFloatWidget *m_lrcFloatWidget;
    MusicLrcFloatPlayWidget *m_floatPlayWidget;
    MusicClickedLabel *m_noLrcCurrentInfo;
    MusicLrcCommentsWidget *m_commentsWidget;
    MusicLrcTranslatedWidget *m_translatedWidget;
    MusicVLayoutAnimationWidget *m_layoutWidget;

};

#endif // MUSICLRCCCONTAINERFORINTERIOR_H
