#include <QtQml>

#include "settings.h"

#define defaultSeriesCollectionStyle CollectionViewStyle::GridView
#define defaultSeriesCardType CardType::LargeCard
#define defaultSeasonCollectionStyle CollectionViewStyle::GridView
#define defaultEpisodeCollectionStyle CollectionViewStyle::GridView

Settings::Settings(QObject *parent) :
    QObject(parent),mSettings("rom1504","TvSeriesOrganizer")
{
    mSeriesCollectionStyle=CollectionViewStyle(mSettings.value("seriesCollectionStyle",int(defaultSeriesCollectionStyle)).toInt());
    mSeriesCardType=CardType(mSettings.value("seriesCardType",int(defaultSeriesCardType)).toInt());
    mSeasonCollectionStyle=CollectionViewStyle(mSettings.value("seasonCollectionStyle",int(defaultSeasonCollectionStyle)).toInt());
    mEpisodeCollectionStyle=CollectionViewStyle(mSettings.value("episodeCollectionStyle",int(defaultEpisodeCollectionStyle)).toInt());
}


Settings::CollectionViewStyle Settings::seriesCollectionStyle() const
{
    return mSeriesCollectionStyle;
}

void Settings::setSeriesCollectionStyle(Settings::CollectionViewStyle seriesCollectionStyle)
{
    mSeriesCollectionStyle=seriesCollectionStyle;
    mSettings.setValue("seriesCollectionStyle",int(mSeriesCollectionStyle));
    emit seriesCollectionStyleChanged();
}


Settings::CardType Settings::seriesCardType() const
{
    return mSeriesCardType;
}

void Settings::setSeriesCardType(Settings::CardType seriesCardType)
{
    mSeriesCardType=seriesCardType;
    mSettings.setValue("seriesCardType",int(mSeriesCardType));
    emit seriesCardTypeChanged();
}

Settings::CollectionViewStyle Settings::seasonCollectionStyle() const
{
    return mSeasonCollectionStyle;
}

void Settings::setSeasonCollectionStyle(Settings::CollectionViewStyle seasonCollectionStyle)
{
    mSeasonCollectionStyle=seasonCollectionStyle;
    mSettings.setValue("seasonCollectionStyle",int(mSeasonCollectionStyle));
    emit seasonCollectionStyleChanged();
}

Settings::CollectionViewStyle Settings::episodeCollectionStyle() const
{
    return mEpisodeCollectionStyle;
}

void Settings::setEpisodeCollectionStyle(Settings::CollectionViewStyle episodeCollectionStyle)
{
    mEpisodeCollectionStyle=episodeCollectionStyle;
    mSettings.setValue("episodeCollectionStyle",int(mEpisodeCollectionStyle));
    emit episodeCollectionStyleChanged();
}

void Settings::declareSettingsQml()
{
    qmlRegisterType<Settings>("com.rom1504.TvSeriesOrganizer", 1, 0, "SettingsModel");
}
