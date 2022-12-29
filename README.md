# QTBible
A desktop app built with QT5 to add tools to help you study the Bible
Highly WIP, hopefully will be using api.bible for translations.

## Libraries
- QT5
- KDDockWidgets
- QT5 Charts

## Building
``` 
git clone https://github.com/ArmandRathgeb/QTBible.git
mkdir QTBible/build && cd QTBible/build
cmake -DAPI_KEY[Your api.bible api key] ..
cmake --build .
```