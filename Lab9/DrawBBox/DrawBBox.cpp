#include "DrawBBox.h"
#include "glwidget.h"

void DrawBBox::onPluginLoad()
{
	// Load shaders
	m_vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	m_vs->compileSourceFile("./bbox.vert");
	std::cout << "VS log:" << m_vs->log().toStdString() << "\n";

	m_fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	m_fs->compileSourceFile("./bbox.frag");
	std::cout << "FS log:" << m_fs->log().toStdString() << "\n";

	m_program = new QOpenGLShaderProgram(this);
	m_program->addShader(m_vs);
	m_program->addShader(m_fs);
	m_program->link();
	std::cout << "Link log: " << m_program->log().toStdString() << "\n";


	// Create VAO
	vertices = {
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};
	
	indices =
	{
		0, 1, 2,
		1, 3, 2,
		1, 5, 3,
		5, 7, 3,
		5, 6, 7,
		5, 4, 6,
		4, 2, 0,
		4, 6, 2,
		0, 1, 4,
		1, 5, 4,
		2, 3, 6,
		3, 7, 6
	};

	std::cout << "vertices size: " << vertices.size() << "\n";

	GLWidget& g = *glwidget();
	g.glGenVertexArrays(1, &m_vao);
	g.glBindVertexArray(m_vao);

	unsigned int coordBufferID;
	g.glGenBuffers(1, &coordBufferID);
	g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	g.glEnableVertexAttribArray(0);

	unsigned int indexBufferID;
	g.glGenBuffers(1, &indexBufferID);
	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);
	
	g.glBindVertexArray(0);
}

void DrawBBox::postFrame()
{
	GLWidget& g = *glwidget();
	Scene* sc = scene();

	m_program->bind();
	QMatrix4x4 VP = camera()->projectionMatrix()*camera()->viewMatrix();
	m_program->setUniformValue("modelViewProjectionMatrix", VP);	
	g.glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	for (Object const& obj : sc->objects())
	{
		Box const& box = obj.boundingBox();
		
		Point newMax = box.max()-box.min();

		m_program->setUniformValue("scale", newMax);
		m_program->setUniformValue("translate", box.min());

		g.glBindVertexArray(m_vao);
		g.glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
		g.glBindVertexArray(0);
	}

	g.glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	m_program->release();
}
