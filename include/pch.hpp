#ifndef PCH
#define PCH

#include <sstream>
#include <utility>
#include <algorithm>

#include <QStringView>
#include <QApplication>
#include <QMainWindow>
#include <QFrame>
#include <QSplashScreen>
#include <QRegularExpression>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QToolBar>
#include <QShortcut>
#include <QSettings>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QChart>
#include <QBarSet>
#include <QChartView>
#include <QBarSeries>
#include <QPieSeries>

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
namespace kdd = KDDockWidgets;

#include "config.hpp"

constexpr auto VERSION_HEADER = "https://api.scripture.api.bible/v1/bibles";
constexpr auto VERSIONS_FILE = "versions.json";
constexpr auto BOOKS_HEADER = "https://api.scripture.api.bible/v1/bibles/%1/books";
constexpr auto CHAPTER_HEADER = "https://api.scripture.api.bible/v1/bibles/%1/books/%2/chapters";
constexpr auto ALL_VERSES = "";
constexpr auto VERSE_HEADER= "https://api.scripture.api.bible/v1/bibles/%1/verses/%2?include-chapter-numbers=false&include-verse-numbers=false;";
constexpr auto SEARCH_QUERY = "https://api.scripture.api.bible/v1/bibles/%1/search?query=%2&offset=%3";

#   ifndef API_KEY
#       error "You must define an API key!"
#   endif // API_KEY

#endif // PCH
