#ifndef MUSICDOWNLOADQUERYQQARTISTTHREAD_H
#define MUSICDOWNLOADQUERYQQARTISTTHREAD_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicdownloadqqinterface.h"
#include "musicdownloadquerythreadabstract.h"

/*! @brief The class to qq query artist download data from net.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_NETWORK_EXPORT MusicDownLoadQueryQQArtistThread : public MusicDownLoadQueryThreadAbstract,
                                                              private MusicDownLoadQQInterface
{
    Q_OBJECT
public:
    explicit MusicDownLoadQueryQQArtistThread(QObject *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */

    virtual void startToSearch(QueryType type, const QString &artist) override;
    /*!
     * Start to Search data from name and type.
     */
    void startToSearch(const QString &artist);
    /*!
     * Start to Search data from name and type.
     */

public Q_SLOTS:
    virtual void downLoadFinished() override;
    /*!
     * Download data from net finished.
     */

};

#endif // MUSICDOWNLOADQUERYQQARTISTTHREAD_H
