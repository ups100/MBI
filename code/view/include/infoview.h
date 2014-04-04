#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QWidget>
#include <QShortcut>

namespace Ui {
class InfoView;
}

class InfoView : public QWidget
{
    Q_OBJECT

public:
    explicit InfoView(QWidget *parent = 0);
    ~InfoView();

private:
    Ui::InfoView *ui;

    // shortcut to close window
    QShortcut m_esc;
};

#endif // INFOVIEW_H
