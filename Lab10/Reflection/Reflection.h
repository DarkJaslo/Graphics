#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h" 

class Reflection: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();

	 void onObjectAdd();

	 bool paintGL();
  private:

	 GLuint mirrorVAO, textureId;
	 QOpenGLShader* vs = nullptr;
	 QOpenGLShader* fs = nullptr;
	 QOpenGLShaderProgram* program = nullptr;

	 void recreateMirror();
	 QMatrix4x4 computeReflectionMatrix(float,float,float,float);

	// add private methods and attributes here
};

#endif
