#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&seqInView, SIGNAL(done_signal()), this, SLOT(on_sequenceProvided()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->m_pushButt_Clear->setEnabled(true);
}
