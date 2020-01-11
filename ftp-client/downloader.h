#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

namespace ntwk {
    class Downloader;
    extern QString DownloadPath;
}

/**
 * @brief The ntwk::Downloader class
 */
class ntwk::Downloader : public QObject {
    Q_OBJECT

public:
    explicit Downloader(QObject *parent = nullptr);
    ~Downloader();

    void doDownload(QString urlStr);

public slots:
    void replyFinished(QNetworkReply *reply);

signals:

private:
    QNetworkAccessManager *manager;
};


#endif // DOWNLOADER_H

