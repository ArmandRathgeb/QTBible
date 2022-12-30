#ifndef QTBIBLE_DOWNLOAD_HPP
#define QTBIBLE_DOWNLOAD_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Utils {

    class Download final : public QObject {
    Q_OBJECT
    public:
        Download(QObject* parent = nullptr);

        explicit Download(const QUrl& url, QObject* parent = nullptr);

        [[nodiscard]] inline auto getData() const { return data_; }

    public slots:
        void startDownload(const QUrl& url);

    signals:
        void downloaded();
        void error();

    private:
        void setupConnections();

        QNetworkAccessManager webctrl_;
        QByteArray data_;
    };

}

#endif //QTBIBLE_DOWNLOAD_HPP
