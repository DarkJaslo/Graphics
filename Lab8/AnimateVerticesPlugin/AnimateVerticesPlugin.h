#ifndef _ANIMATEVERTICESPLUGIN_H
#define _ANIMATEVERTICESPLUGIN_H

#include "plugin.h" 

/*
	Plugin that uses the shaders from the "Animate vertices (1) exercise"
*/

class AnimateVerticesPlugin: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
	QOpenGLShader* vs = nullptr;
	QOpenGLShader* fs = nullptr;
	QOpenGLShaderProgram* program = nullptr;
	std::chrono::_V2::system_clock::time_point m_point;
	float time = 0.0f;
};

#endif
