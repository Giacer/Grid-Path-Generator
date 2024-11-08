#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <Qvector2d.h>

enum BlockStyle {
    BLACK, WHITE, PAWN
};

class Block : public QLabel {
    Q_OBJECT
public:
    BlockStyle style;
    QVector2D position;
    bool selected;

    Block(int x, int y, BlockStyle s);
    Block(QVector2D pos, BlockStyle s);

    void imageUpdate();
    void update();
    void unselected();

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void sendPosition(QVector2D pos);
};

#endif // BLOCK_H
