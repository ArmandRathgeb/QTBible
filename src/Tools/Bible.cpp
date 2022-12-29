#include "pch.hpp"

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
{

}

Bible& Bible::operator=(const Bible& b) {
    name_           = b.name_;
    id_             = b.id_;
    abbreviation_   = b.abbreviation_;
    description_    = b.description_;
    language_       = b.language_;

    return *this;
}