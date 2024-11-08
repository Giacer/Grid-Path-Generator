#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class Setting : public QDialog
{
Q_OBJECT
public:
    Setting();

public slots:
    void loadSetting(QString exp, QString del, int sort);

signals:
    void sendSetting(QString exp, QString del, int sort);

private:
    QLineEdit* expression;
    QLineEdit* delimiter;
    QComboBox* sorting;

    QPushButton* apply;
    QPushButton* reset;

    bool isCorrectExpreesion();

private slots:
    void applySetting();
    void resetSetting();
};

#endif // SETTING_H
