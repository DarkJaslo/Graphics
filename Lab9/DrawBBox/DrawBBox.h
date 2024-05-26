#ifndef _DRAWBBOX_H
#define _DRAWBBOX_H

#include "plugin.h" 

/*
	Draws the bounding box of the whole scene
*/

class DrawBBox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
  private:
	// add private methods and attributes here

	QOpenGLShader* m_vs = nullptr;
	QOpenGLShader* m_fs = nullptr;
	QOpenGLShaderProgram* m_program = nullptr;

	unsigned int m_vao;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};

#endif
