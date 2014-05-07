#include "resultwindow.h"
#include "ui_resultwindow.h"
#include "tableplainview.h"
#include "tableview.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

ResultWindow::ResultWindow(int dim, QWidget *parent) :
    QMainWindow(parent), m_dim(dim), m_vs(None),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    makeTabs(Table); //make all Tab widgets and their contents

    // Connect menu actions with slots:
    connect(ui->actionTable_view, SIGNAL(triggered()), this, SLOT(changeViewToTable()));
    connect(ui->actionText_view, SIGNAL(triggered()), this, SLOT(changeViewToText()));

    // Preclusive selections of two menu entries (tick sign next to menu entry):
    connect(ui->actionTable_view, SIGNAL(triggered()), ui->actionText_view, SLOT(toggle()));
    connect(ui->actionText_view, SIGNAL(triggered()), ui->actionTable_view, SLOT(toggle()));

    // File menu
    connect(ui->actionSave_as_CSV, SIGNAL(triggered()), this, SLOT(saveToCSV()));
    connect(ui->actionSave_as_CSV_semicolon, SIGNAL(triggered()), this, SLOT(saveToCSVsemicolon()));
    connect(ui->actionSave_as_Text, SIGNAL(triggered()), this, SLOT(saveToText()));

    // Close menu item
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));

    // initialize data pointer
    m_blosumData = NULL;
    m_substData = NULL;
    m_probData = NULL;
    m_logsData = NULL;
}

ResultWindow::~ResultWindow()
{
    delete ui;

    // Those two QHash were create on heap
    if(m_blosumData) delete m_blosumData;
    if(m_substData) delete m_substData;

    //delete all matrix widgets
    if(m_matBlosum) delete m_matBlosum;
    if(m_matLogs) delete m_matLogs;
    if(m_matProb) delete m_matProb;
    if(m_matSubst) delete m_matSubst;
}

void ResultWindow::makeTabs(ViewStyle vs)
{
    // If we have any view style set already - do nothing.
    if (m_vs != None)
        return;

    // Size policy
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    // Tab 1
    m_tab_1 = new QWidget();
    m_tab_1->setObjectName(QStringLiteral("m_tab_1"));
    ui->m_tabWidget->addTab(m_tab_1, QString("Substitution"));

    // Tab 2
    m_tab_2 = new QWidget();
    m_tab_2->setObjectName(QStringLiteral("m_tab_2"));
    ui->m_tabWidget->addTab(m_tab_2, QString("Probability"));

    // Tab 3
    m_tab_3 = new QWidget();
    m_tab_3->setObjectName(QStringLiteral("m_tab_3"));
    ui->m_tabWidget->addTab(m_tab_3, QString("Logarithms"));

    // Tab 4
    m_tab_4 = new QWidget();
    m_tab_4->setObjectName(QStringLiteral("m_tab_4"));
    ui->m_tabWidget->addTab(m_tab_4, QString("BLOSUM"));

    // At the begging active tab should be Blosum tab
    ui->m_tabWidget->setCurrentIndex(3);

    // Create specific view style - table or plain text view
    if (vs == Table) {
        m_matSubst = new TableView(m_dim, m_tab_1);
        m_matProb = new TableView(m_dim, m_tab_2);
        m_matLogs = new TableView(m_dim, m_tab_3);
        m_matBlosum = new TableView(m_dim, m_tab_4);
    } else {
        m_matSubst = new TablePlainView(m_dim, m_tab_1);
        m_matProb = new TablePlainView(m_dim, m_tab_2);
        m_matLogs = new TablePlainView(m_dim, m_tab_3);
        m_matBlosum = new TablePlainView(m_dim, m_tab_4);
    }

    // Now there is new view style:
    m_vs = vs;
}


void ResultWindow::showBlosumMat(const IntMatrix *m)
{
    if (m == NULL)
        return;

    // Here m must be converted to TMatrix type
    m_blosumData = new TMatrix;
	IntMatrix::ConstIterator it = m->begin();
    IntMatrix::ConstIterator end = m->end();
    for ( ; it != end; ++it) {
        m_blosumData->insert(it.key(), it.value());
    }

    // Call view function to display matrix
    m_matBlosum->viewMatrix(m_blosumData);
}

void ResultWindow::showSubstMat(const IntMatrix *m)
{
    if (m == NULL)
        return;

    // Here m must be converted to TMatrix type
    m_substData = new TMatrix;
    IntMatrix::ConstIterator it = m->begin();
    IntMatrix::ConstIterator end = m->end();
    for ( ; it != end; ++it) {
        m_substData->insert(it.key(), it.value());
    }
    // Call view function to display matrix
    m_matSubst->viewMatrix(m_substData);
}

void ResultWindow::showProbMat(TMatrix *m)
{
    if (m == NULL)
        return;

    m_probData = m; //remember matrix to future view refresh
    m_matProb->viewMatrix(m);
}

void ResultWindow::showLogsMat(TMatrix *m)
{
    if (m == NULL)
        return;

    m_logsData = m;
    m_matLogs->viewMatrix(m);
}

void ResultWindow::changeView(ViewStyle vs)
{
    // if current view style is the same as require - do nothing
    if (vs == m_vs)
        return;

    while(ui->m_tabWidget->count())
        ui->m_tabWidget->removeTab(0);

    //delete all matrix widgets
    delete m_matBlosum;
    delete m_matLogs;
    delete m_matProb;
    delete m_matSubst;

    m_vs = None; //to signal that Tab widget is empty - without any Visual Style

    makeTabs(vs); //create new Tabs with new Visual Style

    // if matrix data were loaded before then show it
    showAllMat();
}

void ResultWindow::saveAs(QString sep)
{
    QString fileName;

    if (sep.contains(',') || sep.contains(';'))
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "./untitled.csv",
                               tr("CSV Files (*.csv);; All files (*.*)"));
    else
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "./untitled.txt",
                               tr("Text Files (*.txt);; All files (*.*)"));

    if (fileName.isEmpty()) // no file selected - nothing to do
        return;

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    QVector<QVector<double> > array;

    // check wich Tab is active and choose appropriate matrix data
    switch (ui->m_tabWidget->currentIndex()) {
    case 0:
        array = m_matSubst->getRawData();
        break;
    case 1:
        array = m_matProb->getRawData();
        break;
    case 2:
        array = m_matLogs->getRawData();
        break;
    case 3:
        array = m_matBlosum->getRawData();
        break;
    default:
        break;
    }

    // saving data to file
    int size = array.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j)
        {
            out << QString::number(array[i][j]);
            out << sep; // put separator after

        }
        // last element without separator after
        out << QString::number(array[i][size-1]);
        out << "\r\n";
    }
    file.close();
}

void ResultWindow::changeViewToTable()
{
    changeView(Table);
}

void ResultWindow::changeViewToText()
{
    changeView(PlainText);
}

void ResultWindow::saveToCSV()
{
    saveAs(", ");
}

void ResultWindow::saveToCSVsemicolon()
{
    saveAs("; ");
}

void ResultWindow::saveToText()
{
    saveAs(" ");
}

void ResultWindow::showAllMat()
{
    if(m_matBlosum && m_blosumData) m_matBlosum->viewMatrix(m_blosumData);
    if(m_matSubst && m_substData) m_matSubst->viewMatrix(m_substData);
    if(m_matProb && m_probData) m_matProb->viewMatrix(m_probData);
    if(m_matLogs && m_logsData) m_matLogs->viewMatrix(m_logsData);
}
