#include "window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QClipboard>
#include <QApplication>
#include "board.h"
#include "setting.h"

Window::Window(QWidget *parent)
    : QWidget{parent}
{
    QPixmap bkgnd(":/background");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setContentsMargins(20, 20, 20, 20);

    QTextEdit* output = new QTextEdit();
    output->setReadOnly(true);

    QPushButton* copy = new QPushButton("&Copy");
    QPushButton* clear = new QPushButton("&Clear");
    QPushButton* setting = new QPushButton("&Setting");

    QClipboard* clipboard = QApplication::clipboard();

    connect(copy, &QPushButton::clicked, output, [clipboard, output](){
        clipboard->setText(output->toPlainText());
    });

    Setting* settingwindow = new Setting();

    connect(setting, &QPushButton::clicked, settingwindow, &Setting::exec);

    QHBoxLayout* h_2 = new QHBoxLayout();
    h_2->addWidget(copy);
    h_2->addWidget(clear);
    h_2->addWidget(setting);

    QComboBox* boardsize = new QComboBox();
    boardsize->addItem("5 x 5");
    boardsize->addItem("7 x 7");
    boardsize->addItem("9 x 9");

    QRadioButton* screen = new QRadioButton("Screen Coordinate");
    screen->setChecked(true);
    screen->setStyleSheet(
        "QRadioButton {"
        "   color: white;"
        "}"
        );

    QRadioButton* cartesian = new QRadioButton("Cartesian Coordinate");
    cartesian->setStyleSheet(
        "QRadioButton {"
        "   color: white;"
        "}"
        );

    QButtonGroup* coordinate = new QButtonGroup();
    coordinate->addButton(screen);
    coordinate->addButton(cartesian);

    QVBoxLayout* v_2 = new QVBoxLayout();
    v_2->addWidget(screen);
    v_2->addWidget(cartesian);

    QVBoxLayout* v_1 = new QVBoxLayout();
    v_1->addWidget(output);
    v_1->addLayout(h_2);
    v_1->addWidget(boardsize);
    v_1->addLayout(v_2);

    QHBoxLayout* h_1 = new QHBoxLayout();
    h_1->setSpacing(10);

    Board* board = new Board();
    h_1->addLayout(board);
    h_1->addLayout(v_1);

    this->setLayout(h_1);

    connect(board, &Board::sendDatas, output, [output](QString data){ output->setText(data);});
    connect(clear, &QPushButton::clicked, board, &Board::initBlocks);

    connect(screen, &QRadioButton::toggled, board, [screen, board](){
        if(screen->isChecked()) board->updateCoordinate(Coordinate::SCREEN);
    });

    connect(cartesian, &QRadioButton::toggled, board, [cartesian, board](){
        if(cartesian->isChecked()) board->updateCoordinate(Coordinate::CARTESIAN);
    });

    connect(boardsize, QOverload<int>::of(&QComboBox::currentIndexChanged), board, &Board::updateBoard);

    connect(setting, &QPushButton::clicked, board, &Board::openSetting);
    connect(board, &Board::sendSetting, settingwindow, &Setting::loadSetting);

    connect(settingwindow, &Setting::sendSetting, board, &Board::setSetting);

}
