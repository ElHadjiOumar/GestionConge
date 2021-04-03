#ifndef PROFILUI_H
#define PROFILUI_H

#include <QSqlTableModel>
#include <QMainWindow>
#include "dbaccess.h"
#include "usermodel.h"

namespace Ui {
class ProfilUI;
}

class ProfilUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfilUI(QWidget *parent = nullptr);
    explicit ProfilUI(User *user,QObject *controller);

    void saisirCoordonnes(User *employe);

    ~ProfilUI();

private:
    Ui::ProfilUI *ui;
};

#endif // PROFILUI_H
