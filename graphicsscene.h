#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "position.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphicsScene(QObject *parent = 0);
    ~GraphicsScene();

signals:
    void clicked(Position);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
