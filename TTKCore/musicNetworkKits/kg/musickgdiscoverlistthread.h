#ifndef MUSICKGDISCOVERLISTTHREAD_H
#define MUSICKGDISCOVERLISTTHREAD_H

#include "MusicDownLoadDiscoverListThread.h"

/*! @brief The class to kugou discover toplist.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_NETWORK_EXPORT MusicKGDiscoverListThread : public MusicDownLoadDiscoverListThread
{
    Q_OBJECT
public:
    explicit MusicKGDiscoverListThread(QObject *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */
    virtual void startToSearch() override;
    /*!
     * Start to Search data from toplist.
     */

public Q_SLOTS:
    virtual void downLoadFinished() override;
    /*!
     * Download data from net finished.
     */

};

#endif // MUSICKGDISCOVERLISTTHREAD_H
