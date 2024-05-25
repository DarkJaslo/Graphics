#include "AnimateVerticesPlugin.h"
#include "glwidget.h"

void AnimateVerticesPlugin::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("./vs.vert");
	std::cout << "VS log:" << vs->log().toStdString() << "\n";
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("./fs.frag");
	std::cout << "FS log:" << fs->log().toStdString() << "\n";

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	std::cout << "Link log: " << program->log().toStdString() << "\n";

	m_point = std::chrono::high_resolution_clock::now();
}

void AnimateVerticesPlugin::preFrame()
{
	program->bind();
	auto mark = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float,std::milli> elapsed = mark-m_point;
	m_point = mark;
	time += elapsed.count()/1000.0f;
	program->setUniformValue("time", time);
	QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
}

void AnimateVerticesPlugin::postFrame()
{
	program->release();
}

void AnimateVerticesPlugin::onObjectAdd()
{
	
}

bool AnimateVerticesPlugin::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVerticesPlugin::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVerticesPlugin::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVerticesPlugin::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVerticesPlugin::mouseMoveEvent(QMouseEvent *)
{
	
}

