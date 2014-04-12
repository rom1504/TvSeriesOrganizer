#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QDomElement>
#include <QUrl>

class Actor : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QUrl image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString role READ role NOTIFY roleChanged)
    Q_PROPERTY(int sortOrder READ sortOrder NOTIFY sortOrderChanged)

    explicit Actor(int id,QUrl image,QString name,QString role,int sortOrder,QObject *parent = 0);
    explicit Actor(QDomElement element,QObject *parent = 0);

    QString role() const;
    int sortOrder() const;
    QString name() const;
    QUrl image() const;
    int id() const;

signals:
    void imageChanged();
    void nameChanged();
    void roleChanged();
    void sortOrderChanged();

public slots:

private:
    int mId;
    QUrl mImage;
    QString mName;
    QString mRole;
    int mSortOrder;

};
Q_DECLARE_METATYPE (Actor*)

#endif // ACTOR_H
