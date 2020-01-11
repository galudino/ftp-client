#ifndef FTPGETTER_H
#define FTPGETTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QFile>
#include <QUrl>

#include <QWidget>

namespace ntwk {
    class FTPGetter;
}

class ntwk::FTPGetter : public QObject {
    Q_OBJECT

public:
    explicit FTPGetter(QObject *parent = nullptr);
    ~FTPGetter();


private:
    QNetworkAccessManager manager;
    QFile file;
};

#endif // FTPGETTER_H
