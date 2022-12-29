#include "pch.hpp"

#include "Tools/WordChart.hpp"
#include "Widgets/TextPane.hpp"

TextPane::TextPane(const QString& title)
    : kdd::DockWidget(title)
{
    text = new QTextEdit(this);
    text->setReadOnly(true);
    text->setContextMenuPolicy(Qt::CustomContextMenu);
    setWidget(text);
    text->setText("<b>ARG</b>,  kys;!kys");
    connect(text, &QTextEdit::customContextMenuRequested, this, &TextPane::createContextMenu);
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
