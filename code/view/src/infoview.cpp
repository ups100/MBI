#include "infoview.h"
#include "ui_infoview.h"

InfoView::InfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoView),
    m_esc(tr("Esc"), this)
{
    ui->setupUi(this);

    // Shortcut
    // Escape key should close window.
    connect(&m_esc, SIGNAL(activated()), this, SLOT(close()));
}

InfoView::~InfoView()
{
    delete ui;
}
