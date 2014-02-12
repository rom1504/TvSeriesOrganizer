#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QDate>

class Episode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString overview READ overview NOTIFY overviewChanged)
    Q_PROPERTY(QUrl banner READ banner NOTIFY bannerChanged)
    Q_PROPERTY(QDate firstAired READ firstAired NOTIFY firstAiredChanged)

public:
    explicit Episode(int number, const QString & name, const QString& overview, QUrl banner,QDate firstAired, QObject *parent = 0);
    int number() const;
    QString name() const;
    QString overview() const;
    QUrl banner() const;
    QDate firstAired() const;

signals:
    void numberChanged();
    void nameChanged();
    void overviewChanged();
    void bannerChanged();
    void firstAiredChanged();

public slots:

private:
    int mNumber;
    QString mName;
    QString mOverview;
    QUrl mBanner;
    QDate mFirstAired;
};

Q_DECLARE_METATYPE (Episode*)

#endif // EPISODE_H
