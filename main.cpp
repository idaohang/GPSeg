#include <QApplication>

#include "mainwindow.h"
#include "Widgets/qcustomplot.h"
int
main (int argc, char** argv)
{
  QApplication app (argc, argv);
  MainWindow mw;
  mw.show ();
  QCustomPlot w;
  w.setWindowTitle("Ploting");
  w.show();
  return (app.exec ());
}
