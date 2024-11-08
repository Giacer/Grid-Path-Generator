#include "block.h"
#include <cmath>
#include <QPixmap>

Block::Block(int x, int y, BlockStyle s) : Block(QVector2D(x, y), s){}

Block::Block(QVector2D pos, BlockStyle s) : selected(false) {
    position = pos;
    style = s;

    switch(s) {
    case BlockStyle::BLACK: {
        setPixmap(QPixmap(":/b"));
        break;
    }
    case BlockStyle::WHITE: {
        setPixmap(QPixmap(":/w"));
        break;
    }
    case BlockStyle::PAWN: {
        setPixmap(QPixmap(":/p"));
        break;
    }}

    setScaledContents(true);
}

void Block::imageUpdate() {
    if(style == BlockStyle::BLACK) {
        if(selected)
            setPixmap(QPixmap(":/b_active"));
        else
            setPixmap(QPixmap(":/b"));
    }
    else if(style == BlockStyle::WHITE){
        if(selected)
            setPixmap(QPixmap(":/w_active"));
        else
            setPixmap(QPixmap(":/w"));
    }
}

void Block::update() {
    if(style == BlockStyle::PAWN) return;
    emit sendPosition(position);
}

void Block::unselected() {
    if(!selected) return;
    selected = false;
    imageUpdate();
    emit sendPosition(position);
}

void Block::mousePressEvent(QMouseEvent* event) {
    QLabel::mouseMoveEvent(event);
    selected = !selected;
    imageUpdate();
    update();
}
