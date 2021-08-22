#ifndef MUSICAUDIORECORDERMODULE_H
#define MUSICAUDIORECORDERMODULE_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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
 ================================================= */

#include <QFile>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include "musicglobaldefine.h"

/*! @brief The class of the audio recorder core.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicAudioRecorderModule : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicAudioRecorderModule)
public:
    /*! @brief The class of the audio file wav header.
     * @author Greedysky <greedysky@163.com>
     */
    typedef struct TTK_MODULE_EXPORT WAVHEADER
    {
        char RIFFNAME[4];
        ulong RIFFLENGTH;
        char WAVNAME[4];
        char FMTNAME[4];
        ulong FMTLENGTH;
        ushort AUDIOFORMAT;
        ushort CHANNLENUMBER;
        ulong SAMPLERATE;
        ulong BYTESPERSECOND;
        ushort BYTESPERSAMPLE;
        ushort BITSPERSAMPLE;
        char DATANAME[4];
        ulong DATALENGTH;
    }WAVHEADER;

    /*!
     * Object contsructor.
     */
    explicit MusicAudioRecorderModule(QObject *parent = nullptr);
    ~MusicAudioRecorderModule();

    /*!
     * Add the header of wav.
     */
    int addWavHeader(const char *filename) const;

    /*!
     * Set volume by value.
     */
    void setVolume(int volume);
    /*!
     * Get volume by value.
     */
    int volume() const;

    /*!
     * Set output file name.
     */
    void setFileName(const QString &name);
    /*!
     * Get output file name.
     */
    QString getFileName() const;
    /*!
     * Current input device error or not.
     */
    bool error() const;

public Q_SLOTS:
    /*!
     * Recorder play start.
     */
    void onRecordStart();
    /*!
     * Recorder play stop.
     */
    void onRecordStop();
    /*!
     * Recorder play play.
     */
    void onRecordPlay();
    /*!
     * Recorder play state changed.
     */
    void onStateChange(QAudio::State state);

protected:
    int m_inputVolume;
    QFile *m_outputFile;
    QAudioFormat m_formatFile;
    QAudioInput *m_audioInputFile;
    QAudioOutput *m_audioOutputFile;

};

#endif // MUSICAUDIORECORDERMODULE_H
