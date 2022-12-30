#ifndef QTBIBLE_BIBLE_HPP
#define QTBIBLE_BIBLE_HPP

#include <QObject>
#include <QString>

namespace Tools {

    class Bible : public QObject {
    Q_OBJECT
    public:
        Bible(QString name,
              QString id,
              QString abbreviation,
              QString description,
              QString language);

        Bible(const Bible& b);

        Bible& operator=(const Bible& b);

        bool operator<(const Bible& b);

        [[nodiscard]] auto name()           const { return name_; }
        [[nodiscard]] auto id()             const { return id_; }
        [[nodiscard]] auto abbreviation()   const { return abbreviation_; }
        [[nodiscard]] auto description()    const { return description_; }
        [[nodiscard]] auto language()       const { return language_; }

    private:
        QString name_;
        QString id_;
        QString abbreviation_;
        QString description_;
        QString language_;
    };

} // Tools

#endif //QTBIBLE_BIBLE_HPP
