
#include "dcpbutton2imageview.h"
//DUI_STYLABLE_CPP(DcpButton2ImageView, DuiWidgetView)

#include <QPainter>
#include <DuiTheme>
#include "dcpbutton.h"

//dummy
const QString imageFile    = "/usr/share/themes/dui/duicontrolpanel/images/starfield.png";

/* 
LEFT
Margins:

              marginLeft                  imageSpacer 
                V                            V
                +----------------+-----------+    < marginTop
                |Text1           |           |
marginMiddle >  +----------------+   Image   +
                |           Text2|           |
                +----------------+ ----------+   < marginBotton
                                 A
                            marginRight
*/

/* 
RIGHT
Margins:

              imageSpacer     marginLeft
                V           V
                +-----------+----------------+    < marginTop
                |           |Text1           |
marginMiddle >  +   Image   +----------------+
                |           |           Text2|
                +-----------+ ---------------+    < marginBotton
                                             A
                                        marginRight
*/


DcpButton2ImageView::DcpButton2ImageView(DcpButton *button) :
    DcpButton2View(button)
{

	//QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));

	m_Image = new QPixmap(QPixmap(imageFile).scaled(62, 62)); //dummy
}

DcpButton2ImageView::~DcpButton2ImageView()
{
	delete m_Image;
}

void DcpButton2ImageView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

	paintBackground(painter);

	paintLine(painter);

//qDebug() << "size()   " << size().width() << "   X   "<< size().height();

	if ( m_Alignment==Qt::AlignLeft ) {
		paintTriangle(painter);
		paintTextLeft(painter);
		paintImageLeft(painter);

	} else {
  //  if ( m_Alignment==Qt::AlignRight ) {
		paintTriangleRight(painter);
		paintTextRight(painter);
		paintImageRight(painter);

	}

}

void DcpButton2ImageView::paintTextLeft(QPainter *painter, bool textBool)
{
  	int marginLeft = style()->fieldMarginLeft();
    int marginRight = style()->fieldMarginRight();
    int marginTop = style()->fieldMarginTop();
    int marginBottom = style()->fieldMarginBottom();
	int marginMiddle = style()->fieldMarginMiddle();


	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();

	int fieldWidth = style()->backgroundSize().width() -
					 marginLeft -
					 marginRight -
					 triangleWidth -
					 style()->imageSize().width() -
					 style()->marginSpacer() ;

	int fieldHeight = (style()->backgroundSize().height() - marginTop - marginBottom - marginMiddle) / 2;

	QRectF text1Rect(style()->textPos1().x() + marginLeft + triangleWidth,
					 style()->textPos1().y() + marginTop,
					 fieldWidth,
					 fieldHeight);


    // Draw text
    painter->setFont(style()->font1());
	painter->setPen(style()->textColor1());
	
    painter->drawText(text1Rect, style()->textAlign1(), m_Text1);

	QRectF text2Rect(style()->textPos2().x() + marginLeft + triangleWidth,
					 style()->textPos2().y() + marginTop,
					 fieldWidth,
					 fieldHeight);

    painter->setFont(style()->font2());

	if (textBool)
		painter->setPen(style()->textColor2());
	else
		painter->setPen(style()->textOffColor());

    painter->drawText(text2Rect, style()->textAlign2(), m_Text2);

	return;
}

void DcpButton2ImageView::paintImageLeft(QPainter *painter)
{

	int marginSpacer = style()->marginSpacer();

//		QPixmap *image = new QPixmap(QPixmap(*styleAttribute<const QPixmap*>(ImageNameAttribute)).scaled(styleAttribute<const QSize>(ImageSizeAttribute)));


    if (m_Image != NULL) {

		//QPointF imagePoint( width() - m_Image->width() + 1 - marginSpacer,
		//				   (height() - m_Image->height()) / 2				);

		QPointF imagePoint( size().width() - m_Image->width() + 1 - marginSpacer,
						   (size().height() - m_Image->height()) / 2				);


        painter->drawPixmap(imagePoint, *m_Image);
	}

	
	const QPixmap *border = DuiTheme::pixmap(style()->backgroundBorder(),
											 QSize(m_Image->width() + 2, m_Image->height() + 2)	);

    if (border != NULL) {

	//	QPointF imagePoint( width() - border->width() + (border->width() - m_Image->width()) - marginSpacer,
	//		 			   (height() - border->height()) / 2					);

	QPointF imagePoint( size().width() - border->width() + (border->width() - m_Image->width()) - marginSpacer,
			 		   (size().height() - border->height()) / 2					);


        painter->drawPixmap(imagePoint, *border);
	}

}

