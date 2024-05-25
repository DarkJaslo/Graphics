#include "ModelInfo.h"
#include "glwidget.h"

void ModelInfo::onPluginLoad()
{
	
}

void ModelInfo::preFrame()
{
	
}

void ModelInfo::postFrame()
{
	Scene* sc = scene();
	const std::vector<Object>& obj = sc->objects();
	if(obj.size() != m_objects)
	{
		m_objects = obj.size();
		std::cout << "Objects: " << obj.size() << "\n";
	}
	int faces = 0;
	int vertices = 0;

	for(const Object& o : obj)
	{
		faces += o.faces().size();
		vertices += o.vertices().size(); 
	}

	if(faces != m_faces or vertices != m_vertices)
	{
		m_faces = faces;
		m_vertices = vertices;
		std::cout << "No. faces: " << faces << "\nNo. vertices: " << vertices << "\n"; 
	}
}

void ModelInfo::onObjectAdd()
{
	
}

bool ModelInfo::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo::mouseMoveEvent(QMouseEvent *)
{
	
}

