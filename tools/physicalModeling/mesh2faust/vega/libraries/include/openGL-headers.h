#if defined(_WIN32) || defined(WIN32)
  #include <Windows.h>
#endif

#if defined(_WIN32) || defined(WIN32) || defined(linux) || defined (__linux__)
  #include <GL/gl.h> 
  #include <GL/glu.h> 
  #include <GL/glut.h>
#elif defined(__APPLE__)
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <GLUT/glut.h>
#endif

