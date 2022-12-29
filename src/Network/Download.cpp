#include "pch.hpp"

#include "Network/Download.hpp"

using namespace Network;

Download::Download(const QUrl& name, QObject* parent)
    : QObject(parent)
{
    QNetworkRequest request{name};
    request.setRawHeader("api-key", API_KEY);
    webctrl_.get(request);
    connect(
            &webctrl_,
            &QNetworkAccessManager::finished,
            [&](auto* ptr) {
                data_ = ptr->readAll();
                ptr->deleteLater();
                emit downloaded();
            }
    );

    connect(
            &webctrl_,
            &QNetworkAccessManager::sslErrors,
            [&](auto* reply, const auto& errors) {
                for (const auto& error : errors) {
                    qWarning() << error.errorString();
                }
                emit error();
            }
    );
}
