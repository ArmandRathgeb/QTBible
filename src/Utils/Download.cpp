#include "pch.hpp"

#include "Utils/Download.hpp"

using namespace Utils;

Download::Download(QObject* parent)
    : QObject(parent)
{
    setupConnections();
}


Download::Download(const QUrl& url, QObject* parent)
    : QObject(parent)
{
    setupConnections();
    startDownload(url);
}

void Download::startDownload(const QUrl& url) {
    QNetworkRequest request{url};
    request.setRawHeader("api-key", API_KEY);
    webctrl_.get(request);
}

void Download::setupConnections() {
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
