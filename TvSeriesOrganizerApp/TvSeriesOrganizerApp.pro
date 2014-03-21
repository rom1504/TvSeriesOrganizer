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


QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc \
    ../GeneralQmlItems/GeneralQmlItemsResources.qrc


OTHER_FILES += android/AndroidManifest.xml

QT+= xml


INCLUDEPATH += $$PWD/../GeneralQmlItems
DEPENDPATH += $$PWD/../GeneralQmlItems

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


TRANSLATIONS += translations/TvSeriesOrganizer_fr.ts
TRANSLATIONS += translations/TvSeriesOrganizer_en.ts

lupdate_only{
SOURCES = view/Episode.qml \
    view/EpisodeDetails.qml \
    view/SeasonDetails.qml \
    view/Season.qml \
    view/SeriesDetails.qml \
    view/Series.qml \
    view/SeriesList.qml \
    view/SeenIndicator.qml \
    view/MainView.qml \
    view/ListPage.qml \
    view/SimplePage.qml \
    view/TabItem.qml \
    view/TabPage.qml \
    view/SeriesSearch.qml \
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SignalList/release/ -lSignalList
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SignalList/debug/ -lSignalList
else:unix: LIBS += -L$$OUT_PWD/../SignalList/ -lSignalList

INCLUDEPATH += $$PWD/../SignalList/source
DEPENDPATH += $$PWD/../SignalList/source

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SignalList/release/libSignalList.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SignalList/debug/libSignalList.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SignalList/release/SignalList.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SignalList/debug/SignalList.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../SignalList/libSignalList.a
