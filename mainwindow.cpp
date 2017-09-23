#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow() {
  QCoreApplication::setApplicationName("Etrian Odyssey V Skill Simulator");
  mainLayout = new MainLayout;
  setCentralWidget(mainLayout);
  mainLayout->setSkillsR();
  mainLayout->setSkillsB();
  mainLayout->setMasteries();
  mainLayout->setSkillsM();
  createMenus();

}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(tr("Export Character"), this, &MainWindow::exportBuild);
  aboutMenu = menuBar()->addMenu(tr("&About"));
  aboutMenu->addAction(tr("Info"), this, &MainWindow::about);
}

MainWindow::~MainWindow()
{

}

void MainWindow::exportBuild() {
    QString build = mainLayout->writeBuild();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Character Skills")
      , QDir::currentPath(), tr("(*.txt)"));
    QFile file(QFileInfo(fileName).absoluteFilePath());
  file.open(QIODevice::WriteOnly | QFile::Text);
  QTextStream out(&file);
  out << build;
  file.close();
}

void MainWindow::about() {
  QString aboutText;
  aboutText = "<HTML><center>"
    "<b>Etrian Odyssey V Skill Simulator</b><br>"
    "(c) Brent Scheppmann<br>"
    "bareous@gmail.com<br>"
    "<a href='https://github.com/Bareon'>Github</a> | "
    "<a href='https://www.youtube.com/c/BrentScheppmann'>Youtube</a> | "
    "<a href='https://twitter.com/Bareous'>Twitter</a><br>"
    "</center>"
    "</HTML>";
  QMessageBox::about(this, tr("Contact"),
    aboutText);
}
