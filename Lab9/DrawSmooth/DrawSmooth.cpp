#include "DrawSmooth.h"
#include "glwidget.h"
#include <cmath>
#include <cassert>
#include <set>

DrawSmooth::~DrawSmooth()
{
	cleanup();
}

void DrawSmooth::cleanup()
{
	GLWidget &g = *glwidget();
	g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
	g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
	g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
	g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
	g.glDeleteBuffers(indexBuffers.size(), &indexBuffers[0]);
	g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
	coordBuffers.clear();
	normalBuffers.clear();
	stBuffers.clear();
	colorBuffers.clear();
	VAOs.clear();
	indexBuffers.clear();
	numIndices.clear();
}

void DrawSmooth::onSceneClear()
{
	cleanup();
}

void DrawSmooth::onPluginLoad()
{
	for(unsigned int i = 0; i < scene()->objects().size(); ++i)
	{
		addVBO(i);
	}
}

void DrawSmooth::onObjectAdd()
{
	addVBO( scene()->objects().size()-1 );
}

bool DrawSmooth::drawScene()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	GLint program;
	g.glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	GLint loc = g.glGetUniformLocation(program,"objectID");

	for(unsigned int i = 0; i < VAOs.size(); ++i)
	{
		if(loc >= 0) g.glUniform1i(loc,i);
		drawObject(i);
	}
	return true; // return true only if implemented
}

bool DrawSmooth::drawObject(int i)
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	g.glBindVertexArray(VAOs[i]);
	g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);
	g.glBindVertexArray(0);
	return true; // return true only if implemented
}

// Private
void DrawSmooth::addVBO(unsigned int currentObject)
{
	Object const& obj = scene()->objects()[currentObject];

	std::vector<unsigned int> indices;
	std::vector<int> references;
	std::vector<float> vertices;
	std::map<MyPoint, int> verticesMap;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<float> texCoords;

	auto verts = obj.vertices();
	auto norms = obj.vertNormals();
	auto coords = obj.vertTexCoords();

	for(auto&& f: obj.faces())
	{
		for(int i = 0; i < 3; ++i)
		{
			Point P = verts[f.vertexIndex(i)].coord();
			MyPoint Pt(P.x(),P.y(),P.z());
			verticesMap[Pt]++;
		}
	}

	references = std::vector<int>(verticesMap.size(),0);
	{
		int i = 0;
		for(auto it = verticesMap.begin(); it != verticesMap.end(); ++it)
		{
			vertices.push_back(it->first.x);
			vertices.push_back(it->first.y);
			vertices.push_back(it->first.z);
			references[i] = it->second;
			it->second = i;
			++i;
		}
	}
	colors.resize(vertices.size());
	normals.resize(vertices.size());
	texCoords.resize((vertices.size()/3)*2);

	for(auto&& f: obj.faces())
	{
		for(int i = 0; i < 3; ++i)
		{
			Point P = verts[f.vertexIndex(i)].coord();
			Vector N = norms[f.normalIndex(i)];
			std::pair<float,float> TC = coords[f.texcoordsIndex(i)];
			manageVertex(P,N,TC,indices,normals,colors,texCoords,verticesMap);
		}
	}

	cout << "Indices size: " << indices.size() << ". Vertices size: " << vertices.size() << "\n";
	cout << "Faces: " << obj.faces().size() << "\n";
	assert(indices.size() == 3*obj.faces().size());

	for(unsigned int i = 0; i < references.size(); ++i)
	{
		assert(references[i] > 0);
	}

	cout << "norms: " << normals.size() << "  cols: " << colors.size() << "  coords: " << texCoords.size() << "\n";

	assert(vertices.size() == normals.size());
	assert(vertices.size() == colors.size());
	assert(vertices.size()*2 == 3*texCoords.size());

	for(unsigned int i = 0; i < verticesMap.size(); ++i)
	{
		normals[3*i] /= references[i];
		normals[3*i+1] /= references[i];
		normals[3*i+2] /= references[i];

		colors[3*i] /= references[i];
		colors[3*i+1] /= references[i];
		colors[3*i+2] /= references[i];
		
		texCoords[2*i] /= references[i];
		texCoords[2*i+1] /= references[i];
	}

	GLWidget &g = *glwidget();
	GLuint VAO;
	g.glGenVertexArrays(1, &VAO);
	VAOs.push_back(VAO);
	g.glBindVertexArray(VAO);

	GLuint coordBufferID;
	g.glGenBuffers(1,&coordBufferID);
	coordBuffers.push_back(coordBufferID);

	GLuint normalBufferID;
	g.glGenBuffers(1, &normalBufferID);
	normalBuffers.push_back(normalBufferID);
	
	GLuint stBufferID;
	g.glGenBuffers(1, &stBufferID);
	stBuffers.push_back(stBufferID);
	
	GLuint colorBufferID;
	g.glGenBuffers(1, &colorBufferID);
	colorBuffers.push_back(colorBufferID);

	GLuint indexBufferID;
	g.glGenBuffers(1, &indexBufferID);
	indexBuffers.push_back(indexBufferID);

	numIndices.push_back(indices.size());

	g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
  	g.glEnableVertexAttribArray(0);

	g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(1);

	g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(2);

	g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(3);

	g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

	g.glBindBuffer(GL_ARRAY_BUFFER,0);
	g.glBindVertexArray(0);
}

void DrawSmooth::manageVertex(
	Point P,
	Vector N,
	std::pair<float,float> TC,
	std::vector<unsigned int>& indices,
	std::vector<float>& normals,
	std::vector<float>& colors,
	std::vector<float>& texCoords,
	std::map<MyPoint,int>& verticesMap)
{
	MyPoint Pt(P.x(),P.y(),P.z());

	int vertexIndex = verticesMap[Pt];

	indices.push_back(vertexIndex);
	normals[3*vertexIndex] += N.x();
	normals[3*vertexIndex+1] += N.y();
	normals[3*vertexIndex+2] += N.z();
	
	colors[3*vertexIndex] += fabs(N.x());
	colors[3*vertexIndex+1] += fabs(N.y());
	colors[3*vertexIndex+2] += fabs(N.z());

	texCoords[2*vertexIndex] += TC.first;
	texCoords[2*vertexIndex+1] += TC.second;
}