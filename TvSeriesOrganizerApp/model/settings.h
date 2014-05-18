#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(CollectionViewStyle)
    Q_ENUMS(CardType)
    Q_PROPERTY(CollectionViewStyle seriesCollectionStyle READ seriesCollectionStyle WRITE setSeriesCollectionStyle NOTIFY seriesCollectionStyleChanged)
    Q_PROPERTY(CardType seriesCardType READ seriesCardType WRITE setSeriesCardType NOTIFY seriesCardTypeChanged)
    Q_PROPERTY(CollectionViewStyle seasonCollectionStyle READ seasonCollectionStyle WRITE setSeasonCollectionStyle NOTIFY seasonCollectionStyleChanged)
    Q_PROPERTY(CollectionViewStyle episodeCollectionStyle READ episodeCollectionStyle WRITE setEpisodeCollectionStyle NOTIFY episodeCollectionStyleChanged)

public:
    enum CollectionViewStyle
    {
         ListView,
         GridView
    };

    enum CardType
    {
        SmallCard,
        LargeCard
    };

    explicit Settings(QObject *parent = 0);

    CollectionViewStyle seriesCollectionStyle() const;
    void setSeriesCollectionStyle(CollectionViewStyle seriesCollectionStyle);

    CardType seriesCardType() const;
    void setSeriesCardType(CardType seriesCardType);

    CollectionViewStyle seasonCollectionStyle() const;
    void setSeasonCollectionStyle(CollectionViewStyle seasonCollectionStyle);

    CollectionViewStyle episodeCollectionStyle() const;
    void setEpisodeCollectionStyle(CollectionViewStyle episodeCollectionStyle);


    static void declareSettingsQml();

signals:
    void seriesCollectionStyleChanged();
    void seriesCardTypeChanged();
    void seasonCollectionStyleChanged();
    void episodeCollectionStyleChanged();

private:
    CollectionViewStyle mSeriesCollectionStyle;
    CardType mSeriesCardType;
    CollectionViewStyle mSeasonCollectionStyle;
    CollectionViewStyle mEpisodeCollectionStyle;
    QSettings mSettings;
};

#endif // SETTINGS_H
