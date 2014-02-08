#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QString>
#include <QUrl>

class Episode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    Q_PROPERTY(QUrl banner READ banner NOTIFY bannerChanged)

public:
    explicit Episode(int number, const QString & name, const QString& description, QUrl banner, QObject *parent = 0);
    int number() const;
    QString name() const;
    QString description() const;
    QUrl banner() const;

signals:
    void numberChanged();
    void nameChanged();
    void descriptionChanged();
    void bannerChanged();

public slots:

private:
    int mNumber;
    QString mName;
    QString mDescription;
    QUrl mBanner;
};

Q_DECLARE_METATYPE (Episode*)

#endif // EPISODE_H
