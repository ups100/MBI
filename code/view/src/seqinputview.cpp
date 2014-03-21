#include "seqinputview.h"
#include "ui_seqinputview.h"

SeqInputView::SeqInputView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeqInputView)
{
    ui->setupUi(this);
}

SeqInputView::~SeqInputView()
{
    delete ui;
}

QVector<SequenceType> SeqInputView::getSequence() const
{
    QVector<SequenceType> seqList;

    QString str;
    int listSize = ui->m_listWidget->count();
    for(int i=0; i < listSize; ++i) {
        str = ui->m_listWidget->item(i)->text();
        seqList.push_back(str.toStdString().c_str());
    }

    return seqList;
}

void SeqInputView::on_m_pushButt_Add_clicked()
{
    ui->m_listWidget->addItem(ui->m_lineInsert->text());
    ui->m_lineInsert->clear();

    //TODO
    // emit sygnał do modelu żeby dodać nową sekwencję, albo trzymanie
}

void SeqInputView::on_m_lineInsert_returnPressed()
{
    on_m_pushButt_Add_clicked();
}

void SeqInputView::on_m_pushButt_Delete_clicked()
{
    qDeleteAll(ui->m_listWidget->selectedItems());
}

void SeqInputView::on_m_pushButt_Cancel_clicked()
{
    this->hide();
}

void SeqInputView::on_m_pushButt_Export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "./untitled.mbi",
                               tr("MBI Files (*.mbi); All files (*.*)"));

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    int listSize = ui->m_listWidget->count();
    for(int i=0; i < listSize; ++i)
        out << ui->m_listWidget->item(i)->text() << "\n";

    file.close();
}

void SeqInputView::on_m_pushButt_Import_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), ".", tr("MBI Files (*.mbi); All files (*.*)"));

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    while (!in.atEnd()) {
        ui->m_listWidget->addItem(in.readLine());
    }
    file.close();
}

void SeqInputView::on_m_pushButt_Done_clicked()
{
    if (ui->m_listWidget->count() <= 0) {
        QMessageBox messageBox;
        messageBox.critical(0,tr("Error"),tr("First give some sequences !"));
        messageBox.setFixedSize(500,200);
    } else {
        this->hide();
        emit done_signal();
    }
}
