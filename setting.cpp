#include "setting.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

Setting::Setting() {

    auto h_1 = new QHBoxLayout();
    h_1->addWidget(new QLabel("Expression"));
    h_1->addWidget(expression = new QLineEdit());

    auto h_2 = new QHBoxLayout();
    h_2->addWidget(new QLabel("Delimiter"));
    h_2->addWidget(delimiter = new QLineEdit());

    auto h_3 = new QHBoxLayout();
    h_3->addWidget(new QLabel("Sorting"));
    h_3->addWidget(sorting = new QComboBox());

    sorting->addItem("Ascending By X");
    sorting->addItem("Ascending By Y");
    sorting->addItem("Descending by X");
    sorting->addItem("Descending by Y");

    auto h_4 = new QHBoxLayout();
    h_4->addWidget(apply = new QPushButton("Apply"));
    h_4->addWidget(reset = new QPushButton("Reset"));

    auto v = new QVBoxLayout();
    v->addLayout(h_1);
    v->addLayout(h_2);
    v->addLayout(h_3);
    v->addLayout(h_4);

    this->setLayout(v);

    connect(expression, &QLineEdit::textChanged, [this](QString text){
        if(isCorrectExpreesion())
            expression->setStyleSheet("");
        else
            expression->setStyleSheet("border: 1px solid red;");
    });

    connect(apply, &QPushButton::clicked, this, [this](){
        if(isCorrectExpreesion()) {
            applySetting();
            close();
        }
        else
            QMessageBox::warning(this, "Invalid Input", "Expression must include both &x and &y.");
    });
    connect(reset, &QPushButton::clicked, this, &Setting::resetSetting);
}

bool Setting::isCorrectExpreesion() {
    auto exp = expression->text();
    if(exp.contains("&x") && exp.contains("&y")) return true;
    return false;
}

void Setting::applySetting() {
    emit sendSetting(expression->text(), delimiter->text(), sorting->currentIndex());
}

void Setting::resetSetting() {
    expression->setText("(&x, &y)");
    delimiter->setText(", ");
}

void Setting::loadSetting(QString exp, QString del, int sort) {
    expression->setText(exp);
    delimiter->setText(del);
    sorting->setCurrentIndex(sort);
}
