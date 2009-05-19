
#include "dcpbuttonview.h"
//DUI_STYLABLE_CPP(DcpButtonView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

const QColor LINECOLOR = QColor(64, 64, 64);

DcpButtonView::DcpButtonView(DcpButton *button) :
    DuiWidgetView(button),
//    controller(*button),
    m_Bkgr(false),
	m_LineBool(true)
{
//    controller.setZValue(1);

	//style()->fieldMarginLeft();
}

DcpButtonView::~DcpButtonView()
{
    //if (m_Background) {
    //    DuiTheme::releasePixmap(m_Background);
    //}
}

void DcpButtonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

//qDebug() << "---------------------------------------";
//qDebug() << "size:   " <<  controller.size().width() << "   X   " << controller.size().height();
//qDebug() << "boundingRect:   " <<  controller.boundingRect().width() << "   X   " << controller.boundingRect().height();
//qDebug() << "geometry:   " << controller.geometry().width() << "   X   " << controller.geometry().height(); 
//qDebug() << "---------------------------------------";

    Q_UNUSED(widget);
    Q_UNUSED(option);

    //paintBackground(painter);
	paintLine(painter);
    paintTriangle(painter);
    paintText(painter);

    return;
}

void DcpButtonView::paintBackground(QPainter *painter)
{

    if (m_Bkgr) {
        //const QPixmap *bg = DuiTheme::pixmap(styleAttribute<const QString>(BackgroundAttribute),                                         styleAttribute<const QSize>(BackgroundSizeAttribute));

		const QPixmap *bg = DuiTheme::pixmap(style()->background(), style()->backgroundSize());

        if (bg != NULL)
            painter->drawPixmap(0, 0, *bg);
    }

}

void DcpButtonView::paintLine(QPainter *painter)
{
	if (m_LineBool) {
		painter->setPen(LINECOLOR);
		//painter->drawLine(0, height() + 15, width() , height());
		painter->drawLine(0, size().height() + 15, size().width() , size().height() + 15);
	}
}

void DcpButtonView::paintTriangle(QPainter *painter)
{

	int marginLeft = style()->fieldMarginLeft();
	int marginTop = style()->fieldMarginTop();


	//const QPixmap *triangle = DuiTheme::pixmap(	styleAttribute<const QString>(TriangleBackgroundAttribute), 																styleAttribute<const QSize>(TriangleBackgroundSizeAttribute));

	const QPixmap *triangle = DuiTheme::pixmap(style()->triangleBackground(), style()->triangleBackgroundSize());

    if (triangle != NULL) {

		//QPointF trianglePoint(	styleAttribute<QPointF>(TrianglePosAttribute).x() + marginLeft,														styleAttribute<QPointF>(TrianglePosAttribute).y() + marginTop		);

		QPointF trianglePoint(style()->trianglePos().x() + marginLeft, style()->trianglePos().y() + marginTop);

        painter->drawPixmap(trianglePoint, *triangle);
	}
}

void DcpButtonView::paintText(QPainter *painter)
{
  	int marginLeft = style()->fieldMarginLeft();
    int marginRight = style()->fieldMarginRight();
    int marginTop = style()->fieldMarginTop();
    int marginBottom = style()->fieldMarginBottom();

	QRectF text1Rect(	style()->textPos1().x() + marginLeft,
						style()->textPos1().y() + marginTop,
						width() - marginLeft - marginRight,
						height() - marginTop - marginBottom);

    // Draw text
    painter->setFont(style()->font1());
    painter->setPen(style()->textColor1());
    painter->drawText(text1Rect, style()->textAlign1(), m_Text1);

}

QRectF DcpButtonView::boundingRect() const
{
	return QRectF(QPointF(), style()->backgroundSize());
}


/*
void DcpButtonView::registerStyleAttributes(DuiStyleDescription &description)
{

  	description.addAttribute(MarginLeftAttribute, "marginLeft");
    description.addAttribute(MarginRightAttribute, "marginRight");
    description.addAttribute(MarginTopAttribute, "marginTop");
    description.addAttribute(MarginBottomAttribute, "marginBottom");
//		description.addAttribute(MarginMiddleAttribute, "marginMiddle");


    description.addAttribute(BackgroundAttribute, "backgroundImage");
	description.addAttribute(BackgroundSizeAttribute, "backgroundSize");

    description.addAttribute(Font1Attribute, "font1");
//		description.addAttribute(Font2Attribute, "font2");

    description.addAttribute(TextColor1Attribute, "textColor1");
//		description.addAttribute(TextColor2Attribute, "textColor2");

	description.addAttribute(TextSize1Attribute, "textSize1");
//		description.addAttribute(TextSize2Attribute, "textSize2");

	description.addAttribute(TextPos1Attribute, "textPos1");
//		description.addAttribute(TextPos2Attribute, "textPos2");

	description.addAttribute(TextAlign1Attribute, "textAlign1");
//		description.addAttribute(TextAlign2Attribute, "textAlign2");
		

	description.addAttribute(TriangleBackgroundAttribute, "triangleBackground");
	description.addAttribute(TriangleBackgroundSizeAttribute, "triangleBackgroundSize");
	description.addAttribute(TrianglePosAttribute, "trianglePos");

}
*/

void DcpButtonView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

}

void DcpButtonView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
	emit clicked();
}

int DcpButtonView::width()
{
	return style()->backgroundSize().width();
}

int DcpButtonView::height()
{
	return style()->backgroundSize().height();
}



typedef struct ALIGNTYPE{
	QString m_Name;
	Qt::Alignment m_Flag;
};

ALIGNTYPE listAlignment[] = {   { "AlignLeft", Qt::AlignLeft },
								{ "AlignRight", Qt::AlignRight },
								{ "AlignHCenter", Qt::AlignHCenter },

								{ "AlignTop", Qt::AlignTop },
								{ "AlignBottom", Qt::AlignBottom },
								{ "AlignVCenter", Qt::AlignVCenter },

								{ "AlignHCenter", Qt::AlignHCenter }        };


Qt::Alignment DcpButtonView::stringToAlign(const QString& alignment)
{

	Qt::Alignment outAligment;

	for (int i = 0; i < sizeof(listAlignment)/sizeof(ALIGNTYPE); i++)
			if (alignment.indexOf(listAlignment[i].m_Name) != -1)
				outAligment |= listAlignment[i].m_Flag;

		return outAligment;
}

DUI_REGISTER_VIEW("DcpButtonView", DcpButtonView, DcpButton)