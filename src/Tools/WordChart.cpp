#include <qt6/QtCharts/QChart>
#include "pch.hpp"

#include "Tools/WordChart.hpp"

using namespace Tools;

WordChart::WordChart(QString passage, QWidget* parent)
    : QWidget(parent)
    , histogram(nullptr)
    , pie(nullptr)
    , tabs(nullptr)
{
    setWindowTitle(tr("Word count"));
    auto* vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);
    tabs = new QTabWidget(this);
    tabs->setTabShape(QTabWidget::Rounded);

    passage_words = passage.split(QRegularExpression("[^a-zA-Z0-9 ]| "), Qt::SkipEmptyParts);
    counted = countWords(passage_words);

    {
        auto* chart = new QtCharts::QChart();
        auto* series = new QtCharts::QBarSeries();
        for (const auto& [str, cnt] : counted) {
            auto* set = new QtCharts::QBarSet(str);
            *set << cnt;
            series->append(set);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setAnimationOptions(QtCharts::QChart::AllAnimations);
        tabs->addTab(createChart(*chart, histogram, *tabs), "Histogram");
    }
    {
        auto* chart = new QtCharts::QChart();
        auto* series = new QtCharts::QPieSeries();
        for (const auto& [str, cnt] : counted) {
            series->append(str, cnt);
        }
        chart->addSeries(series);
        chart->setAnimationOptions(QtCharts::QChart::AllAnimations);
        tabs->addTab(createChart(*chart, pie, *tabs), "Pie Chart");
    }
    {
        auto* filters = new QWidget(tabs);

        tabs->addTab(filters, "Filters");
    }

    vbox->addWidget(tabs);
    setLayout(vbox);
    resize(420, 300);
}

QWidget* WordChart::createChart(QtCharts::QChart& chart, QtCharts::QChartView* view, QWidget& parent) {
    auto* page = new QWidget(&parent);
    auto* ivbox = new QVBoxLayout(page);
    view = new QtCharts::QChartView(&chart);
    view->setRenderHint(QPainter::Antialiasing);
    ivbox->addWidget(view);

    page->setLayout(ivbox);
    return page;
}

QVector<std::pair<QString, int>> WordChart::countWords(QStringList& words) {
    QVector<std::pair<QString, int>> count;
    std::sort(words.begin(), words.end());
    for (const auto& word : words) {
        bool contained = false;
        for (auto& pair : count) {
            if (QString::compare(word, pair.first, Qt::CaseInsensitive) == 0) {
                pair.second++;
                contained = true;
                break;
            }
        }
        //std::binary_search(count.begin(), count.end(), word, [](std::pair<QString, int> wor, QString p) {
            //return !(QString::compare(wor.first, p, Qt::CaseInsensitive));
        //});
        if (not contained) {
            count.push_back({word, 1});
        }
    }

    return count;
}
