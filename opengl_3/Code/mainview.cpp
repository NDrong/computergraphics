#include "mainview.h"
#include <cmath>
#include "vertex.h"

#include <QDateTime>

#include <animations/rotationanimation.h>
#include <animations/scaleanimation.h>

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
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    objects.push_back(std::make_unique<SceneObject>());

    objects[0]->createFromModelResource(":/models/cat.obj", {0, 0, -2});
    objects[0]->texture.loadFromFile(":/textures/cat_diff.png");

    createShaderProgram();

    lightPosition = {0, 1000, -1};
    material = {0.5f, 0.8f, 0.3f};

    animationController.addAnimation(objects[0].get(), std::make_unique<RotationAnimation>(360, QVector3D(1.0f, 0, 0)));
    animationController.addAnimation(objects[0].get(), std::make_unique<ScaleAnimation>(180, 0.5f, 2.0f));

    timer.start(1000 / 60);
}

void MainView::timerTick() {
    animationController.tick();

    update();
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

    // Link the variables to the shaders.
    sLocModelTransform[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::NORMAL] = shaders[ShadingMode::NORMAL].uniformLocation("normalTransform");

    sLocModelTransform[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("normalTransform");
    sLocMaterial[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("material");
    sLocLightPosition[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("lightPosition");
    sLocTextureSampler[ShadingMode::PHONG] = shaders[ShadingMode::PHONG].uniformLocation("textureSampler");

    sLocModelTransform[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("modelTransform");
    sLocProjectionTransform[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("projectionTransform");
    sLocNormal[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("normalTransform");
    sLocMaterial[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("material");
    sLocLightPosition[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("lightPosition");
    sLocTextureSampler[ShadingMode::GOURAUD] = shaders[ShadingMode::GOURAUD].uniformLocation("textureSampler");
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

    if (currentShadingMode == ShadingMode::GOURAUD || currentShadingMode == ShadingMode::PHONG) {
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
