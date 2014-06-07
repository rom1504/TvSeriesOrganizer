#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QUrl>

class Image : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl small READ small NOTIFY smallChanged)
    Q_PROPERTY(QUrl big READ big NOTIFY bigChanged)

public:
    explicit Image(QUrl small,QUrl big,QObject *parent);
    explicit Image(QString thetvdbFileName,QObject *parent);

    QUrl small() const;
    QUrl big() const;

signals:
    void smallChanged();
    void bigChanged();


private:
    QUrl mSmall;
    QUrl mBig;
};
Q_DECLARE_METATYPE (Image*)

#endif // IMAGE_H
