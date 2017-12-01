#include "linedraw.h"
#include <QPainter>

//Unused
LineDraw::LineDraw(
    QWidget *from
    , QWidget *to
    , QWidget *parent) :
    QWidget(parent),
    _from(from),
    _to(to)
{

}

void LineDraw::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);

  QPainter painter(this);

  QPoint start = _from->mapToGlobal(_from->rect().center());
  QPoint end = _to->mapToGlobal(_to->rect().center());
  painter.drawLine(mapFromGlobal(start), mapFromGlobal(end));
}
