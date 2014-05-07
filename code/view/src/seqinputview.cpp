#include "seqinputview.h"
#include "ui_seqinputview.h"

SeqInputView::SeqInputView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeqInputView),
    m_esc(tr("Esc"), this)
{
    ui->setupUi(this);
	
	// Monospace font set into sequence editor and list widgets
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    ui->m_listWidget->setFont(font);
    ui->m_lineInsert->setFont(font);

    // Double click on any list item should make it editable
    connect(ui->m_listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_m_pushButt_Edit_clicked()));

    // Shortcut
    // Escape key should close window.
    connect(&m_esc, SIGNAL(activated()), this, SLOT(close()));

	// after click Add button, keyboard focus still stay at the line insert field
	connect(ui->m_pushButt_Add, SIGNAL(clicked()), ui->m_lineInsert, SLOT(setFocus()));
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
    QString newSeq = ui->m_lineInsert->text();
    if (newSeq.length() == 0) {
        QMessageBox emptySeq;
        emptySeq.information(this,"Empty sequence", tr("Zero length sequence is incorrect."));
        return;
    }

    // if sequence is not empty add to sequence list (not check if all lengths are equal)
    ui->m_listWidget->addItem(newSeq);
    ui->m_lineInsert->clear();
}

void SeqInputView::on_m_lineInsert_returnPressed()
{
    on_m_pushButt_Add_clicked();
}

void SeqInputView::on_m_pushButt_Delete_clicked()
{
    // if no item is selected (even that which was last selected and now it is still current item until new will be selected)
    if( !ui->m_listWidget->isItemSelected(ui->m_listWidget->currentItem()) ) {
        QMessageBox messageBox;
        messageBox.critical(0,tr("Error"),tr("No items to delete.\n Select any item."));
        messageBox.setFixedSize(500,200);
    }

    qDeleteAll(ui->m_listWidget->selectedItems());
}

void SeqInputView::on_m_pushButt_Cancel_clicked()
{
    this->hide();
}

void SeqInputView::on_m_pushButt_Export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "./untitled.blo",
                               tr("BLOSUM Files (*.blo);; All files (*.*)"));

    if (fileName.isEmpty()) // no file selected
        return;

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
        tr("Open File"), ".", tr("BLOSUM Files (*.blo);; Test files (*.mbi);; All files (*.*)"));

    if (fileName.isEmpty()) // no file selected
        return;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

	// Read .mbi files
	if (fileName.contains(QString(".mbi"))) { //attempt to load file with .mbi extension (files used for project testing)
		readMbiFiles(file);
		file.close();
		return;
	}

	// Normal files (.blo) read
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
        if (!checkGivenSeq())
            return;
        this->hide();
        emit done_signal();
    }
}


void SeqInputView::on_m_pushButt_Edit_clicked()
{
    QListWidgetItem *item = ui->m_listWidget->currentItem();
    // check if any item is selected
    if (!item) {
        QMessageBox messageBox;
        messageBox.critical(0,tr("Error"),tr("Select any item from the sequence list."));
        messageBox.setFixedSize(500,200);
        messageBox.show();
        return;
    }

    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->m_listWidget->editItem(item);
}

bool SeqInputView::checkGivenSeq() const
{
    bool correct = true; //intialy set to correct sequence decision

    // First sequence size (one list item length)
    int seqSize = ui->m_listWidget->item(0)->text().size();

    // now check if all sequence has the same lenght as first.
    // Prepare message:
    QString text("First sequence lenght is different then all which are selected. \nFirst sequence length is ");
    text.append(QString::number(seqSize));
    text.append("\nAll sequence must have the same length. Please correct length in either first or selected sequence. \
		\nOr you can delete selected items by Delete button.");

    int currSize = 0;
    int listSize = ui->m_listWidget->count();
    QListWidgetItem *item;
    for(int i=1; i < listSize; ++i) { //start from second sequence
        item = ui->m_listWidget->item(i);
        currSize = item->text().size();
        if (seqSize != currSize) {
            correct = false; //there is at least one sequence with different length than first sequence
            item->setSelected(true); // it should be selected
			ui->m_listWidget->setCurrentItem(item);
        } else
            item->setSelected(false);
    }

    if (!correct) {
        QMessageBox messageBox;

        messageBox.information(0,tr("Error"),text);
        messageBox.setFixedSize(500,200);
        messageBox.show();
    }

    return correct;
}

void SeqInputView::readMbiFiles(QFile &file)
{
	QTextStream in(&file);
	// load entire line
	QString line(in.readLine());
	// line consist some number of sequence which are separated by semicolon sign ';'
	QString seq(line.section(';', 0, 0)); //get first sequence

	int secIter = 1; //string section iterator - begin from second sequence (first is already read)
	while (!seq.isEmpty() && !seq.contains('=')) {
        ui->m_listWidget->addItem(seq);
		seq = line.section(';', secIter, secIter); //get next section
		++secIter;
    }
}
