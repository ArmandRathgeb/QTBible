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
    qDebug() << "Started parsing versions";
    for (const auto& value : doc.object()["data"].toArray()) {
        const auto& obj = value.toObject();
        bibles_.push_back({
            obj["name"].toString(),
            obj["id"].toString(),
            obj["abbreviation"].toString(),
            obj["description"].toString(),
            obj["language"].toString()
        });
    }
    std::sort(bibles_.begin(), bibles_.end());
    for (const auto& bible : bibles_) {
        tools_->insertVersion(bible.abbreviation().toUpper());
    }
    qDebug() << "Parsed " << bibles_.size() << " versions";
}

void MainDisplay::writeVersions() {
    for (const auto& bible : bibles_) {

    }
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

