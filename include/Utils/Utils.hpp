#ifndef QTBIBLE_UTILS_HPP
#define QTBIBLE_UTILS_HPP

#include <QStandardPaths>

namespace Utils {

    inline auto getCache() {
        return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    }

}

#endif //QTBIBLE_UTILS_HPP
