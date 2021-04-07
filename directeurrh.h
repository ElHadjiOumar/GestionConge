#ifndef DIRECTEURRH_H
#define DIRECTEURRH_H

#include <QSqlQueryModel>
#include "authentification.h"
#include "dbaccess.h"
#include <user.h>
#include "usermodel.h"
#include <QPrinter>

#include <QSqlQuery>
#include <QStandardItemModel>
#include <QPainter>
#include <QtDebug>
#include <QVariant>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QStyleOptionViewItem>

namespace Ui {
class DirecteurRH;
}

class DirecteurRH : public QMainWindow
{
    Q_OBJECT

public:
    explicit DirecteurRH(QWidget *parent = nullptr);
    explicit DirecteurRH(QObject *controller);
    ~DirecteurRH();

private slots:
        void onExtractClicked();
        void onPrintClicked();
        void onExtractClickedConge();
        void onPrintClickedConge();


private:
    Ui::DirecteurRH *ui;
    UserModel *modelUser;
    UserModel *modelConge;

    void setInformation();
    void setInformationConge();
    void setUpTableView();
     void setUpTableViewConge();
     QVariant getValueAt(int ix, int jx);
     bool createHtmlTableFromModel();
     void printTable(QPrinter &printer);
     QStyleOptionViewItem viewOptions() const;
};

#endif // DIRECTEURRH_H
