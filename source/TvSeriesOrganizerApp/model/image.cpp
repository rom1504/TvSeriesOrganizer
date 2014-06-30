#include "image.h"

Image::Image(QUrl small,QUrl big,QObject *parent) :
    QObject(parent), mSmall(small), mBig(big)
{
}


Image::Image(QString thetvdbFileName,QObject *parent) :
    Image(QUrl("http://thetvdb.com/banners/_cache/"+thetvdbFileName),QUrl("http://thetvdb.com/banners/"+thetvdbFileName),parent)
{
}

QUrl Image::small() const
{
    return mSmall;
}

QUrl Image::big() const
{
    return mBig;
}
