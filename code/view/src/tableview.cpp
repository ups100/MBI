#include "tableview.h"
#include "ui_tableview.h"

TableView::TableView(int inputDim, QWidget *parent) :
    TableAbstract(inputDim, parent)
{
    m_tableView = new QTableView(parent);

    // Create a new model
    // QStandardItemModel(int rows, int columns, QObject * parent = 0)
    m_model = new QStandardItemModel(inputDim, inputDim, this);
    // Attach the model to the view
    m_tableView->setModel(m_model);

    m_tableView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    m_gridLayout = new QGridLayout(parent);
    m_description = new QLabel("Blosum algorithm results:");
    m_gridLayout->addWidget(m_description);
    m_gridLayout->addWidget(m_tableView);
}

TableView::~TableView()
{
    delete m_tableView;
}

void TableView::viewMatrix(TMatrix *m)
{
    transformIntoArray(m);

    QString str;
    int size = m_symbols.size();
    for (int i = 0; i < size; ++i) {
        m_model->setHorizontalHeaderItem(i, new QStandardItem(QString(m_symbols[i])));
        m_model->setVerticalHeaderItem(i, new QStandardItem(QString(m_symbols[i])));
        for (int j = 0; j < size; ++j)
        {
            m_model->setItem(i,j, new QStandardItem(QString::number(m_array[i][j])));
        }

    }
}

void TableView::setDescription(QString &des)
{
    m_description->setText(des);
}
