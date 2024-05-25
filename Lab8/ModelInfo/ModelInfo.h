#ifndef _MODELINFO_H
#define _MODELINFO_H

#include "plugin.h" 

/*
	Plugin that displays info about the scene after each frame:

	- Number of objects
	- Number of faces
	- Number of vertices

	This is only printed when changes occur.
*/

class ModelInfo: public QObject, public Plugin
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

	unsigned int m_objects = 0;
	int m_faces = 0;
	int m_vertices = 0;
};

#endif
