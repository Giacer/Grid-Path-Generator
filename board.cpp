#include "board.h"
#include "block.h"
#include <algorithm>
#include <QSizePolicy>

Board::Board() : coord(Coordinate::SCREEN){
    setBoard(5);
    setSpacing(0);
    setContentsMargins(0, 0, 0, 0);

    for(int i = 0; i < 5; i++) {
        setRowStretch(i, 1);
        setColumnStretch(i, 1);
    }

    order = Order::X_ACENDING;
    expression = "(&x, &y)";
    delimiter = ", ";
}

void Board::setBoard(int size) {
    if(this->size == size) return;

    clearBoard();

    this->size = size;

    int gap = (size - 1) / 2;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            Block* block;
            if(i == j && i == gap)
                block = new Block(i, j, BlockStyle::PAWN);
            else if((i + j) % 2 == 0)
                block = new Block(i, j, BlockStyle::BLACK);
            else
                block = new Block(i, j, BlockStyle::WHITE);
            connect(block, &Block::sendPosition, this, &Board::updateData);
            connect(this, &Board::initBlocks, block, &Block::unselected);
            container.push_back(block);
            this->addWidget(block, i, j);
        }
    }
}

void Board::clearBoard() {
    while (QLayoutItem *item = this->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    container.clear();
}

void Board::setOrder(Order order) {
    this->order = order;
}

void Board::setCoordinate(Coordinate coord) {
    this->coord = coord;
}

void Board::updateBoard(int size) {
    switch(size) {
    case 0: {
        setBoard(5);
        break;
    }
    case 1: {
        setBoard(7);
        break;
    }
    case 2: {
        setBoard(9);
        break;
    }}
}

void Board::updateData(QVector2D data) {
    int index = std::find(datas.begin(), datas.end(), data) - datas.begin();

    if(index == datas.size())
        datas.push_back(data);
    else
        datas.takeAt(index);

    parsingDatas();
}

void Board::updateCoordinate(Coordinate coord) {
    setCoordinate(coord);
    parsingDatas();
}

void Board::updateOrder(Order order) {
    setOrder(order);
}

void Board::setSetting(QString exp, QString del, int sort) {
    expression = exp;
    delimiter = del;
    order = (Order)sort;
    parsingDatas();
}

void Board::openSetting() {
    emit sendSetting(expression, delimiter, (int)order);
}

void Board::parsingDatas() {
    QStringList list;
    int gap = (size - 1) / 2;

    if(order == Order::X_ACENDING) {
        std::sort(datas.begin(), datas.end(), [](const QVector2D &a, const QVector2D &b) {
            if (a.x() == b.x()) return a.y() < b.y();
            return a.x() < b.x();
        });
    }
    else if(order == Order::X_DESCENDING) {
        std::sort(datas.begin(), datas.end(), [](const QVector2D &a, const QVector2D &b) {
            if (a.x() == b.x()) return a.y() > b.y();
            return a.x() > b.x();
        });
    }
    else if(order == Order::Y_ACENDING) {
        std::sort(datas.begin(), datas.end(), [](const QVector2D &a, const QVector2D &b) {
            if (a.y() == b.y()) return a.x() < b.x();
            return a.y() < b.y();
        });
    }
    else {//order == Order::Y_DESCENDING
        std::sort(datas.begin(), datas.end(), [](const QVector2D &a, const QVector2D &b) {
            if (a.y() == b.y()) return a.x() > b.x();
            return a.y() > b.y();
        });
    }

    for(auto it : datas) {
        QString format = expression;
        if(coord == Coordinate::SCREEN) {
            format.replace("&x", QString::number(it.x() - gap));
            format.replace("&y", QString::number(it.y() - gap));
        }
        else { // coord == Coordinate::CARTESIAN
            format.replace("&x", QString::number(it.x() - gap));
            format.replace("&y", QString::number(gap - it.y()));
        }
        list.append(format);
    }

    QString data = list.join(delimiter);
    emit sendDatas(data);
}
