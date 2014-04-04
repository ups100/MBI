#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	MBI_project::Algorithm::BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;

	w.setAlgorithm(&alg);

    w.show();

    return a.exec();
}
