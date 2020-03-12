#include "dbmanager.h"

bool fileExists(const QString &path) {
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}
bool
runQuery(const QString& qry)
{
    QSqlQuery query;
    query.prepare(qry);
    if (!query.exec()) {
        qDebug() << "Database: [" << qry << "] failed";
        query.prepare("ROLLBACK;");
        query.exec();
        return false;
    } else {
        qDebug() << "Database.: [" << qry << "] succeded";
    }
    return true;
}

bool
runInsertProgress(int routine, int day, int movement)
{
    QSqlQuery query;
    query.prepare("INSERT INTO \"Progress\" (Routine,Day,Movement) "
                  "VALUES(:Routine,:Day,:Movement);");
    query.bindValue(":Routine", routine);
    query.bindValue(":Day", day);
    query.bindValue(":Movement", movement);
    if (!query.exec()) {
        qDebug() << "Database: [" << query.lastQuery() << "] failed";
        query.prepare("ROLLBACK;");
        query.exec();
        return false;
    } else {
        qDebug() << "Database.: [" << query.lastQuery() << "] succeded";
    }
    return true;
}
bool
initialize()
{
    QSqlQuery query;
    qDebug() << "Database: start";
    query.prepare("BEGIN TRANSACTION;");
    if(!query.exec()){
        qDebug() << "Database: begin transaction failed";
        query.prepare("COMMIT;");
        query.exec();
        return false;
    }
    if (!runQuery("CREATE TABLE User(Id INTEGER PRIMARY KEY,Name TEXT);")) {
        return false;
    }
    if (!runQuery(
          "CREATE TABLE Status(Id INTEGER PRIMARY KEY,  Routine INTEGER,  "
          "Pushups INTEGER,  Squats INTEGER,  Pullups INTEGER,  LegRaises "
          "INTEGER,  Bridges INTEGER,  HandstandPushups INTEGER);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE Routine(Id INTEGER PRIMARY KEY,Name TEXT);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE Day(Id INTEGER PRIMARY KEY, Name TEXT);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE Pushups(Id INTEGER PRIMARY KEY, Name TEXT);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE Squats(Id INTEGER PRIMARY KEY, Name TEXT);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE Pullups(Id INTEGER PRIMARY KEY, Name TEXT);")) {
        return false;
    }
    if (!runQuery(
          "CREATE TABLE LegRaises(Id INTEGER PRIMARY KEY, Name TEXT);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE Bridges(Id INTEGER PRIMARY KEY, Name TEXT);")) {
        return false;
    }
    if (!runQuery("CREATE TABLE HandstandPushups(Id INTEGER PRIMARY KEY, Name "
                  "TEXT);")) {
        return false;
    }
    if (!runQuery(
          "CREATE TABLE Set1(Id INTEGER PRIMARY KEY, Rest INTEGER, Set1 "
          "INTEGER, Set2 INTEGER, Set3 INTEGER, Set4 INTEGER, Set5 "
          "INTEGER, Set6 INTEGER, Set7 INTEGER, Set8 INTEGER);")) {
        return false;
    }
    if (!runQuery(
          "CREATE TABLE Set2(Id INTEGER PRIMARY KEY, Rest INTEGER, Set1 "
          "INTEGER, Set2 INTEGER, Set3 INTEGER, Set4 INTEGER, Set5 "
          "INTEGER, Set6 INTEGER, Set7 INTEGER, Set8 INTEGER);")) {
        return false;
    }
    if (!runQuery(
          "CREATE TABLE Set3(Id INTEGER PRIMARY KEY, Rest INTEGER, Set1 "
          "INTEGER, Set2 INTEGER, Set3 INTEGER, Set4 INTEGER, Set5 "
          "INTEGER, Set6 INTEGER, Set7 INTEGER, Set8 INTEGER);")) {
        return false;
    }

    if (!runQuery("CREATE TABLE Progress(Routine INTEGER, Day INTEGER, "
                  "Movement INTEGER);")) {
        return false;
    }
    if (!runQuery(
          "CREATE TABLE ProgressionIndex(Id INTEGER PRIMARY KEY,Pushups "
          "INTEGER,Squats INTEGER,Pullups INTEGER,LegRaises INTEGER,Bridges "
          "INTEGER,HandstandPushups INTEGER);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"User\" VALUES(1, 'User');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Status\" VALUES(1, 2, 8, 8, 1, 8, 1, 1);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Routine\" VALUES(1, 'new blood');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Routine\" VALUES(2, 'good behavior');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Routine\" VALUES(3, 'veterano');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(1, 'Domingo');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(2, 'Segunda');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(3, 'Terça');")){
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(4, 'Quarta');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(5, 'Quinta');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(6, 'Sexta');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Day\" VALUES(7, 'Sábado');")){
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(1, 'wall pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(2, 'incline pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(3, 'kneeling pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(4, 'half pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(5, 'full pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(6, 'close pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(7, 'uneven pushups');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Pushups\" VALUES(8, '1/2 one-arm pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(9, 'lever pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pushups\" VALUES(10, 'one-arm pushups');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Squats\" VALUES(1, 'shoulderstand squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(2, 'jackknife squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(3, 'supported squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(4, 'half squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(5, 'full squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(6, 'close squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(7, 'uneven squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(8, '1/2 one-leg squats');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Squats\" VALUES(9, 'assisted one-leg squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Squats\" VALUES(10, 'one-leg squats');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(1, 'vertical pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(2, 'horizontal pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(3, 'jackknife pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(4, 'half pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(5, 'full pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(6, 'close pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(7, 'uneven pullups');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Pullups\" VALUES(8, '1/2 one-arm pullups');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Pullups\" VALUES(9, 'assisted one-arm pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Pullups\" VALUES(10, 'one-arm pullups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"LegRaises\" VALUES(1, 'knee tucks');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"LegRaises\" VALUES(2, 'flat knee raises');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"LegRaises\" VALUES(3, 'flat bent leg raises');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"LegRaises\" VALUES(4, 'flat frog raises');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"LegRaises\" VALUES(5, 'flat straight leg raises');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"LegRaises\" VALUES(6, 'hanging knee raises');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"LegRaises\" VALUES(7, 'hanging bent leg raises');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"LegRaises\" VALUES(8, 'hanging frog raises');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"LegRaises\" VALUES(9, 'partial straight leg "
                  "raises');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"LegRaises\" VALUES(10, 'hanging straight leg "
                  "raises');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(1, 'short bridges');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(2, 'straight bridges');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(3, 'angled bridges');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(4, 'head bridges');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(5, 'half bridges');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(6, 'full bridges');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Bridges\" VALUES(7, 'wall walking bridges(down)');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Bridges\" VALUES(8, 'wall walking bridges(up)');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Bridges\" VALUES(9, 'closing bridges');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Bridges\" VALUES(10, 'stand-to-stand bridges');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"HandstandPushups\" VALUES(1, 'wall headstands');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"HandstandPushups\" VALUES(2, 'crow stands');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"HandstandPushups\" VALUES(3, 'wall handstands');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"HandstandPushups\" VALUES(4, 'half handstand "
                  "pushups');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"HandstandPushups\" VALUES(5, 'handstand pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"HandstandPushups\" VALUES(6, 'close handstand "
                  "pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"HandstandPushups\" VALUES(7, 'uneven "
                  "handstand pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"HandstandPushups\" VALUES(8, '1/2 one-arm "
                  "handstand pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"HandstandPushups\" VALUES(9, 'lever handstand "
                  "pushups');")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"HandstandPushups\" VALUES(10, 'one-arm "
                  "handstand pushups');")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(1, 60, 2, 3, 2, 2, 3, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(2, 60, 3, 4, 2, 3, 4, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(3, 60, 4, 5, 4, 4, 5, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(4, 60, 4, 6, 4, 4, 6, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(5, 60, 5, 6, 4, 4, 7, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(6, 60, 5, 7, 5, 5, 8, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(7, 60, 10, 12, 7, 7, 9, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(8, 60, 10, 12, 8, 8, 12, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set1\" VALUES(9, 60, 11, 13, 9, 9, 13, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(10, 60, 12, 14, 11, 10, 16, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(11, 60, 14, 16, 12, 12, 18, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(12, 60, 16, 18, 13, 13, 20, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(13, 60, 17, 19, 15, 15, 20, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(14, 45, 10, 10, 13, 13, 10, 10, "
                  "9, 25);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(15, 45, 13, 13, 15, 15, 12, 12, "
                  "10, 30);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(16, 60, 17, 19, 15, 15, 20, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(17, 45, 10, 10, 13, 13, 10, 10, "
                  "9, 25);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set1\" VALUES(18, 45, 13, 13, 15, 15, 12, 12, "
                  "10, 30);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(1, 60, 6, 6, 4, 4, 5, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(2, 60, 6, 8, 6, 6, 7, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(3, 60, 8, 10, 7, 7, 10, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(4, 60, 9, 11, 8, 8, 11, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(5, 60, 10, 12, 9, 9, 13, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(6, 60, 12, 13, 10, 10, 15, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(7, 60, 12, 17, 13, 13, 17, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(8, 60, 14, 19, 14, 14, 19, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set2\" VALUES(9, 60, 16, 21, 15, 15, 21, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(10, 60, 18, 22, 16, 16, 25, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(11, 60, 20, 25, 20, 20, 28, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(12, 60, 23, 28, 23, 23, 33, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(13, 60, 28, 35, 25, 22, 35, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(14, 45, 18, 18, 20, 20, 14, 14, "
                  "16, 40);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(15, 45, 18, 18, 20, 20, 17, 17, "
                  "20, 45);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(16, 60, 28, 35, 25, 22, 35, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(17, 45, 18, 18, 20, 20, 14, 14, "
                  "16, 40);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set2\" VALUES(18, 45, 18, 18, 20, 20, 17, 17, "
                  "20, 45);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(1, 60, 10, 12, 7, 7, 9, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(2, 60, 10, 12, 8, 8, 12, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(3, 60, 11, 15, 9, 9, 13, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(4, 60, 14, 14, 10, 10, 15, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(5, 60, 14, 16, 12, 12, 17, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(6, 60, 16, 17, 14, 14, 20, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(7, 60, 14, 18, 14, 14, 20, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(8, 60, 20, 25, 15, 15, 25, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(9, 60, 22, 30, 20, 20, 28, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(10, 60, 21, 25, 21, 21, 32, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(11, 60, 25, 29, 25, 25, 36, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(12, 60, 29, 33, 29, 29, 40, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(13, 60, 36, 40, 30, 24, 40, 0, "
                  "0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(14, 45, 19, 19, 22, 22, 18, 18, "
                  "22, 45);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(15, 45, 20, 20, 24, 24, 20, 20, "
                  "22, 50);")) {
        return false;
    }
    if (!runQuery(
          "INSERT INTO \"Set3\" VALUES(16, 60, 36, 0, 30, 24, 40, 0, 0, 0);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(17, 45, 19, 19, 22, 22, 18, 18, "
                  "22, 45);")) {
        return false;
    }
    if (!runQuery("INSERT INTO \"Set3\" VALUES(18, 45, 20, 20, 24, 24, 20, 20, "
                  "22, 50);")) {
        return false;
    }

    if (!runInsertProgress(1, Monday, Pushups)) {
        return false;
    }
    if (!runInsertProgress(1, Monday, LegRaises)) {
        return false;
    }
    if (!runInsertProgress(1, Thursday, Pullups)) {
        return false;
    }
    if (!runInsertProgress(1, Thursday, Squats)) {
        return false;
    }
    if (!runInsertProgress(2, Monday, Pushups)) {
        return false;
    }
    if (!runInsertProgress(2, Monday, LegRaises)) {
        return false;
    }
    if (!runInsertProgress(2, Wednesday, Pullups)) {
        return false;
    }
    if (!runInsertProgress(2, Wednesday, Squats)) {
        return false;
    }
    if (!runInsertProgress(2, Friday, HandstandPushups)) {
        return false;
    }
    if (!runInsertProgress(2, Friday, Bridges)) {
        return false;
    }
    if (!runInsertProgress(3, Monday, Pullups)) {
        return false;
    }
    if (!runInsertProgress(3, Tuesday, Bridges)) {
        return false;
    }
    if (!runInsertProgress(3, Wednesday, HandstandPushups)) {
        return false;
    }
    if (!runInsertProgress(3, Thursday, LegRaises)) {
        return false;
    }
    if (!runInsertProgress(3, Friday, Squats)) {
        return false;
    }
    if (!runInsertProgress(3, Saturday, Pushups)) {
        return false;
    }
    if (!runQuery("INSERT INTO \"ProgressionIndex\" VALUES(1,5,5,5,5,1,1);")) {
        return false;
    }
    query.prepare("COMMIT;");
    query.exec();
    return true;
}
int
getWeekDay()
{
    struct tm* ts;
    time_t timestamp = time(NULL);
    ts = localtime(&timestamp);
    return ts->tm_wday;
}

DbManager::DbManager(const QString& path)
  : m_user(1)
  , m_day(getWeekDay() + 1)
  , m_routine1(0)
  , m_routine2(0)
  , m_routine(1)
  , m_movement(1)
  , m_Pushups(1)
  , m_Squats(1)
  , m_Pullups(1)
  , m_LegRaises(1)
  , m_Bridges(1)
  , m_HandstandPushups(1)
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    qDebug() << path;
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
       QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='User'");
       int idName = query.record().indexOf("name");
       if (query.exec())
       {
          if (query.next())
          {
             qDebug() << "Tables already initialized!";
          }else{
              qDebug() << "initializing tables";
              if (initialize()) {
                  qDebug() << "tables ok";
              } else {
                  qDebug() << "create tables failed";
              }
          }
       }
    }

    refreshStatus();
    refreshRoutines();
}

QSqlDatabase
DbManager::db()
{
    return m_db;
}
void
DbManager::setUser(int user)
{
    m_user = user;
}
void
DbManager::setDay(int day)
{
    qDebug() << "setDay " << day;
    m_day = day;
}

void
DbManager::setRoutine1(int routine1)
{
    qDebug() << "setRoutine1 " << routine1;
    m_routine1 = routine1;
}

void
DbManager::setRoutine2(int routine2)
{
    qDebug() << "setRoutine2 " << routine2;
    m_routine2 = routine2;
}

int
DbManager::user() const
{
    qDebug() << "user " << m_user;
    return m_user;
}

int
DbManager::day() const
{
    qDebug() << "day " << m_day;
    return m_day;
}

int
DbManager::routine1() const
{
    qDebug() << "routine1 " << m_routine1;
    return m_routine1;
}

int
DbManager::routine2() const
{
    qDebug() << "routine2 " << m_routine2;
    return m_routine2;
}

int DbManager::routine() const
{
    qDebug() << "routine " << m_routine;
    return m_routine;
}

void DbManager::setRoutine(int routine)
{
    m_routine = routine;
}
void
DbManager::updateRoutine(int routine)
{
    QString qry;
    QSqlQuery query;
    if (m_routine == routine) {
        qDebug() << "updateRoutine " << m_routine << " " << routine;
        return;
    }
    qry =
      QString("UPDATE Status SET Routine = '%1' WHERE Id = (:Id)").arg(routine);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "runUpdateRoutine error: " << query.lastError();
    }
    m_routine = routine;
}
void
DbManager::updatePushups(int value)
{
    QString qry;
    QSqlQuery query;
    if (m_Pushups == value) {
        qDebug() << "updatePushups " << m_Pushups << " " << value;
        return;
    } else {
        qDebug() << "updatePushups " << m_Pushups << " " << value;
    }
    qry =
      QString("UPDATE Status SET Pushups = '%1' WHERE Id = (:Id)").arg(value);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "updatePushups error: " << query.lastError();
    }
    m_Pushups = value;
}
void
DbManager::updateSquats(int value)
{
    QString qry;
    QSqlQuery query;
    if (m_Squats == value) {
        qDebug() << "updateSquats " << m_Squats << " " << value;
        return;
    } else {
        qDebug() << "updateSquats " << m_Squats << " " << value;
    }
    qry =
      QString("UPDATE Status SET Squats = '%1' WHERE Id = (:Id)").arg(value);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "updateSquats error: " << query.lastError();
    }
    m_Squats = value;
}
void
DbManager::updatePullups(int value)
{
    QString qry;
    QSqlQuery query;
    if (m_Pullups == value) {
        qDebug() << "updatePullups " << m_Pullups << " " << value;
        return;
    } else {
        qDebug() << "updatePullups " << m_Pullups << " " << value;
    }
    qry =
      QString("UPDATE Status SET Pullups = '%1' WHERE Id = (:Id)").arg(value);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "updatePullups error: " << query.lastError();
    }
    m_Pullups = value;
}
void
DbManager::updateLegRaises(int value)
{
    QString qry;
    QSqlQuery query;
    if (m_LegRaises == value) {
        qDebug() << "updateLegRaises " << m_LegRaises << " " << value;
        return;
    } else {
        qDebug() << "updateLegRaises " << m_LegRaises << " " << value;
    }
    qry =
      QString("UPDATE Status SET LegRaises = '%1' WHERE Id = (:Id)").arg(value);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "updateLegRaises error: " << query.lastError();
    }
    m_LegRaises = value;
}
void
DbManager::updateBridges(int value)
{
    QString qry;
    QSqlQuery query;
    if (m_Bridges == value) {
        qDebug() << "updateBridges " << m_Bridges << " " << value;
        return;
    } else {
        qDebug() << "updateBridges " << m_Bridges << " " << value;
    }
    qry =
      QString("UPDATE Status SET Bridges = '%1' WHERE Id = (:Id)").arg(value);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "updateBridges error: " << query.lastError();
    }
    m_Bridges = value;
}
void
DbManager::updateHandstandPushups(int value)
{
    QString qry;
    QSqlQuery query;
    if (m_HandstandPushups == value) {
        qDebug() << "updateHandstandPushups " << m_HandstandPushups << " "
                 << value;
        return;
    } else {
        qDebug() << "updateHandstandPushups " << m_HandstandPushups << " "
                 << value;
    }
    qry = QString("UPDATE Status SET HandstandPushups = '%1' WHERE Id = (:Id)")
            .arg(value);
    qDebug() << qry;
    query.prepare(qry);
    query.bindValue(":Id", m_user);
    if (!query.exec()) {
        qDebug() << "updateHandstandPushups error: " << query.lastError();
    }
    m_HandstandPushups = value;
}
QStringList
DbManager::getUsers()
{
    QStringList list;
    QSqlQuery query("SELECT Id,Name FROM User;");
    int idName = query.record().indexOf("Name");
    while (query.next()) {
        QString name = query.value(idName).toString();
        qDebug() << "->" << name;
        list.append(name);
    }
    return list;
}
QStringList
DbManager::getWeeDays()
{
    QStringList list;
    QSqlQuery query("SELECT * FROM Day;");
    int idName = query.record().indexOf("Name");
    while (query.next()) {
        QString name = query.value(idName).toString();
        qDebug() << "->" << name;
        list.append(name);
    }
    return list;
}
QString
DbManager::getMovementName(int movement)
{
    qDebug() << "getMovementName " << movement;
    switch (movement) {
        case Pushups:
            return "Pushups";
        case Squats:
            return "Squats";
        case Pullups:
            return "Pullups";
        case LegRaises:
            return "LegRaises";
        case Bridges:
            return "Bridges";
        case HandstandPushups:
            return "HandstandPushups";
        default:
            return "unknown";
    }
}
QStringList
DbManager::getMovementNames(int movement)
{
    QStringList list;
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM %1;").arg(getMovementName(movement)));
    if (query.exec()) {
        qDebug() << "getMovementNames " << query.lastQuery();
        int idName = query.record().indexOf("Name");
        while (query.next()) {
            QString name = query.value(idName).toString();
            qDebug() << "-> " << name;
            list.append(name);
        }
    }
    return list;
}

