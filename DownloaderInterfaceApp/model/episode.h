#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QString>

class Episode : public QObject
{
    Q_OBJECT
public:
    explicit Episode(int number, const QString & name, const QString& description, QObject *parent = 0);
    int number() const;
    QString name() const;
    QString description() const;

    void setNumber(int number);
    void setName(const QString & name);
    void setDescription(const QString& description);

signals:

public slots:

private:
    int mNumber;
    QString mName;
    QString mDescription;
};

Q_DECLARE_METATYPE (Episode*)

#endif // EPISODE_H
