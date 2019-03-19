#include "mainview.h"
#include <cmath>
#include "vertex.h"

#include <QDateTime>
#include <QtMath>

#include <animations/rotationanimation.h>
#include <animations/scaleanimation.h>
#include <animations/translationanimation.h>
#include <animations/sequentialanimation.h>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTick()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();

    qDebug() << "MainView destructor";
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    // glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    objects.push_back(std::make_unique<SceneObject>());

    objects[0]->createFromModelResource(":/models/grid.obj", {0, 0, -2});

    objects[0]->setWaveParameters(0, 0.1f, float(8.0 * M_PI), float(0.5 * M_PI));
    objects[0]->setWaveParameters(1, 0.15f, float(2.0 * M_PI), float(-1.0 * M_PI));

    createShaderProgram();

    cameraPosition = QVector3D(0, 0, 0);
    cameraUp = QVector3D(0, 1, 0);
    setYawPitch(0, 0);

    lightPosition = {0, 1000, -1};
    material = {0.5f, 0.8f, 0.3f};

    /*
    auto seq = new SequentialAnimation();
    seq->addAnimationNL(std::make_unique<RotationAnimation>(360, QVector3D(1.0f, 0, 0)));
    seq->addAnimationNL(std::make_unique<RotationAnimation>(360, QVector3D(0, 1.0f, 0)));
    seq->addAnimationNL(std::make_unique<RotationAnimation>(360, QVector3D(0, 0, 1.0f)));
    //animationController.addAnimation(objects[0].get(), std::unique_ptr<Animation>(seq));
    //animationController.addAnimation(objects[0].get(), std::make_unique<TranslationAnimation>(720, QVector3D(-5, 0, -10), QVector3D(5, 0, -10)));
    animationController.addAnimation(objects[0].get(), std::make_unique<ScaleAnimation>(180, 1.5f, 2.0f));
    */
    view.setToIdentity();

    timer.start(1000 / 60);
}

void MainView::timerTick() {
    float tickSpeed = 0.1f;
    animationController.tick();

    if (keysDown[(int)'A']) {
        cameraPosition -= tickSpeed * QVector3D::crossProduct(cameraFront, cameraUp).normalized();
    }
    if (keysDown[(int)'D']) {
        cameraPosition += tickSpeed * QVector3D::crossProduct(cameraFront, cameraUp).normalized();
    }
    if (keysDown[(int)'W']) {
        cameraPosition += tickSpeed * cameraFront;
    }
    if (keysDown[(int)'S']) {
        cameraPosition -= tickSpeed * cameraFront;
    }
    if (keysDown[Qt::Key::Key_Space]) {
        cameraPosition += tickSpeed * cameraUp;
    }
    if (keysDown[Qt::Key::Key_Shift]) {
        cameraPosition -= tickSpeed * cameraUp;
    }

    update();

    ticks += 0.1f;
}

