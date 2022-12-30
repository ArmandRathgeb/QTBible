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

#   ifndef API_KEY
#       error "You must define an API key!"
#   endif // API_KEY

#endif // PCH
