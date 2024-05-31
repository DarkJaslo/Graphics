#include "TextureSplatting.h"
#include "glwidget.h"

void TextureSplatting::onPluginLoad()
{
	// Load, compile and link shaders
	vs = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vs->compileSourceFile("splatting.vert");
	cout << "VS log:" << vs->log().toStdString() << "\n";

	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs->compileSourceFile("splatting.frag");
	cout << "FS log:" << fs->log().toStdString() << "\n";

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	cout << "Link log:" << program->log().toStdString() << "\n";

	GLWidget &g = *glwidget();

	// Load Texture 1
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	

	//"./noise_smooth.png"
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	g.glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2	
	QImage img1("./rock.png");	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 3	
	QImage img2("./grass.png");	
	QImage im2 = img2.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE2);
	g.glGenTextures( 1, &textureId2);
	g.glBindTexture(GL_TEXTURE_2D, textureId2);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::preFrame()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();

	program->bind();

	//bind textures
	g.glActiveTexture(GL_TEXTURE0);
	g.glBindTexture(GL_TEXTURE_2D,textureId0);
	g.glActiveTexture(GL_TEXTURE1);
	g.glBindTexture(GL_TEXTURE_2D,textureId1);
	g.glActiveTexture(GL_TEXTURE2);
	g.glBindTexture(GL_TEXTURE_2D,textureId2);

	program->setUniformValue("noise0", 0);
	program->setUniformValue("rock1", 1);
	program->setUniformValue("grass2", 2);
	program->setUniformValue("radius", float(scene()->boundingBox().radius()));
	program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
	program->setUniformValue("normalMatrix",camera()->viewMatrix().normalMatrix());
}

void TextureSplatting::postFrame()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();

	g.defaultProgram()->bind();
	g.glActiveTexture(GL_TEXTURE0);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	g.glActiveTexture(GL_TEXTURE1);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	g.glActiveTexture(GL_TEXTURE2);
	g.glBindTexture(GL_TEXTURE_2D, 0);
}
