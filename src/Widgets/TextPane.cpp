#include "pch.hpp"

#include "Tools/Bible.hpp"
#include "Tools/WordChart.hpp"
#include "Widgets/TextPane.hpp"

TextPane::TextPane(const QString& title, const QVector<Tools::Bible>& bibles)
    : kdd::DockWidget(title)
    , bibles_(bibles)
{
    setupToolbar();
    setupTextArea();
    toggleAction();
    /*
    connect(new QShortcut(QKeySequence(Qt::MouseButton::MiddleButton), titleBar()), &QShortcut::activated,
            this, &kdd::DockWidget::close
            );
            */
}

void TextPane::createContextMenu(const QPoint& pnt) {
    auto* menu = text->createStandardContextMenu();
    QAction word_count("Count words", text);
    connect(&word_count, &QAction::triggered, [&] {
        auto* chart = new Tools::WordChart(text->textCursor().selectedText());
        chart->show();
    });
    menu->addAction(&word_count);

    menu->exec(mapToGlobal(pnt));
}

void TextPane::setupToolbar() {
    tools_ = new QToolBar("Tools");
    versions_ = new QComboBox(tools_);
    for (const auto& bible : bibles_) {
        versions_->addItem(bible.abbreviation().toUpper());
    }
    connect(versions_, SIGNAL(currentIndexChanged(int)), this, SLOT(switchVersions(int)));
    tools_->addWidget(versions_);

    layout()->addWidget(tools_);
}

void TextPane::setupTextArea() {
    text = new QTextEdit(this);
    text->setReadOnly(true);
    text->setContextMenuPolicy(Qt::CustomContextMenu);
    layout()->addWidget(text);
    connect(text, &QTextEdit::customContextMenuRequested, this, &TextPane::createContextMenu);
}

void TextPane::switchVersions(int index) {
    setTitle(bibles_[index].name());
}
