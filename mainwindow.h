#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainlayout.h"

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class MainLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

private:
  MainLayout *mainLayout;
  QMenu *fileMenu;
  QMenu *aboutMenu;

  //Functions
  void createMenus();

private slots:
  void exportBuild();
  void about();
};

#endif // MAINWINDOW_H
