#ifndef MUSICLOCALSONGSEARCH_H
#define MUSICLOCALSONGSEARCH_H

/* =================================================
 * This file is part of the Music Player project
 * Copyright (c) 2014 - 2015 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QtWidgets>
#include "musiclibexportglobal.h"

class MusicLocalSongSearchEdit;

class MUSIC_WIDGET_EXPORT MusicLocalSongSearch : public QDialog
{
    Q_OBJECT
public:
    explicit MusicLocalSongSearch(QWidget *parent = 0);
    ~MusicLocalSongSearch();

    QString getSearchedText() const;
    void clearSearchedText() const;

private:
    QLabel *m_showIcon;
    MusicLocalSongSearchEdit *m_searchLine;
    QToolButton *m_closeButton;

};

#endif // MUSICLOCALSONGSEARCH_H
