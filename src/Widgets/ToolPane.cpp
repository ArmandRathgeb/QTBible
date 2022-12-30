#include "pch.hpp"

#include "Widgets/ToolPane.hpp"

ToolPane::ToolPane()
    : kdd::DockWidget(tr("Tools"), kdd::DockWidget::Option_NotClosable)
{
    auto* grid = new QGridLayout();
    grid->setContentsMargins(4, 4, 4, 4);

    versions_box = new QComboBox(this);
    grid->addWidget(versions_box, 1, 1);

    layout()->addItem(grid);
}

void ToolPane::insertVersion(const QString& version) {
    versions_box->addItem(version);
}
