#include "ShowDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	
}

void ShowDegree::preFrame()
{
	
}

void ShowDegree::postFrame()
{
	int vertices = 0;
	int edges = 0;

	Scene* sc = scene();

	for(Object const& obj : sc->objects())
	{
		for(Face const& face : obj.faces())
		{
			edges += face.numVertices();
		}
		vertices += obj.vertices().size();
	}

	float averageDegree = 0.0f;
	if(vertices != 0)
	{
		averageDegree = float(edges)/vertices;
	}

	QFont font;
	font.setPixelSize(20);
	m_painter.begin(glwidget());
	m_painter.setFont(font);
	int x = 15;
	int y = 40;
	QString text = "Degree: " + QString::number(averageDegree);
	m_painter.drawText(x, y, text);    
	m_painter.end();
}

void ShowDegree::onObjectAdd()
{
	
}

bool ShowDegree::drawScene()
{
	return false; // return true only if implemented
}

bool ShowDegree::drawObject(int)
{
	return false; // return true only if implemented
}

bool ShowDegree::paintGL()
{
	return false; // return true only if implemented
}

void ShowDegree::keyPressEvent(QKeyEvent *)
{
	
}

void ShowDegree::mouseMoveEvent(QMouseEvent *)
{
	
}

