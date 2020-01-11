#include "downloader.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>

#include <QDebug>

using ntwk::Downloader;

QString ntwk::DownloadPath = "";

/**
 * @brief Downloader::Downloader
 * @param parent
 */
Downloader::Downloader(QObject *parent) {
    Q_UNUSED(parent)

    manager = new QNetworkAccessManager(this);

    connect(manager,
            SIGNAL(finished(QNetworkReply *)),
            this,
            SLOT(replyFinished(QNetworkReply *)));
}

/**
 * @brief Downloader::~Downloader
 */
Downloader::~Downloader() {
    delete manager;
}

/**
 * @brief Downloader::doDownload
 * @param urlStr
 */
void Downloader::doDownload(QString urlStr) {
    manager->get(QNetworkRequest(QUrl(urlStr)));
}

/**
 * @brief Downloader::replyFinished
 * @param reply
 */
void Downloader::replyFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "[ERROR]" << reply->errorString();
    } else {
        qDebug() << "*********************************************************";
        qDebug() << "ContentTypeHeader:\t\t"
                 << reply->header(QNetworkRequest::ContentTypeHeader).toString();

        qDebug() << "LastModifierHeader:\t\t"
                 << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();

        qDebug() << "ContentLengthHeader:\t\t"
                 << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();

        qDebug() << "HttpStatusCodeAttribute:\t"
                 << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        qDebug() << "HttpReasonPhraseAttribute:\t"
                 << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << "*********************************************************";

        QFile file(DownloadPath);

        if (file.open(QIODevice::ReadWrite)) {
            QTextStream fos(&file);
            fos << reply->readAll();

            file.flush();
            file.close();

            qDebug() << "[SUCCESS]"
                     << ntwk::DownloadPath << "successfully written";
        } else {
            qDebug() << "[ERROR]" << "file.open() failed";
        }
    }

    reply->deleteLater();
}
