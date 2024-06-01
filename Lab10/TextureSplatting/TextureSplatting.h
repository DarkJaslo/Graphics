#ifndef _TEXTURESPLATTING_H
#define _TEXTURESPLATTING_H

#include "plugin.h" 

class TextureSplatting: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
  private:
	// add private methods and attributes here
	QOpenGLShader* vs;
	QOpenGLShader* fs;
	QOpenGLShaderProgram* program;
	GLuint textureId0, textureId1, textureId2;
};

#endif
