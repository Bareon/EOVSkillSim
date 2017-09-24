#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QtWidgets>
#include <QtSql>

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
QT_END_NAMESPACE

class MainLayout : public QWidget
{
  Q_OBJECT

public:
  MainLayout(QWidget *parent = 0);

  void setSkillPts(int value);
  void setRaces();
  void setClasses();
  QString writeBuild();

public slots:
  void updateSkillPts();
  void updateDescRace();
  void updateDescClass();
  void resetSkills();
  void setSkillsR();
  void setSkillsB();
  void setSkillsM();
  void setMasteries();
  void setActiveTab();
  void checkReqsR();
  void checkReqs();
  void checkDeps();
  void classChanged();
  void masteryChanged();


signals:
  void valueChanged(bool);

private:
  int skillPts = 3;
  int ptsAlloc = 0;
  int ptsTotal = 0;
  int retPts = 0;
  int retLv = 30;
  QMap<int, int> skillMapR;
  QMap<QString, int> skillMap;
  QSqlDatabase db;
  QComboBox *raceBox;
  QComboBox *classBox;
  QComboBox *masterBox;
  QSpinBox *level;
  QSpinBox *retLevel;
  QCheckBox *ret;

  QLabel *skillPtsValue;

  QHBoxLayout *charSkills;
  QTabWidget *charSkillsTabs;
  QPlainTextEdit *skillDesc;
  QHBoxLayout *classSkillsBox;
  QFormLayout *baseSkills;
  QFormLayout *masterSkills;
  QGridLayout *raceSkillsBox;
  QGroupBox *baseSkillsBox;
  QGroupBox *masterSkillsBox;
  QGroupBox *raceLv1;
  QGroupBox *raceLv5;
  QGroupBox *raceLv10;
  QGroupBox *raceLv15;
  QGroupBox *raceLv20;

  enum { numRaceSkills = 24, numClassSkills = 20};
  QHBoxLayout *raceSet[numRaceSkills];
  QPushButton *raceButtons[numRaceSkills];
  QCheckBox *raceChecks[numRaceSkills];
  QPushButton *classButtons[numClassSkills];
  QSpinBox *classSkillLv[numClassSkills];
  QWidget *raceTab;
  QWidget *classTab;
  QPushButton *resetButton;

  void setupLayout();
  void raceSelect();
  void classSelect();
  void masterSelect();



};

#endif // MAINLAYOUT_H
