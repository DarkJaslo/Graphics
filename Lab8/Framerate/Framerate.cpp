#include "Framerate.h"
#include "glwidget.h"

void Framerate::onPluginLoad()
{
	m_point = std::chrono::high_resolution_clock::now();
	m_framerate = 0.0f;
}

void Framerate::preFrame()
{

}

void Framerate::postFrame()
{
	auto aux = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float,std::milli> elapsed = aux-m_point;
	if(m_iterations % 64 == 0)
		m_framerate = 1.0f/(elapsed.count()/1000.0f);
	m_point = aux;

	++m_iterations;

	QFont font;
	font.setPixelSize(20);
	m_painter.begin(glwidget());
	m_painter.setFont(font);
	int x = 15;
	int y = 40;
	QString text = "FPS: " + QString::number(m_framerate);
	m_painter.drawText(x, y, text);    
	m_painter.end();
}

void Framerate::onObjectAdd()
{
	
}

bool Framerate::drawScene()
{
	return false; // return true only if implemented
}

bool Framerate::drawObject(int)
{
	return false; // return true only if implemented
}

bool Framerate::paintGL()
{
	return false; // return true only if implemented
}

void Framerate::keyPressEvent(QKeyEvent *)
{
	
}

void Framerate::mouseMoveEvent(QMouseEvent *)
{
	
}

