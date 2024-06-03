#ifndef _SELECTMOUSE_H
#define _SELECTMOUSE_H

#include "plugin.h" 

class SelectMouse: public QObject, public Plugin
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
	 void mouseReleaseEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
	QOpenGLShader* m_vs = nullptr;
	QOpenGLShader* m_fs = nullptr;
	QOpenGLShaderProgram* m_program = nullptr;
};

#endif
