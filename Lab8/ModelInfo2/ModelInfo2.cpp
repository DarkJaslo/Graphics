#include "ModelInfo2.h"
#include "glwidget.h"

void ModelInfo2::onPluginLoad()
{
	
}

void ModelInfo2::preFrame()
{
	
}

void ModelInfo2::postFrame()
{
	int objects, faces, vertices;
	objects = faces = vertices = 0;
	Scene* sc = scene();

	objects = sc->objects().size();

	for(const Object& obj : sc->objects())
	{
		faces += obj.faces().size();
		vertices += obj.vertices().size();
	}

	QFont font;
	font.setPixelSize(20);
	m_painter.begin(glwidget());
	m_painter.setFont(font);
	int x = 15;
	int y = 40;
	QString text = "Objects: ";
	text.append(QString::number(objects));
	text.append("  Faces: ");
	text.append(QString::number(faces));
	text.append("  Vertices: ");
	text.append(QString::number(vertices));

	m_painter.drawText(x, y, text);    
	m_painter.end();
}

void ModelInfo2::onObjectAdd()
{
	
}

bool ModelInfo2::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo2::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo2::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo2::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo2::mouseMoveEvent(QMouseEvent *)
{
	
}

