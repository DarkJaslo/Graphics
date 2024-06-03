#include "SelectMouse.h"
#include "glwidget.h"

void SelectMouse::onPluginLoad()
{
	// Load shaders
	m_vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	m_vs->compileSourceFile("./mouse.vert");
	std::cout << "VS log:" << m_vs->log().toStdString() << "\n";

	m_fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	m_fs->compileSourceFile("./mouse.frag");
	std::cout << "FS log:" << m_fs->log().toStdString() << "\n";

	m_program = new QOpenGLShaderProgram(this);
	m_program->addShader(m_vs);
	m_program->addShader(m_fs);
	m_program->link();
	std::cout << "Link log: " << m_program->log().toStdString() << "\n";
}

void SelectMouse::preFrame()
{
	
}

void SelectMouse::postFrame()
{
	
}

void SelectMouse::onObjectAdd()
{
	
}

bool SelectMouse::drawScene()
{
	return false; // return true only if implemented
}

bool SelectMouse::drawObject(int)
{
	return false; // return true only if implemented
}

bool SelectMouse::paintGL()
{
	return false; // return true only if implemented
}

void SelectMouse::keyPressEvent(QKeyEvent *)
{
	
}

void SelectMouse::mouseMoveEvent(QMouseEvent * )
{
	
}

/* FOR SIMPLICITY...*/
std::vector<QVector4D> COLORS = 
{
	QVector4D(1.0f,0.0f,0.0f,1.0f), //red
	QVector4D(0.0f,1.0f,0.0f,1.0f), //green
	QVector4D(0.0f,0.0f,1.0f,1.0f), //blue
	QVector4D(0.0f,1.0f,1.0f,1.0f), //etc
	QVector4D(1.0f,0.0f,1.0f,1.0f), //etc
	QVector4D(1.0f,1.0f,0.0f,1.0f), //etc
};

void encodeID(int i, GLubyte* color)
{
	vector<int> col(4,0);
	if(i == 0)
	{
		col[0] = 255;
	}
	else if(i == 1)
	{
		col[1] = 255;
	}
	else if(i == 2)
	{
		col[2] = 255;
	}

	color[0] = col[0];
	color[1] = col[1];
	color[2] = col[2];
	color[3] = col[3];
}

void SelectMouse::mouseReleaseEvent(QMouseEvent * e)
{
	if(not ((e->modifiers() & Qt::ControlModifier) and e->button() & Qt::LeftButton))
	{
		cout << " invalid\n";
		return;
	}
	else
	{
		cout << "valid\n";
	}

	GLWidget &g = *glwidget();
	g.makeCurrent();

	g.glClearColor(1,1,1,0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_program->bind();

	/*for(auto& c : COLORS)
	{
		cout << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << "\n";
	}*/

	QMatrix4x4 MVP = g.camera()->projectionMatrix() * g.camera()->viewMatrix();
	m_program->setUniformValue("modelViewProjectionMatrix", MVP);


	for(unsigned int i = 0; i < g.scene()->objects().size(); ++i)
	{
		m_program->setUniformValue("color", COLORS[i%COLORS.size()]);
		drawPlugin()->drawObject(i);
	}

	int x = e->x();
    int y = glwidget()->height()-e->y();
    GLubyte read[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

	cout << "read:\n";
	cout << int(read[0]) << ", ";
	cout << int(read[1]) << ", ";
	cout << int(read[2]) << ", ";
	cout << int(read[3]) << "\n";

	int id = -1;

	for(unsigned int i = 0; i < COLORS.size(); ++i)
	{
		GLubyte col[4];
		encodeID(i,col);
		bool same = true;
		
		for(int j = 0; j < 3; ++j)
		{
			if(read[j] != col[j]) 
				same = false;
		}

		if(same)
		{
			id = i;
		}
	}

	if(id >= 0)
	{
		cout << "selected object: " << id << "\n";
		scene()->setSelectedObject(id);
	}
	else{
		cout << "no selected object\n";
	}
	g.update();

	g.defaultProgram()->bind();
}

