#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>

struct Position {
    int x;
    int y;
};

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = nullptr);
    ~Display();

    bool getNewTouchEvent();
    Position getTouchEvent();

    void update(int x, int y);

private:
    bool newTouchEvent;
    Position touchEvent;

};

#endif // DISPLAY_H
