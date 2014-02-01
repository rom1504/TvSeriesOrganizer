#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QString>

class Episode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number NOTIFY numberChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)

public:
    explicit Episode(int number, const QString & name, const QString& description, QObject *parent = 0);
    int number() const;
    QString name() const;
    QString description() const;

    void setNumber(int number);
    void setName(const QString & name);
    void setDescription(const QString& description);

signals:
    void numberChanged();
    void nameChanged();
    void descriptionChanged();

public slots:

private:
    int mNumber;
    QString mName;
    QString mDescription;
};

Q_DECLARE_METATYPE (Episode*)

#endif // EPISODE_H
