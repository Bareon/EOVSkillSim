#ifndef LINEDRAW_H
#define LINEDRAW_H

#include <QWidget>

//Unused
class LineDraw : public QWidget {
public:
  LineDraw(
    QWidget *from
    , QWidget *to
    , QWidget *parent = nullptr);
  virtual ~LineDraw() = default;

protected:
  virtual void paintEvent(QPaintEvent *e) final override;

private:
  QWidget *_from;
  QWidget *_to;
};

#endif // LINEDRAW_H
