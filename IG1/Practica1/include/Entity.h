#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0)  // 4x4 identity matrix
	  , mShader(nullptr) {};
	virtual ~Abs_Entity();

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(const glm::mat4& modelViewMat) const = 0; // abstract method

	// modeling matrix
	glm::mat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::mat4 const& aMat) { mModelMat = aMat; };

	// load or unload entity data into the GPU
	void load();
	void unload();

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::mat4 mModelMat;  // modeling matrix
	Shader* mShader; // shader

	// transfers modelViewMat to the GPU
	virtual void upload(const glm::mat4& mModelViewMat) const;
};

class EntityWithColors : public Abs_Entity
{
public:
	explicit EntityWithColors();
	void render(const glm::mat4& modelViewMat) const override;
};

class RGBAxes : public EntityWithColors
{
public:
	explicit RGBAxes(GLdouble l);
};

class SingleColorEntity : public Abs_Entity
{
public:
	explicit SingleColorEntity(glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));
	glm::dvec4 color() const;
	void setColor(glm::dvec4 color);

	void render(const glm::mat4& modelViewMat) const override;

protected:
	glm::dvec4 mColor;
};

// Apartado 4
class RegularPolygon : public SingleColorEntity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r, glm::dvec4 color = glm::dvec4(0.0, 0.0, 0.0, 1.0));
};

#endif //_H_Entities_H_
