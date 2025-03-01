#ifndef MUSICSOUNDEFFECTSWIDGET_H
#define MUSICSOUNDEFFECTSWIDGET_H

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

#include "musicabstractmovedialog.h"

namespace Ui {
class MusicSoundEffectsWidget;
}

/*! @brief The class of the sound effect item widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicSoundEffectsItemWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicSoundEffectsItemWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSoundEffectsItemWidget(const QString &name, QWidget *parent = nullptr);
    ~MusicSoundEffectsItemWidget();

    /*!
     * Get plugin module name.
     */
    inline QString name() const { return m_type; }
    /*!
     * Set plugin enable or not.
     */
    void setPluginEnabled(bool enable);
    /*!
     * Get plugin enable or not.
     */
    bool pluginEnabled() const;

    /*!
     * Sound effect changed.
     */
    static void soundEffectChanged(const QString &name, bool enable);

public Q_SLOTS:
    /*!
     * Set plugin enable or not.
     */
    void setPluginEnabled();
    /*!
     * Sound effect button value changed.
     */
    void soundEffectValueChanged();

protected:
    QString m_type;
    bool m_enable;
    QLabel *m_textLabel;
    QPushButton *m_settingButton, *m_openButton;

};


/*! @brief The class of the sound effect widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicSoundEffectsWidget : public MusicAbstractMoveDialog
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicSoundEffectsWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSoundEffectsWidget(QWidget *parent = nullptr);
    ~MusicSoundEffectsWidget();

    /*!
     * Set input connection.
     */
    void setInputModule(QObject *object);

Q_SIGNALS:
    /*!
     * Read equalizer effect from config file.
     */
    void setEqInformation();

public Q_SLOTS:
    /*!
     * Equalizer button state changed.
     */
    void equalizerButtonChanged(bool state);
    /*!
     * Equalizer button state changed.
     */
    void equalizerButtonChanged();
    /*!
     * State combobox index changed.
     */
    void stateComboBoxChanged(int index);
    /*!
     * Override exec function.
     */
    virtual int exec();

protected:
    /*!
     * Read sound effect function.
     */
    void readSoundEffect();
    /*!
     * Write sound effect function.
     */
    void writeSoundEffect();

    Ui::MusicSoundEffectsWidget *m_ui;
    QList<MusicSoundEffectsItemWidget*> m_items;

};

#endif // MUSICSOUNDEFFECTSWIDGET_H
