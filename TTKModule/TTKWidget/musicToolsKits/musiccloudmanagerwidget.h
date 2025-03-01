#ifndef MUSICCLOUDMANAGERWIDGET_H
#define MUSICCLOUDMANAGERWIDGET_H

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
#include "musicclouddataitem.h"
#include "musicabstracttablewidget.h"

class QSyncListData;
class QSyncDeleteData;
class QSyncUploadData;
class QSyncDownloadData;
class MusicOpenFileWidget;
class MusicProgressBarDelegate;
class QNetworkAccessManager;

/*! @brief The class of the cloud shared song table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicCloudManagerTableWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicCloudManagerTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicCloudManagerTableWidget(QWidget *parent = nullptr);
    ~MusicCloudManagerTableWidget();

    /*!
     * Get query cloud id keys.
     */
    bool queryCloudKey();
    /*!
     * Resize window bound by widget resize called.
     */
    void resizeWindow();

Q_SIGNALS:
    /*!
     * To update message label text.
     */
    void updateLabelMessage(const QString &text);
    /*!
     * Update size label.
     */
    void updataSizeLabel(qint64 size);
    /*!
     * Get key data from net finished.
     */
    void finished();
    /*!
     * Upload file error occurred.
     */
    void uploadFileError(const MusicCloudDataItem &item);

public Q_SLOTS:
    /*!
     * Table widget item cell click.
     */
    virtual void itemCellClicked(int row, int column) override final;
    /*!
     * Send recieved data from net.
     */
    void downLoadFinished(const QByteArray &bytes);
    /*!
     * Receive data from sync finshed.
     */
    void receiveDataFinshed(const QSyncDataItems &items);
    /*!
     * Upload data to sync finshed.
     */
    void uploadFileFinished(const QString &time);
    /*!
     * Delete data to sync finshed.
     */
    void deleteFileFinished(bool state);

    /*!
     * Update list to server.
     */
    void updateListToServer();
    /*!
     * Delete file to server.
     */
    void deleteFileToServer();
    /*!
     * Delete files to server.
     */
    void deleteFilesToServer();
    /*!
     * Download file to server.
     */
    void downloadFileToServer();

    /*!
     * Cancel upload files to server.
     */
    void cancelUploadFilesToServer();
    /*!
     * Upload files to server.
     */
    void uploadFilesToServer();
    /*!
     * Upload file dir to server.
     */
    void uploadFileDirToServer();
    /*!
     * Reupload files to server.
     */
    void reuploadFilesToServer(const QStringList &items);

    /*!
     * Show upload progress.
     */
    void uploadProgress(const QString &time, qint64 bytesSent, qint64 bytesTotal);
    /*!
     * All files upload finsihed.
     */
    void uploadDone();
    /*!
     * Show file information widget.
     */
    void showFileInformationWidget();

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    /*!
     * Upload files to server.
     */
    void uploadFilesToServer(const QStringList &paths);
    /*!
     * Create upload file module.
     */
    void createUploadFileModule();
    /*!
     * Start to upload files to server.
     */
    void startToUploadFile();
    /*!
     * Create table item.
     */
    void createItem(const MusicCloudDataItem &data);
    /*!
     * Find upload item row.
     */
    int FindUploadItemRow(const QString &time) const;
    /*!
     * Find waited item row.
     */
    MusicCloudDataItem FindWaitedItemRow() const;

    bool m_uploading;
    bool m_cancel;
    qint64 m_totalFileSzie;
    QSyncListData *m_syncListData;
    QSyncDeleteData *m_syncDeleteData;
    QSyncUploadData *m_syncUploadData;
    QSyncDownloadData *m_syncDownloadData;
    QNetworkAccessManager *m_manager;
    MusicOpenFileWidget *m_openFileWidget;
    MusicCloudDataItem m_currentDataItem;
    MusicProgressBarDelegate *m_progressBarDelegate;

};



/*! @brief The class of the cloud manager widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicCloudManagerWidget : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicCloudManagerWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicCloudManagerWidget(QWidget *parent = nullptr);
    ~MusicCloudManagerWidget();

    /*!
     * Resize window bound by widget resize called.
     */
    virtual void resizeWindow();

public Q_SLOTS:
    /*!
     * Update size label.
     */
    void updataSizeLabel(qint64 size);
    /*!
     * Download file to server.
     */
    void downloadFileToServer();
    /*!
     * Delete file to server.
     */
    void deleteFileToServer();
    /*!
     * Upload files to server.
     */
    void uploadFilesToServer();

protected:
    /*!
     * Override the widget event.
     */
    virtual void resizeEvent(QResizeEvent *event) override final;

protected:
    QLabel *m_sizeValueLabel;
    QProgressBar *m_sizeValueBar;
    QList<QWidget*> m_resizeWidgets;
    MusicCloudManagerTableWidget *m_managerTableWidget;

};

#endif // MUSICCLOUDMANAGERWIDGET_H
