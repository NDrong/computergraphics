#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "sceneobject.h"

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

    QOpenGLShaderProgram shaders[3];

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);

    QMatrix4x4 projection;
    GLint sLocModelTransform[3], sLocProjectionTransform[3], sLocNormal[3], sLocLightPosition[3], sLocMaterial[3], sLocTextureSampler[3], sLocNormalSampler[3];

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

private:
    void createShaderProgram();
    std::vector<std::unique_ptr<SceneObject>> objects;
    ShadingMode currentShadingMode = ShadingMode::PHONG;
    QVector3D lightPosition;
    QVector3D material;

};

#endif // MAINVIEW_H