void
DbManager::refreshStatus()
{

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM Status WHERE Id = %1;").arg(m_user));
    qDebug() << "refreshStatus <<<<<<<<<";
    if (query.exec()) {
        int idxRoutine = query.record().indexOf("Routine");
        int idxPushups = query.record().indexOf("Pushups");
        int idxSquats = query.record().indexOf("Squats");
        int idxPullups = query.record().indexOf("Pullups");
        int idxLegRaises = query.record().indexOf("LegRaises");
        int idxBridges = query.record().indexOf("Bridges");
        int idxHandstandPushups = query.record().indexOf("HandstandPushups");
        qDebug() << "refreshStatus " << query.lastQuery();
        if (query.next()) {
            m_routine = query.value(idxRoutine).toInt();
            m_Pushups = query.value(idxPushups).toInt();
            m_Squats = query.value(idxSquats).toInt();
            m_Pullups = query.value(idxPullups).toInt();
            m_LegRaises = query.value(idxLegRaises).toInt();
            m_Bridges = query.value(idxBridges).toInt();
            m_HandstandPushups = query.value(idxHandstandPushups).toInt();
        }
    }
}
void
DbManager::refreshRoutines()
{
    int count = 0;
    QSqlQuery query;
    query.prepare(
      QString("SELECT * FROM Progress WHERE Routine = %1 and Day = %2;")
        .arg(m_routine)
        .arg(m_day));
    qDebug() << "refreshRoutines " << m_routine << " " << m_day;

    if (query.exec()) {
        int idxMovement = query.record().indexOf("Movement");
        qDebug() << "refreshRoutines " << query.lastQuery();
        qDebug() << "idxMovement " << idxMovement;
        /*if (query.next()) {
            qDebug() << "next ";
            if (count == 0) {
                m_routine1 = query.value(idxMovement).toInt();
                ++count;
            } else {
                m_routine2 = query.value(idxMovement).toInt();
            }
        }*/
        QSqlRecord rec = query.record();
        int cols = rec.count();
        for (int c = 0; c < cols; c++)
            qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

        for (int r = 0; query.next(); r++) {
            m_routine = query.value(idxMovement).toInt();
            for (int c = 0; c < cols; c++) {
                qDebug() << QString("Row %1, %2: %3")
                              .arg(r)
                              .arg(rec.fieldName(c))
                              .arg(query.value(c).toString());
            }
        }
    }
    qDebug() << "refreshRoutines " << m_routine1 << " " << m_routine2;
}
void
DbManager::getStatus(int user,
                     int* Routine,
                     int* Pushups,
                     int* Squats,
                     int* Pullups,
                     int* LegRaises,
                     int* Bridges,
                     int* HandstandPushups)
{

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM Status WHERE Id = %1;").arg(user));
    if (query.exec()) {
        int idxRoutine = query.record().indexOf("Routine");
        int idxPushups = query.record().indexOf("Pushups");
        int idxSquats = query.record().indexOf("Squats");
        int idxPullups = query.record().indexOf("Pullups");
        int idxLegRaises = query.record().indexOf("LegRaises");
        int idxBridges = query.record().indexOf("Bridges");
        int idxHandstandPushups = query.record().indexOf("HandstandPushups");
#ifdef DEBUG
        QSqlRecord rec = query.record();
        int cols = rec.count();
        for (int c = 0; c < cols; c++)
            qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

        for (int r = 0; query.next(); r++) {
            m_routine = query.value(idxRoutine).toInt();
            for (int c = 0; c < cols; c++) {
                qDebug() << QString("Row %1, %2: %3")
                              .arg(r)
                              .arg(rec.fieldName(c))
                              .arg(query.value(c).toString());
            }
        }
#else
        if (query.next()) {
            m_routine = query.value(idxRoutine).toInt();
            m_Pushups = query.value(idxPushups).toInt();
            m_Squats = query.value(idxSquats).toInt();
            m_Pullups = query.value(idxPullups).toInt();
            m_LegRaises = query.value(idxLegRaises).toInt();
            m_Bridges = query.value(idxBridges).toInt();
            m_HandstandPushups = query.value(idxHandstandPushups).toInt();

            qDebug() << "   idxRoutine " << idxRoutine << " " << m_routine;
            qDebug() << "   idxPushups " << idxPushups << " " << m_Pushups;
            qDebug() << "   idxSquats " << idxSquats << " " << m_Squats;
            qDebug() << "   idxPullups " << idxPullups << " " << m_Pullups;
            qDebug() << "   idxLegRaises " << idxLegRaises << " "
                     << m_LegRaises;
            qDebug() << "   idxBridges " << idxBridges << " " << m_Bridges;
            qDebug() << "   idxHandstandPushups " << idxHandstandPushups << " "
                     << m_HandstandPushups;
        }
#endif

        *Routine = m_routine;
        *Pushups = m_Pushups;
        *Squats = m_Squats;
        *Pullups = m_Pullups;
        *LegRaises = m_LegRaises;
        *Bridges = m_Bridges;
        *HandstandPushups = m_HandstandPushups;
    }
}
int
DbManager::getProgressionIndex(int movement)
{
    QSqlQuery query;
    query.prepare(
      QString("SELECT * FROM ProgressionIndex WHERE Id = %1;").arg(m_user));
    if (query.exec()) {
        qDebug() << "getProgressionIndex " << query.lastQuery();
        if (query.next()) {
            int idMovement = 0;
            switch (movement) {
                case Pushups:
                    idMovement = query.record().indexOf("Pushups");
                    break;
                case Squats:
                    idMovement = query.record().indexOf("Squats");
                    break;
                case Pullups:
                    idMovement = query.record().indexOf("Pullups");
                    break;
                case LegRaises:
                    idMovement = query.record().indexOf("LegRaises");
                    break;
                case Bridges:
                    idMovement = query.record().indexOf("Bridges");
                    break;
                case HandstandPushups:
                    idMovement = query.record().indexOf("HandstandPushups");
                    break;
            }
            return query.value(idMovement).toInt();
        }
    }
    return 0;
}
QList<int>
DbManager::getProgress(int day)
{
    QList<int> list;
    QSqlQuery query;
    query.prepare(
      QString("SELECT * FROM Progress WHERE Routine = %1 AND Day = %2;")
        .arg(m_routine)
        .arg(day));
    qDebug() << "getProgress " << m_routine << " " << m_day;
    if (query.exec()) {
        qDebug() << "getProgress " << query.lastQuery();
        int idMovement = query.record().indexOf("Movement");
        qDebug() << "getProgress " << idMovement;
        while (query.next()) {
            int movement = query.value(idMovement).toInt();
            qDebug() << "getProgress next " << movement;
            qDebug() << getMovementName(movement);
            list.append(movement);
        }
    }

    return list;
}
int
DbManager::getMovementProgress(int movement)
{
    switch (movement) {
        case Pushups:
            return m_Pushups;
        case Squats:
            return m_Squats;
        case Pullups:
            return m_Pullups;
        case LegRaises:
            return m_LegRaises;
        case Bridges:
            return m_Bridges;
        case HandstandPushups:
            return m_HandstandPushups;
    }
}

int
DbManager::getRoutine() const
{
    return m_routine;
}

int
DbManager::getRoutine1() const
{
    return m_routine1;
}

int
DbManager::getRoutine2() const
{
    return m_routine2;
}
