#include "pch.hpp"

#include "Dialogs/Settings.hpp"
#include "Network/Download.hpp"
#include "Tools/WordChart.hpp"
#include "Widgets/TextPane.hpp"
#include "MainDisplay.hpp"

MainDisplay::MainDisplay()
    : kdd::MainWindow("QTBible", kdd::MainWindowOption_HasCentralFrame)
    , down(QUrl(VERSION_HEADER), this)
    , settings_()
    , toolbar(nullptr)
    , showMenu(nullptr)
    , quit(nullptr)
    , settings_menu(nullptr)
{
    QMainWindow::showMaximized();
    QMainWindow::setWindowTitle("QTBible");

    qDebug() << "Loading";
    createMenus();
    createToolbars();
    createShortcuts();
    loadVersions();
    loadSettings();

    {
        auto tx = new TextPane(tr("ASV"));
        addDockWidget(tx, kdd::Location_OnLeft);
        tools_ = new ToolPane();
        addDockWidget(tools_, kdd::Location_OnRight);
        addDockWidgetAsTab(tx);
    }
}

MainDisplay::~MainDisplay() {
    writeSettings();
    writeVersions();
}

void MainDisplay::showSettings() {
    Settings(this).exec();
}

void MainDisplay::createMenus() {
    settings_menu = new QAction(QIcon::fromTheme("settings"), "&Settings", this);
    showMenu = new QAction("&Show menu", this);
    showMenu->setCheckable(true);
    quit = new QAction(QIcon::fromTheme("exit"), "&Quit", this);

    auto* file = menuBar()->addMenu("&File");
    file->addAction(settings_menu);
    file->addAction(showMenu);
    file->addAction(quit);

    connect(settings_menu, &QAction::triggered, this, &MainDisplay::showSettings);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(showMenu, &QAction::triggered, [&] {
        auto val = showMenu->isChecked();
        menuBar()->setVisible(val);
        settings_.setValue("MainWindow/ShowMenuBar", val);
    });

}

void MainDisplay::createToolbars() {
    toolbar = addToolBar("Main");

    toolbar->addAction(quit);
    toolbar->addAction(settings_menu);
    toolbar->addSeparator();

}

void MainDisplay::createShortcuts() {
    using QSS = QShortcut;
    using QKS = QKeySequence;
    connect(new QSS(QKS("CTRL+Q"), this), &QShortcut::activated, qApp, &QApplication::quit);
    connect(new QSS(QKS("CTRL+ALT+S"), this), &QShortcut::activated, this, &MainDisplay::showSettings);
}

void MainDisplay::loadVersions() {
    auto versions_file = QFile(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + VERSIONS_FILE);
    if (versions_file.exists()) {
        versions_file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray data = versions_file.readAll();
        readVersionsFromJson(QJsonDocument::fromJson(data));
    } else {
        connect(
                &down,
                &Network::Download::downloaded,
                [&] {
                    QJsonDocument doc = QJsonDocument::fromJson(down.getData());
                    readVersionsFromJson(doc);
                }
        );
        connect(
                &down,
                &Network::Download::error,
                [&] {
                    qWarning() << "Failed to get versions!";
                }
        );
    }
}

void MainDisplay::readVersionsFromJson(const QJsonDocument& doc) {
    const auto obj = doc.object();
    if (!obj.contains("title") || !obj.contains("description")) {
#ifdef NDEBUG
        qFatal("Versions malformed");
#else
        qWarning() << "Versions malformed";
        return;
#endif
    }
    auto titles = obj["title"].toArray();
    auto descriptions = obj["description"].toArray();
    version_descriptions.clear();
    version_descriptions.reserve(descriptions.size());

    assert(titles.size() == descriptions.size());
    for (int i = 0; i < titles.size(); ++i) {
        version_descriptions[i] = std::move(descriptions[i].toString());
    }
}

void MainDisplay::writeVersions() {

}

void MainDisplay::loadSettings() {
    auto checked = settings_.value("MainWindow/ShowMenuBar").toBool();
    menuBar()->setVisible(checked);
    showMenu->setChecked(checked);
}

void MainDisplay::writeSettings() {

}

#ifndef Q_OS_MAC
void MainDisplay::keyReleaseEvent(QKeyEvent* evt) {
    if (evt->key() == Qt::Key_Alt && !settings_.value("MainWindow/ShowMenuBar").toBool()) {
        menuBar()->setVisible(!menuBar()->isVisible());
    } else {
        QMainWindow::keyReleaseEvent(evt);
    }
}
#endif

