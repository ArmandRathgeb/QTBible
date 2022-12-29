#ifndef QTBIBLE_DOWNLOAD_HPP
#define QTBIBLE_DOWNLOAD_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Network {

    class Download final : public QObject {
    Q_OBJECT
    public:
        explicit Download(const QUrl& name, QObject* parent = nullptr);

        ~Download() override = default;

        [[nodiscard]] inline auto getData() const { return data_; }

    signals:
        void downloaded();
        void error();

    private:
        QNetworkAccessManager webctrl_;
        QByteArray data_;
    };

}

#endif //QTBIBLE_DOWNLOAD_HPP
