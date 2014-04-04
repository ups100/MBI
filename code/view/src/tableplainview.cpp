#include "tableplainview.h"

TablePlainView::TablePlainView(int inputDim, QWidget *parent) :
    TableAbstract(inputDim, parent), m_sep(" ")
{
    m_tableField = new QTextEdit(parent);
    m_tableField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_description = new QLabel("Blosum algorithm results:"); //by default - should be changed by setDescription()

    m_gridLayout = new QGridLayout(parent);
    m_gridLayout->addWidget(m_description);
    m_gridLayout->addWidget(m_tableField);
}

void TablePlainView::viewMatrix(TMatrix *m)
{
    transformIntoArray(m);

    QString str;
    int size = m_symbols.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
        {
            if (m_array[i][j] >= 0)
                str.append(m_sep);
            str.append(QString::number(m_array[i][j]));
            str.append(m_sep);
        }

        m_tableField->append(str);
        str.clear();
    }
}

void TablePlainView::setDescription(QString &des)
{
    m_description->setText(des);
}
