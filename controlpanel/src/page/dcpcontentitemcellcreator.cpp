#include "dcpcontentitemcellcreator.h"

#include <QModelIndex>
#include <MWidgetRecycler>

MWidget * DcpContentItemCellCreator::createCell (const QModelIndex &index,
                                              MWidgetRecycler &recycler) const
{
    DcpContentItem * cell =
        qobject_cast<DcpContentItem*>(recycler.take("DcpContentItem"));
    if (!cell) {
        cell = new DcpContentItem();
        cell->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
    updateCell(index, cell);
    return cell;
}

void DcpContentItemCellCreator::updateCell (
        const QModelIndex& index, MWidget * cell) const
{
    DcpContentItem * contentItem = qobject_cast<DcpContentItem *>(cell);

    DcpAppletMetadata* metadata =
        index.data(MetadataRole).value<DcpAppletMetadata*>();
    DcpAppletObject* applet =
        index.data(AppletRole).value<DcpAppletObject*>();
    QString mattiID = index.data(MattiRole).toString();

    if (applet) {
        contentItem->setApplet (applet);
    } else {
        contentItem->setMetadata (metadata);
    }
    contentItem->setMattiID (mattiID);
}

