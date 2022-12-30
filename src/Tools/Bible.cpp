#include "pch.hpp"

#include "Utils/Download.hpp"
#include "Tools/Bible.hpp"

using namespace Tools;

Bible::Bible(QString name,
             QString id,
             QString abbreviation,
             QString description,
             QString language)
    : name_{std::move(name)}
    , id_{std::move(id)}
    , abbreviation_{std::move(abbreviation)}
    , description_{std::move(description)}
    , language_{std::move(language)}
    , download_{ new Utils::Download() }
{
    setupConnections();
}

Bible::Bible(const Bible& b)
    : name_{b.name_}
    , id_{b.id_}
    , abbreviation_{b.abbreviation_}
    , description_{b.abbreviation_}
    , language_{b.language_}
    , download_{ b.download_ }
{
    setupConnections();
}

Bible& Bible::operator=(const Bible& b) {
    name_           = b.name_;
    id_             = b.id_;
    abbreviation_   = b.abbreviation_;
    description_    = b.description_;
    language_       = b.language_;
    download_       = b.download_;

    return *this;
}

bool Bible::operator<(const Bible& b) {
    return QString::compare(abbreviation_, b.abbreviation_, Qt::CaseInsensitive) < 0;
}

void Bible::getVerse(const QString& verseID) {
    download_->startDownload(QUrl(QString(VERSE_HEADER).arg(id_, verseID)));
}

void Bible::setupConnections() {
    connect(download_, &Utils::Download::downloaded, [&]{
        emit verse(download_->getData());
    });
}