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
    Q_PROPERTY(bool seen READ seen WRITE setSeen NOTIFY seenChanged)
    Q_PROPERTY(bool aired READ aired NOTIFY airedChanged)

public:
    explicit Episode(int number, const QString & name, const QString& overview, QUrl banner,QDate firstAired, QObject *parent = 0);
    int number() const;
    QString name() const;
    QString overview() const;
    QUrl banner() const;
    QDate firstAired() const;
    bool seen() const;
    bool aired() const;


    void setSeen(bool seen);

signals:
    void numberChanged();
    void nameChanged();
    void overviewChanged();
    void bannerChanged();
    void firstAiredChanged();
    void seenChanged();
    void airedChanged();

public slots:

private:
    int mNumber;
    QString mName;
    QString mOverview;
    QUrl mBanner;
    QDate mFirstAired;
    bool mSeen;
};

Q_DECLARE_METATYPE (Episode*)

#endif // EPISODE_H