void MainView::createShaderProgram()
{
    shaders[ShadingMode::NORMAL].addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    shaders[ShadingMode::NORMAL].addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    shaders[ShadingMode::NORMAL].link();

    shaders[ShadingMode::PHONG].addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_phong.glsl");
    shaders[ShadingMode::PHONG].addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader_phong.glsl");
    shaders[ShadingMode::PHONG].link();

    shaders[ShadingMode::GOURAUD].addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_gouraud.glsl");
    shaders[ShadingMode::GOURAUD].addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader_gouraud.glsl");
    shaders[ShadingMode::GOURAUD].link();

    shaders[ShadingMode::WATER].addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader_water.glsl");
    shaders[ShadingMode::WATER].addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader_water.glsl");
    shaders[ShadingMode::WATER].link();


    // Link the variables to the shaders.
    sLocModelTransform[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("normalTransform");
    sLocViewTransform[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("viewTransform");

    sLocModelTransform[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("normalTransform");
    sLocMaterial[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("material");
    sLocLightPosition[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("lightPosition");
    sLocTextureSampler[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("textureSampler");
    sLocViewTransform[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("viewTransform");

    sLocModelTransform[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("normalTransform");
    sLocMaterial[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("material");
    sLocLightPosition[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("lightPosition");
    sLocTextureSampler[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("textureSampler");
    sLocViewTransform[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("viewTransform");

    sLocModelTransform[ShadingMode::WATER] = shaders[ShadingMode::WATER].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::WATER] = shaders[ShadingMode::WATER].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::WATER] = shaders[ShadingMode::WATER].uniformLocation("normalTransform");
    sLocViewTransform[ShadingMode::WATER] = shaders[ShadingMode::WATER].uniformLocation("viewTransform");
    sLocWaveAmplitudes = shaders[ShadingMode::WATER].uniformLocation("waveAmplitudes[0]");
    sLocWaveFrequencies = shaders[ShadingMode::WATER].uniformLocation("waveFrequencies[0]");
    sLocWavePhases = shaders[ShadingMode::WATER].uniformLocation("wavePhases[0]");
    sLocTime = shaders[ShadingMode::WATER].uniformLocation("time");
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaders[currentShadingMode].bind();

    glUniformMatrix4fv(sLocProjectionTransform[currentShadingMode], 1, false, projection.data());

    QMatrix4x4 view;
    view.lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    //view.setToIdentity();
    //view.translate(cameraPosition);
    glUniformMatrix4fv(sLocViewTransform[currentShadingMode], 1, false, view.data());

    if (currentShadingMode == ShadingMode::GOURAUD || currentShadingMode == ShadingMode::PHONG || currentShadingMode == ShadingMode::WATER) {
        glUniform3f(sLocMaterial[currentShadingMode], material.x(), material.y(), material.z());
        glUniform3f(sLocLightPosition[currentShadingMode], lightPosition.x(), lightPosition.y(), lightPosition.z());
    }

    // Draw here
    for (auto& object : objects) {
        object->bind();

        if (currentShadingMode == ShadingMode::GOURAUD || currentShadingMode == ShadingMode::PHONG) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, object->texture._texture);
            glUniform1i(sLocTextureSampler[currentShadingMode], 0);
        } else if (currentShadingMode == ShadingMode::WATER) {
            glUniform1fv(sLocWaveAmplitudes, 2, object->waveAmplitudes);
            glUniform1fv(sLocWaveFrequencies, 2, object->waveFrequencies);
            glUniform1fv(sLocWavePhases, 2, object->wavePhases);
            glUniform1fv(sLocTime, 1, &ticks);
        }

        QMatrix3x3 normals;
        normals = object->transform.normalMatrix();
        glUniformMatrix3fv(sLocNormal[currentShadingMode], 1, false, normals.data());
        glUniformMatrix4fv(sLocModelTransform[currentShadingMode], 1, false, object->transform.data());
        glDrawArrays(GL_TRIANGLES, 0, GLsizei(object->numVertices()));
    }

    shaders[currentShadingMode].release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
    projection.setToIdentity();
    projection.perspective(60, float(newWidth) / float(newHeight), 0.01f, 10000.0f);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    qDebug() << rotateX << "\n";
    for (auto& object : objects) {
        object->setRotation(rotateX, rotateY, rotateZ);
    }
    update();
}

void MainView::setScale(int scale)
{
    for (auto& object : objects) {
        object->setScaling(scale / 100.0f);
    }
    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    currentShadingMode = shading;
    update();
}

void MainView::setYawPitch(float yaw, float pitch)
{
    if (pitch > 89.99f) {
        pitch = 89.99f;
    }
    if (pitch < -89.99f) {
        pitch = -89.99f;
    }

    float dirX = cosf(qDegreesToRadians(pitch)) * cosf(qDegreesToRadians(yaw));
    float dirY = sinf(qDegreesToRadians(pitch));
    float dirZ = cosf(qDegreesToRadians(pitch)) * sinf(qDegreesToRadians(yaw));
    QVector3D dir(dirX, dirY, dirZ);

    cameraFront = dir.normalized();

    MainView::yaw = yaw;
    MainView::pitch = pitch;
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( const QOpenGLDebugMessage& Message ) {
    qDebug() << " → Log:" << Message;
}
