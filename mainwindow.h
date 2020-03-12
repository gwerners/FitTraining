#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSqlTableModel>
#include <QElapsedTimer>
#include <QTime>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>

#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  DbManager& db();
private slots:

  void on_cmbDayOfWeek_currentIndexChanged(int index);

  void on_rbtnNewBlood_clicked();

  void on_rbtnGoodBhavior_clicked();

  void on_rbtnVeteran_clicked();

  void on_spnPushups_valueChanged(int arg1);

  void on_spnSquats_valueChanged(int arg1);

  void on_spnPullups_valueChanged(int arg1);

  void on_spnLegRaises_valueChanged(int arg1);

  void on_spnBridges_valueChanged(int arg1);

  void on_spnHandstandPushups_valueChanged(int arg1);

  void showImage1(QString name, int index);

  void showImage2(QString name, int index);

  void on_cmbRoutine1_currentIndexChanged(int arg1);

  void on_cmbUser_currentIndexChanged(int index);

  void fillRoutines(int day);

  void getRoutine(int user, int day);

  void changeSerie(QString tblName, QTableView* tbl, int index);

  void setSerie(int day);

  void on_cmbRoutine1_highlighted(int index);

  void on_cmbRoutine2_currentIndexChanged(int index);

  void on_cmbRoutine2_highlighted(int index);

  void on_btnStart_released();
  void showTime();

private:
  Ui::MainWindow *ui;
  DbManager m_db;
  bool canUpdateRoutine1;
  bool canUpdateRoutine2;
  QTimer* timer;
  int rest;
  int pos;
  QMediaPlayer* player;
};

#endif // MAINWINDOW_H
