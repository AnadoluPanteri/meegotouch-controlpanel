#ifndef DCPIMAGEUTILS_H
#define DCPIMAGEUTILS_H

#include <QPixmap>
#include <QString>
#include <QHash>
class QPixmapCache;

class DcpImageUtils {
public:
    static DcpImageUtils* instance();
    static QPixmap borderCorrectScale(const QPixmap& pixmap,
                           int newWidth, int newHeight = -1,
                           int borderSize = 20);
    QPixmap scaledPixmap(const QString& id, int newWidth,
                          int newHeight = -1, int borderSize = 20);
    QPixmap scaledPixmap(const QString& id, const QSize& newSize,
                         int borderSize = 20);

protected:
    DcpImageUtils();
    ~DcpImageUtils();
    static DcpImageUtils* sm_Instance;

    QPixmapCache* m_PixmapCache;
    QHash<QString, const QPixmap*> m_PixmapUnderLoading;
};


inline DcpImageUtils* DcpImageUtils::instance() {
    if (!sm_Instance) sm_Instance = new DcpImageUtils;
    return sm_Instance;
}


inline QPixmap
        DcpImageUtils::scaledPixmap(const QString& id, const QSize& newSize,
                                    int borderSize)
{
    return scaledPixmap(id, newSize.width(), newSize.height(), borderSize);
}


#endif // DCPIMAGEUTILS_H
