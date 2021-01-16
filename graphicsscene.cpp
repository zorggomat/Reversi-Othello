#include "graphicsscene.h"

#include <QDebug>

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent) {}

GraphicsScene::~GraphicsScene() {}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    emit clicked(Position(point.x() / 67 + 1, point.y() / 67 + 1));
}
