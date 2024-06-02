#include "Reflection.h"
#include "glwidget.h"

const int WIDTH = 512;
const int HEIGHT = 512;

void Reflection::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vs->compileSourceFile("reflection.vert");
	cout << "vs log: " << vs->log().toStdString() << "\n";

	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs->compileSourceFile("reflection.frag");
	cout << "Fs log: " << fs->log().toStdString() << "\n";

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "program log: " << program->log().toStdString() << "\n";

	GLWidget& g = *glwidget();
	g.makeCurrent();

	//Setup texture
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures(1,&textureId);
	g.glBindTexture(GL_TEXTURE_2D,textureId);
	g.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	// Resize to power-of-two viewport
    g.resize(WIDTH,HEIGHT);

	//Turns out this is needed
	recreateMirror();
}

void Reflection::onObjectAdd()
{
	recreateMirror();
}

bool Reflection::paintGL()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();

	program->bind();

	QMatrix4x4 MVP = g.camera()->projectionMatrix() * g.camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);

	QMatrix4x4 RM = computeReflectionMatrix(0,-1,0,g.scene()->boundingBox().min().y());
	program->setUniformValue("reflectionMatrix", RM);

	program->setUniformValue("doreflect",false);

	g.glClearColor(1,1,1,0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	if(drawPlugin()) drawPlugin()->drawScene();

	// Save drawing into the texture
	g.glBindTexture(GL_TEXTURE_2D, textureId);
	g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, WIDTH, HEIGHT);
	g.glGenerateMipmap(GL_TEXTURE_2D);

	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	program->setUniformValue("reflectionMatrix", QMatrix4x4(1.0f,0.0f,0.0f,0.0f,
															0.0f,1.0f,0.0f,0.0f,
															0.0f,0.0f,1.0f,0.0f,
															0.0f,0.0f,0.0f,1.0f));
	if (drawPlugin()) drawPlugin()->drawScene();

	program->setUniformValue("colorMap", 0);
	program->setUniformValue("SIZE", float(WIDTH));
	program->setUniformValue("doreflect",true);

	// Draw mirror quad	
	g.glBindVertexArray(mirrorVAO);
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	g.glBindVertexArray(0);
	g.glBindTexture(GL_TEXTURE_2D,0);
	g.defaultProgram()->bind();
	return true; // return true only if implemented
}

void Reflection::recreateMirror()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	GLuint mirrorVBO;
	float y = g.scene()->boundingBox().min().y();
	float xmin = g.scene()->boundingBox().min().x();
	float xmax = g.scene()->boundingBox().max().x();
	float zmin = g.scene()->boundingBox().min().z();
	float zmax = g.scene()->boundingBox().max().z();

	std::vector<float> vertices = 
	{
		xmin, y, zmin,
		xmax, y, zmin,
		xmin, y, zmax,
		xmax, y, zmax
	};

	g.glGenVertexArrays(1, &mirrorVAO);
	g.glBindVertexArray(mirrorVAO);

	g.glGenBuffers(1,&mirrorVBO);
	g.glBindBuffer(GL_ARRAY_BUFFER, mirrorVBO);
	g.glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(0);
	g.glBindVertexArray(0);
}

QMatrix4x4 Reflection::computeReflectionMatrix(float a, float b, float c, float d)
{
	QMatrix4x4 mat
	(	1.0f - 2.0f*a*a, -2.0f*a*b,      -2*a*c,        -2*a*d,
		-2.0f*a*b,        1.0f-2.0f*b*b, -2.0f*b*c,      -2.0f*b*d,
		-2.0f*a*c,       -2.0f*b*c,      1.0f-2.0f*c*c, -2.0f*c*d,
		0.0f,             0.0f,          0.0f,            1.0f
	);
	return mat;
}
