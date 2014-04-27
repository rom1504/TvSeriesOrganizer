#include <QtQml>

#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent),mSettings("rom1504","TvSeriesOrganizer")
{
    mSeriesCollectionStyle=SeriesCollectionStyle(mSettings.value("seriesCollectionStyle",int(SeriesCollectionStyle::SeriesGrid)).toInt());
}


Settings::SeriesCollectionStyle Settings::seriesCollectionStyle() const
{
    return mSeriesCollectionStyle;
}

void Settings::setSeriesCollectionStyle(Settings::SeriesCollectionStyle seriesCollectionStyle)
{
    mSeriesCollectionStyle=seriesCollectionStyle;
    mSettings.setValue("seriesCollectionStyle",int(mSeriesCollectionStyle));
    emit seriesCollectionStyleChanged();
}


void Settings::declareSettingsQml()
{
    qmlRegisterType<Settings>("com.rom1504.TvSeriesOrganizer", 1, 0, "SettingsModel");
}