void DcpButton2ImageView::paintTriangleRight(QPainter *painter)
{
    int marginLeft = style()->fieldMarginLeft();
    int marginTop = style()->fieldMarginTop();

	const QPixmap *triangle = DuiTheme::pixmap(	style()->triangleBackground(), style()->triangleBackgroundSize());

    if (triangle != NULL) {

		QPointF trianglePoint(style()->trianglePos().x() + style()->marginSpacer() + style()->imageSize().width() + marginLeft,
							  style()->trianglePos().y() + marginTop		);

        painter->drawPixmap(trianglePoint, *triangle);
	}
}

void DcpButton2ImageView::paintTextRight(QPainter *painter, bool textBool)
{
  	int marginLeft = style()->fieldMarginLeft();
    int marginRight = style()->fieldMarginRight();
    int marginTop = style()->fieldMarginTop();
    int marginBottom = style()->fieldMarginBottom();
	int marginMiddle = style()->fieldMarginMiddle();

	int triangleWidth = style()->triangleBackgroundSize().width() + style()->marginTriangle();


	int fieldWidth = style()->backgroundSize().width() -
					 marginLeft -
					 marginRight -
					 triangleWidth -
					 style()->imageSize().width() -
					 style()->marginSpacer();

	int fieldHeight = (style()->backgroundSize().height() - marginTop - marginBottom - marginMiddle) / 2;

	QRectF text1Rect(style()->textPos1().x() + style()->marginSpacer() + style()->imageSize().width() + marginLeft + triangleWidth,
					 style()->textPos1().y() + marginTop,
					 fieldWidth,
					 fieldHeight);


    // Draw text
    painter->setFont(style()->font1());
	painter->setPen(style()->textColor1());
	
    painter->drawText(text1Rect, style()->textAlign1(), m_Text1);


	QRectF text2Rect(style()->textPos2().x() + style()->marginSpacer() + style()->imageSize().width() + marginLeft + triangleWidth,
					 style()->textPos2().y() + marginTop,
					 fieldWidth,
					 fieldHeight);

    painter->setFont(style()->font2());

	if (textBool)
    	painter->setPen(style()->textColor2());
	else
		painter->setPen(style()->textOffColor());

    painter->drawText(text2Rect, style()->textAlign2(), m_Text2);

	return;
}

void DcpButton2ImageView::paintImageRight(QPainter *painter)
{
    int marginSpacer = style()->marginSpacer();

    if (m_Image != NULL) {

        QPointF imagePoint( marginSpacer,
                           (height() - m_Image->height()) / 2);

        painter->drawPixmap(imagePoint, *m_Image);
	}

		
	const QPixmap *border = DuiTheme::pixmap(style()->backgroundBorder(),
											 QSize(m_Image->width() + 2, m_Image->height() + 2) );

    if (border != NULL) {

		QPointF imagePoint(marginSpacer + (border->width() - m_Image->width()),
			 			   (height() - border->height()) / 2);

        painter->drawPixmap(imagePoint, *border);
	}
}

/*
void DcpButton2ImageView::registerStyleAttributes(DuiStyleDescription &description)
{

	description.addAttribute(MarginLeftAttribute, "marginLeft");
    description.addAttribute(MarginRightAttribute, "marginRight");
    description.addAttribute(MarginTopAttribute, "marginTop");
    description.addAttribute(MarginBottomAttribute, "marginBottom");
	description.addAttribute(MarginMiddleAttribute, "marginMiddle");

    description.addAttribute(BackgroundAttribute, "backgroundImage");
	description.addAttribute(BackgroundSizeAttribute, "backgroundSize");

    description.addAttribute(Font1Attribute, "font1");
	description.addAttribute(Font2Attribute, "font2");

    description.addAttribute(TextColor1Attribute, "textColor1");
	description.addAttribute(TextColor2Attribute, "textColor2");
	description.addAttribute(TextOffColorAttribute, "textOffColor");

	description.addAttribute(TextSize1Attribute, "textSize1");
	description.addAttribute(TextSize2Attribute, "textSize2");

    description.addAttribute(TextPos1Attribute, "textPos1");
	description.addAttribute(TextPos2Attribute, "textPos2");

	description.addAttribute(TextAlign1Attribute, "textAlign1");
	description.addAttribute(TextAlign2Attribute, "textAlign2");
		
	description.addAttribute(TriangleBackgroundAttribute, "triangleBackground");
	description.addAttribute(TriangleBackgroundSizeAttribute, "triangleBackgroundSize");
	description.addAttribute(TrianglePosAttribute, "trianglePos");

	description.addAttribute(MarginTriangleAttribute, "marginTriangle");

	description.addAttribute(ImageNameAttribute, "imageName");
	description.addAttribute(ImageSizeAttribute, "imageSize");

	description.addAttribute(MarginSpacerAttribute, "marginSpacer");

	description.addAttribute(BackgroundBorderAttribute, "backgroundBorder");
}
*/

DUI_REGISTER_VIEW("DcpButton2ImageView", DcpButton2ImageView, DcpButton)