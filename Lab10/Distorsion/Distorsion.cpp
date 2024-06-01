#include "Distorsion.h"
#include "glwidget.h"

const unsigned int WIDTH = 512;
const unsigned int HEIGHT = 512;

void Distorsion::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vs->compileSourceFile("distort.vert");
	cout << "vs log: " << vs->log().toStdString() << "\n";

	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs->compileSourceFile("distort.frag");
	cout << "Fs log: " << fs->log().toStdString() << "\n";

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "program log: " << program->log().toStdString() << "\n";

	GLWidget& g = *glwidget();

	//Setup texture
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures(1,&textureId);
	g.glBindTexture(GL_TEXTURE_2D,textureId);
	g.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	// Resize to power-of-two viewport
    g.resize(WIDTH,HEIGHT);

	m_point = std::chrono::high_resolution_clock::now();
}

void drawRect(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, 0, 
                            1, -1, 0, 
                           -1,  1, 0, 
                            1,  1, 0};

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}


bool Distorsion::paintGL()
{
	//Pass 1: build texture
	GLWidget &g = *glwidget();
	g.makeCurrent();

	g.glClearColor(0,0,0,0);

	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	if(drawPlugin()) drawPlugin()->drawScene();
	//QMatrix4x4 MVP = g.camera()->projectionMatrix() * g.camera()->viewMatrix();
	//g.defaultProgram()->setUniformValue("modelViewProjectionMatrix", MVP);

	// Get texture
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
			  WIDTH, HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);

	//Draw scene using distortmap
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	program->bind();
	program->setUniformValue("colorMap", 0);
	// quad covering viewport 
    program->setUniformValue("modelViewProjectionMatrix", QMatrix4x4() ); 
	program->setUniformValue("SIZE", float(WIDTH)); 

	auto mark = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float,std::milli> elapsed = mark-m_point;
	m_point = mark;
	time += elapsed.count()/1000.0f;
	program->setUniformValue("time", time);

	drawRect(g);

	g.defaultProgram()->bind();
	g.glBindTexture(GL_TEXTURE_2D, 0);

	return true; // return true only if implemented
}

