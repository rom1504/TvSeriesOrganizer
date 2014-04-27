#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(SeriesCollectionStyle)
    Q_PROPERTY(SeriesCollectionStyle seriesCollectionStyle READ seriesCollectionStyle WRITE setSeriesCollectionStyle NOTIFY seriesCollectionStyleChanged)
public:
    enum SeriesCollectionStyle
    {
         SeriesList,
         SeriesGrid
     };
    explicit Settings(QObject *parent = 0);

    SeriesCollectionStyle seriesCollectionStyle() const;
    void setSeriesCollectionStyle(SeriesCollectionStyle seriesCollectionStyle);

    static void declareSettingsQml();

signals:
    void seriesCollectionStyleChanged();

private:
    SeriesCollectionStyle mSeriesCollectionStyle;
    QSettings mSettings;
};

#endif // SETTINGS_H
