#pragma once
#include "GL\glew.h"
#include <iostream>
#include <sstream>

#define ASSERT(x) if (!x) __debugbreak()
#define GLCALL(x) GLClearError();\
x;\
ASSERT(GLLogCall())

extern void GLClearError();
extern bool GLLogCall();

