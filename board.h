#ifndef BOARD_H
#define BOARD_H

#include <QGridLayout.h>
#include <qvector.h>
#include <qvector2d.h>
#include <qstring>
#include "block.h"

enum class Order {
    X_ACENDING, Y_ACENDING, X_DESCENDING, Y_DESCENDING
};

enum class Coordinate {
    SCREEN, CARTESIAN
};

class Board : public QGridLayout {
    Q_OBJECT
public:
    Board();

    void setBoard(int size);
    void clearBoard();
    void setCoordinate(Coordinate coord);
    void setOrder(Order order);

signals:
    void sendDatas(QString data);
    void sendSetting(QString exp, QString del, int sort);
    void initBlocks();

public slots:
    void updateBoard(int size);
    void updateData(QVector2D data);
    void updateCoordinate(Coordinate coord);
    void updateOrder(Order order);
    void setSetting(QString exp, QString del, int sort);
    void openSetting();

private:
    QVector<Block*> container;
    QVector<QVector2D> datas;
    int size;
    Coordinate coord;

    QString expression;
    QString delimiter;
    Order order;

    void parsingDatas();
};

#endif // BOARD_H
