#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_3_3_Core>

class Texture : protected QOpenGLFunctions_3_3_Core
{
public:
    Texture();

    void loadFromFile(const QString& fn);
    GLuint _texture;

private:
    QVector<quint8> imageToBytes(const QImage& image);

};

#endif // TEXTURE_H
