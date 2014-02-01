# Add more folders to ship with the application, here
folder_01.source = qml/DownloaderInterface
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    model/serie.cpp \
    model/season.cpp \
    model/episode.cpp \
    adapter/episodesignallistadapter.cpp \
    controller/controller.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    model/serie.h \
    model/season.h \
    model/episode.h \
    adapter/episodesignallistadapter.h \
    controller/controller.h

unix:!macx: LIBS += -L$$OUT_PWD/../SignalList/ -lSignalList

INCLUDEPATH += $$PWD/../SignalList/source
DEPENDPATH += $$PWD/../SignalList/source

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../SignalList/libSignalList.a


QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    ressources.qrc

OTHER_FILES += \
    qml/DownloaderInterface/Episode.qml \
    qml/DownloaderInterface/SeasonDetails.qml
