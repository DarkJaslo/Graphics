#ifndef _DISTORSION_H
#define _DISTORSION_H

#include "plugin.h" 

class Distorsion: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();

	 bool paintGL();
  private:
	// add private methods and attributes here

	QOpenGLShader* vs = nullptr;
	QOpenGLShader* fs = nullptr;
	QOpenGLShaderProgram* program = nullptr;

	GLuint textureId;

	std::chrono::_V2::system_clock::time_point m_point;
	float time = 0.0f;
};

#endif
