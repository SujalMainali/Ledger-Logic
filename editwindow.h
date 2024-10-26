#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EditWindow; }
QT_END_NAMESPACE

class EditWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditWindow(QWidget *parent = nullptr);
    ~EditWindow();

    void ShowChildAccountDetail(int16_t currentAccountId);
    void ShowParentAccountDetail(int8_t currentAccountId);

private slots:
    void PopulateSelectHeader();

    void on_Cancel_clicked();

    void on_Save_clicked();
    int16_t GetTypeIdFromType(QString type);

private:
    Ui::EditWindow *ui;
};
#endif // EDITWINDOW_H
