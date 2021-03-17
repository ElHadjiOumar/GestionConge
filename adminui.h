#ifndef ADMINUI_H
#define ADMINUI_H

#include <QSqlTableModel>
#include <QMainWindow>
#include "dbaccess.h"
#include "usermodel.h"

namespace Ui {
class AdminUI;
}

class AdminUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminUI(QWidget *parent = nullptr);
    explicit AdminUI(QObject *controller);

    bool closeConfirmation();
    void activateCreate();
    void activateUpdate();
    ~AdminUI();

private slots:
    void onTableClicked(const QModelIndex &index);
    void onRadioCreateClicked();
    void onRadioUpdateClicked();
    void onSubmitClicked();
    void onDeleteClicked();
    void onClearClicked();
    void onSearchClicked();

private:
    Ui::AdminUI *ui;
    UserModel *model;

    bool getUserInformations(User *user);
    void setUpTableView();
    void populate(uint row);
    void createUser();
    void updateUser();
    void clear();
    void selectFirstRow();
};

#endif // ADMINUI_H
