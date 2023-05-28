#ifndef STRUCT_H
#define STRUCT_H

struct ColorRGB 
{
    float r, g, b;
    ColorRGB(float red, float green, float blue)
        : r(red), g(green), b(blue)
    {
    }
};

struct ImgTexture
{
  GLuint img;
  ColorRGB color;
  int rot;
};

#endif