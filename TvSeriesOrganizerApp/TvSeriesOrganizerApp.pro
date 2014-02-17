# Add more folders to ship with the application, here

DEPLOYMENTFOLDERS =

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

TARGET = TvSeriesOrganizer

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    model/season.cpp \
    model/episode.cpp \
    controller/controller.cpp \
    model/series.cpp \
    model/serieslist.cpp \
    model/qqmlnetworkaccessmanagerfactorywithcache.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    model/season.h \
    model/episode.h \
    controller/controller.h \
    model/series.h \
    model/serieslist.h \
    model/qqmlnetworkaccessmanagerfactorywithcache.h

unix:!macx: LIBS += -L$$OUT_PWD/../SignalList/ -lSignalList

INCLUDEPATH += $$PWD/../SignalList/source
DEPENDPATH += $$PWD/../SignalList/source

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../SignalList/libSignalList.a


QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    ressources.qrc

OTHER_FILES += \
    view/Episode.qml \
    view/EpisodeDetails.qml \
    view/SeasonDetails.qml \
    view/Season.qml \
    view/SeriesDetails.qml \
    view/ShadowBorderRectangle.qml \
    view/Series.qml \
    view/SeriesList.qml \
    view/SimplePage.qml \
    view/ListPage.qml \
    view/ShadowBorderRectangleText.qml \
    view/TitleImageDescriptionItem.qml \
    view/TabPage.qml \
    view/TabItem.qml \
    view/Title.qml \
    view/Description.qml \
    view/Button.qml \
    view/LineInput.qml

QT+= xml
