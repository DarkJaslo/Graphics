#ifndef _DRAWSMOOTH_H
#define _DRAWSMOOTH_H

#include "plugin.h" 

class DrawSmooth: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
    ~DrawSmooth();
	void cleanup();

	void onSceneClear();
	void onPluginLoad();
    void onObjectAdd();
	bool drawScene();
	bool drawObject(int);
  private:
  	struct MyPoint
	{
		MyPoint(){}
		MyPoint(float x, float y, float z)
			: x(x),y(y),z(z){}
		float x,y,z;
		friend bool operator<(const MyPoint& a, const MyPoint& b)
		{
			if(a.x != b.x) return a.x < b.x;
			if(a.y != b.y) return a.y < b.y;
			return a.z < b.z;
		}
	};
	void addVBO(unsigned int object);
	void manageVertex(Point P,
					Vector N,
					std::pair<float,float> TC,
					std::vector<unsigned int>& indices,
					std::vector<int>& references,
					std::vector<float>& normals,
					std::vector<float>& colors,
					std::vector<float>& texCoords,
					std::map<MyPoint,int>& verticesMap);

	// add private methods and attributes here

	// We will create a VBO for each object in the scene
	vector<GLuint> VAOs;          // ID of VAOs
	vector<GLuint> coordBuffers;  // ID of vertex coordinates buffer 
	vector<GLuint> normalBuffers; // ID of normal components buffer 
	vector<GLuint> stBuffers;     // ID of (s,t) buffer 
	vector<GLuint> colorBuffers;  // ID of color buffer  
	vector<GLuint> indexBuffers;  // ID of index buffer
	vector<GLuint> numIndices;    // Size (number of indices) in each index buffer
};

#endif
