#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "animations/animationcontroller.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <memory>
#include <QMatrix4x4>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger{};
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaders[4];

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD, WATER,
    };

    MainView(QWidget *parent = nullptr);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);

    QMatrix4x4 projection, view;
    GLint sLocModelTransform[4], sLocProjectionTransform[4], sLocNormal[4], sLocLightPosition[3], sLocMaterial[3], sLocTextureSampler[3], sLocNormalSampler[3];
    GLint sLocViewTransform[4];

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( const QOpenGLDebugMessage& Message );
    void timerTick();

private:
    void createShaderProgram();
    AnimationController animationController;
    std::vector<std::unique_ptr<SceneObject>> objects;
    ShadingMode currentShadingMode = ShadingMode::WATER;
    QVector3D lightPosition;
    QVector3D material;

};

#endif // MAINVIEW_H
