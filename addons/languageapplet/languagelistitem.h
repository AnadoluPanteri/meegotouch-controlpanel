#ifndef LANGUAGELISTITEM_H
#define LANGUAGELISTITEM_H

#include <DuiWidget>

class DuiLabel;
class DuiButton;
class DuiLayout;
class DuiGridLayoutPolicy;
class DuiSeparator;

class LanguageListItem : public DuiWidget
{
    Q_OBJECT

public:
    LanguageListItem(const QString &langCode,
                     const QString &text, 
                     DuiWidget *parent = 0);
    virtual ~LanguageListItem();
    void checked(bool ok);
    bool isChecked();
    bool isClicked();
    QString text() const;
    QString langCode() const;
    void setVisibleSeparator(bool enable);

protected:
    void initWidget();
    //! reimp
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //! reimp_end

private:
    QString m_LangCode;
    QString m_LabelText;
    DuiLabel *m_NormalLabel;
    DuiButton *m_CheckMark;
    bool m_Checked;
    bool m_Clicked;
    DuiSeparator *m_GreySeparator;

signals:
    void clicked(LanguageListItem *item);
};
#endif // LANGUAGELISTITEM_H

