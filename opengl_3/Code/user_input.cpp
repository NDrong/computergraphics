#include "mainview.h"

#include <QDebug>

// Triggered by pressing a key
void MainView::keyPressEvent(QKeyEvent *ev)
{
    float step = 0.5;
    switch(ev->key()) {
    case 'A':
    case 'S':
    case 'D':
    case 'W':
    case Qt::Key::Key_Shift:
    case Qt::Key::Key_Space:
        if (!ev->isAutoRepeat()) {
            keysDown[ev->key()] = true;
        }
        break;
    default:
        // ev->key() is an integer. For alpha numeric characters keys it equivalent with the char value ('A' == 65, '1' == 49)
        // Alternatively, you could use Qt Key enums, see http://doc.qt.io/qt-5/qt.html#Key-enum
        qDebug() << ev->key() << "pressed";
        break;
    }

    // Used to update the screen after changes
    update();
}

// Triggered by releasing a key
void MainView::keyReleaseEvent(QKeyEvent *ev)
{
    switch(ev->key()) {
    case 'A':
    case 'S':
    case 'D':
    case 'W':
    case Qt::Key::Key_Shift:
    case Qt::Key::Key_Space:
        if (!ev->isAutoRepeat()) {
            keysDown[ev->key()] = false;
        }
        break;
    default:
        qDebug() << ev->key() << "released";
        break;
    }

    update();
}

// Triggered by clicking two subsequent times on any mouse button
// It also fires two mousePress and mouseRelease events!
void MainView::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse double clicked:" << ev->button();

    update();
}

// Triggered when moving the mouse inside the window (only when the mouse is clicked!)
void MainView::mouseMoveEvent(QMouseEvent *ev)
{
    float dX = ev->x() - lastMousePosition.x();
    float dY = ev->y() - lastMousePosition.y();

    dX *= 0.05f;
    dY *= 0.05f;

    setYawPitch(yaw + dX, pitch + dY);

    lastMousePosition.setX(ev->x());
    lastMousePosition.setY(ev->y());
}

// Triggered when pressing any mouse button
void MainView::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse button pressed:" << ev->button();
    lastMousePosition.setX(ev->x());
    lastMousePosition.setY(ev->y());

    update();
    // Do not remove the line below, clicking must focus on this widget!
    this->setFocus();
}

// Triggered when releasing any mouse button
void MainView::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse button released " << ev->button();

    update();
}

// Triggered when clicking scrolling with the scroll wheel on the mouse
void MainView::wheelEvent(QWheelEvent *ev)
{
    // Implement something
//    view.rotate(ev->delta() < 0 ? -1 : 1, QVector3D(0, 1, 0));

    update();
}
