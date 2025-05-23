#ifndef _H_IG1App_H_
#define _H_IG1App_H_

#include <GL/glew.h>     // OpenGL Extension Wrangler
#include <GLFW/glfw3.h>  // OpenGL Library
#include <glm/glm.hpp>   // OpenGL Mathematics

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

class IG1App
{
public:
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const& J) = delete;         // no copy constructor
	void operator=(IG1App const& J) = delete; // no copy assignment

	// Viewport position and size
	Viewport const& viewPort() { return *mViewPort; };
	// Camera position, view volume and projection
	Camera const& camera() { return *mCamera; };
	// Graphics objects of the scene
	Scene const& scene() { return *mScenes[mCurrentScene]; };

	// Change to the given scene
	bool changeScene(size_t sceneNr);

	void run();   // the main event processing loop
	void close(); // the application

	GLint getWinWidth() { return (m2vistas) ? mWinW/2 : mWinW; }
	GLint getWinHeight() { return mWinH; }

	GLboolean showNormals() { return mShowNormals;}

protected:

	// Apartado 14
	static constexpr GLdouble FRAME_DURATION = 1/30.;
	GLboolean mUpdateEnabled = false;
	GLdouble mNextUpdate = 0.0;

	// Apartado 50
	glm::dvec2 mMouseCoord;
	GLint mMouseButt = -1;

	// Apartado 61
	// se lee con el metodo showNormals, usada para saber si renderizar o no normales
	GLboolean mShowNormals = false;

	// Callbacks estáticos
	// Llaman a los callbacks miembros del singletón
	static void s_mouse( GLFWwindow * win, GLint button, GLint action, GLint mods);
	static void s_motion( GLFWwindow * win, GLdouble x, GLdouble y);
	static void s_mouseWheel ( GLFWwindow * win, GLdouble dx, GLdouble dy);

	// Callbacks de cada input del raton
	void mouse( GLint button, GLint action, GLint mods);
	void motion( GLdouble x, GLdouble y);
	void mouseWheel ( GLdouble dx, GLdouble dy );

	IG1App() = default;
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void destroy();

	void display() const;                      // the scene

	/// @brief activa o desactiva viewport con 2 vistas
	GLboolean m2vistas = false;
	/// @brief Renderiza dos vistas, cada una en una mitad de la ventana
	void display2V() const;

	void resize(int newWidth, int newHeight);  // the viewport (without changing the scale)
	void key(unsigned int codepoint); // keypress event
	void specialkey(int key, int scancode, int action, int mods); // special keypress event

	// static callbacks
	static void s_display(GLFWwindow*) { s_ig1app.display(); };
	static void s_resize(GLFWwindow*, int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(GLFWwindow* win, unsigned int codepoint) { s_ig1app.key(codepoint); };
	static void s_specialkey(GLFWwindow* win, int key, int scancode, int action, int mods) { s_ig1app.specialkey(key, scancode, action, mods); };

	// Viewport position and size
	Viewport* mViewPort = nullptr;
	// Camera position, view volume and projection
	Camera* mCamera = nullptr;
	// Graphics objects are in the scenes
	std::vector<Scene*> mScenes;
	size_t mCurrentScene = 0;

	bool mNeedsRedisplay = true;  // main event processing loop
	GLFWwindow* mWindow = nullptr; // window's handle
	int mWinW = 800;               // window's width
	int mWinH = 600;               // window's height
};

#endif //_H_IG1App_H_
