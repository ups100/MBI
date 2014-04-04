#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_alg(NULL),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&seqInView, SIGNAL(done_signal()), this, SLOT(on_sequenceProvided()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAlgorithm(BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg)
{
	if (alg)
		this->m_alg = alg;
}

void MainWindow::on_m_pushButt_Quit_clicked()
{
    close();
}

void MainWindow::on_m_pushButt_SeqInput_clicked()
{
    seqInView.show();
}

void MainWindow::on_sequenceProvided()
{
    ui->m_pushButt_Run->setEnabled(true);
	ui->m_pushButt_SeqInput->setEnabled(false);
}

void MainWindow::on_m_pushButt_Run_clicked()
{
	Q_ASSERT(m_alg != NULL); 

	// Take data:
	QVector<SequenceType> sequences = seqInView.getSequence();

	foreach(SequenceType item, sequences)
		m_alg->addSequence(new SequenceType(item));

	// RUN algorithm
	m_alg->run();

    ui->m_pushButt_Run->setEnabled(false);
    ui->m_pushButt_Clear->setEnabled(true);

	ResultWindow *results = new ResultWindow(m_alg->getSymbolsNumber());

	results->showBlosumMat(m_alg->getBlosum());
	results->showSubstMat(m_alg->getPairsNumbers());
	results->showProbMat(const_cast<TMatrix*>(m_alg->getPairsNumbersNormalized()));
	results->showLogsMat(const_cast<TMatrix*>(m_alg->getLogs()));

    results->show();
}

void MainWindow::on_m_pushButt_Clear_clicked()
{
    m_alg->clear();

	ui->m_pushButt_Clear->setEnabled(false);
	ui->m_pushButt_SeqInput->setEnabled(true);
}

void MainWindow::on_m_pushButt_Info_clicked()
{
    m_infoWidget.show();
}
