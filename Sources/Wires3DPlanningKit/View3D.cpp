#include "View3D.h"

#include <math.h>

double AnglBetweenWalls(const double x, const double z,
						const double x1, const double z1);
double DistanceBetweenWalls(const double x, const double z,
							const double x1, const double z1);
/*
Note that we pass any supplied QWindow parent to the base QWindow class. This is necessary should we
need to use our class within a container.
*/
QTOgreWindow::QTOgreWindow(QWindow *parent)
	: QWindow(parent)
	, m_update_pending(false)
	, m_animating(false)
	, m_ogreRoot(NULL)
	, m_ogreWindow(NULL)
	, m_ogreCamera(NULL)
	, m_cameraMan(NULL)
	, m_wall_numbers(0)
{
	this->initialize();
	setAnimating(true);
	installEventFilter(this);
	m_ogreBackground = Ogre::ColourValue(0.0f, 0.5f, 1.0f);
}

/*
Upon destruction of the QWindow object we destroy the Ogre3D scene.
*/
QTOgreWindow::~QTOgreWindow()
{
	if(m_cameraMan) delete m_cameraMan;
	delete m_ogreRoot;
}

/*
In case any drawing surface backing stores (QRasterWindow or QOpenGLWindow) of Qt are supplied to this
class in any way we inform Qt that they will be unused.
*/
void QTOgreWindow::render(QPainter *painter)
{
	Q_UNUSED(painter);
}

/*
Our initialization function. Called by our renderNow() function once when the window is first exposed.
*/
void QTOgreWindow::initialize()
{
	/*
	As shown Ogre3D is initialized normally; just like in other documentation.
	*/
	m_ogreRoot = new Ogre::Root(Ogre::String("C:\plugins.cfg"));

	/*

	Commended out for simplicity but should you need to initialize resources you can do so normally.

	ogreConfig.load("resources/resource_configs/resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = ogreConfig.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
	secName = seci.peekNextKey();
	Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
	Ogre::ConfigFile::SettingsMultiMap::iterator i;
	for (i = settings->begin(); i != settings->end(); ++i)
	{
	typeName = i->first;
	archName = i->second;
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
	archName, typeName, secName);
	}
	}

	*/

	m_ogreRoot->loadPlugin("D:/ThirdParty/OGRE-SDK-1.9.0-vc140-x64-12.03.2016/bin/Debug/RenderSystem_GL_d.dll");
	const Ogre::RenderSystemList& rsList = m_ogreRoot->getAvailableRenderers();
	Ogre::RenderSystem* rs = rsList[0];
	

	/*
	This list setup the search order for used render system.
	*/
	Ogre::StringVector renderOrder;

	renderOrder.push_back("OpenGL");

	/*
	Setting size and VSync on windows will solve a lot of problems
	*/
	QString dimensions = QString("%1 x %2").arg(this->width()).arg(this->height());
	rs->setConfigOption("Video Mode", dimensions.toStdString());
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("VSync", "Yes");
	m_ogreRoot->setRenderSystem(rs);
	m_ogreRoot->initialise(false);

	Ogre::NameValuePairList parameters;
	/*
	Flag within the parameters set so that Ogre3D initializes an OpenGL context on it's own.
	*/
	//if(rs->getName().find("GL") <= rs->getName().size())
	//  parameters["currentGLContext"] = Ogre::String("false");

	/*
	We need to supply the low level OS window handle to this QWindow so that Ogre3D knows where to draw
	the scene. Below is a cross-platform method on how to do this.
	If you set both options (externalWindowHandle and parentWindowHandle) this code will work with OpenGL
	and DirectX.
	*/
	parameters["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)(this->winId()));
	parameters["parentWindowHandle"] = Ogre::StringConverter::toString((unsigned long)(this->winId()));

	/*
	Note below that we supply the creation function for the Ogre3D window the width and height
	from the current QWindow object using the "this" pointer.
	*/
	m_ogreWindow = m_ogreRoot->createRenderWindow("QT Window",
												  this->width(),
												  this->height(),
												  false,
												  &parameters);
	m_ogreWindow->setVisible(true);

	/*
	The rest of the code in the initialization function is standard Ogre3D scene code. Consult other
	tutorials for specifics.
	*/

	m_ogreSceneMgr = m_ogreRoot->createSceneManager(Ogre::ST_GENERIC);

	m_ogreCamera = m_ogreSceneMgr->createCamera("MainCamera");
	m_ogreCamera->setPosition(Ogre::Vector3(0.0f, 0.0f, 10.0f));
	m_ogreCamera->lookAt(Ogre::Vector3(0.0f, 0.0f, -300.0f));
	m_ogreCamera->setNearClipDistance(0.1f);
	m_ogreCamera->setFarClipDistance(200.0f);
	m_cameraMan = new OgreQtBites::SdkQtCameraMan(m_ogreCamera);   // create a default camera controller

	Ogre::Viewport* pViewPort = m_ogreWindow->addViewport(m_ogreCamera);
	pViewPort->setBackgroundColour(m_ogreBackground);

	m_ogreCamera->setAspectRatio(
		Ogre::Real(m_ogreWindow->getWidth()) / Ogre::Real(m_ogreWindow->getHeight()));
	m_ogreCamera->setAutoAspectRatio(true);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	createScene();
	RenderFoor();
	RenderWall(0, 0, 0, 10);
	RenderWall(0, 0, 10, 0);

	m_ogreRoot->addFrameListener(this);
}

void QTOgreWindow::createScene()
{
	/*
	Example scene
	Derive this class for your own purpose and overwite this function to have a working Ogre widget with
	your own content.
	*/

	m_ogreSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	Ogre::Light* light = m_ogreSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	///////////////////////////
	//// create a floor mesh resource
	//Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                              Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);
	//// create a floor entity, give it a material, and place it at the origin
	//Ogre::Entity* floor = m_ogreSceneMgr->createEntity("Floor", "floor");
	//m_ogreSceneMgr->getRootSceneNode()->attachObject(floor);
	///////////////////////////
}

void QTOgreWindow::render()
{
	/*
	How we tied in the render function for OGre3D with QWindow's render function. This is what gets call
	repeatedly. Note that we don't call this function directly; rather we use the renderNow() function
	to call this method as we don't want to render the Ogre3D scene unless everything is set up first.
	That is what renderNow() does.

	Theoretically you can have one function that does this check but from my experience it seems better
	to keep things separate and keep the render function as simple as possible.
	*/
	Ogre::WindowEventUtilities::messagePump();
	m_ogreRoot->renderOneFrame();
}

void QTOgreWindow::renderLater()
{
	/*
	This function forces QWindow to keep rendering. Omitting this causes the renderNow() function to
	only get called when the window is resized, moved, etc. as opposed to all of the time; which is
	generally what we need.
	*/
	if(!m_update_pending)
	{
		m_update_pending = true;
		QApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
	}
}

bool QTOgreWindow::event(QEvent *event)
{
	/*
	QWindow's "message pump". The base method that handles all QWindow events. As you will see there
	are other methods that actually process the keyboard/other events of Qt and the underlying OS.

	Note that we call the renderNow() function which checks to see if everything is initialized, etc.
	before calling the render() function.
	*/

	switch(event->type())
	{
	case QEvent::UpdateRequest:
		m_update_pending = false;
		renderNow();
		return true;

	default:
		return QWindow::event(event);
	}
}

/*
Called after the QWindow is reopened or when the QWindow is first opened.
*/
void QTOgreWindow::exposeEvent(QExposeEvent *event)
{
	Q_UNUSED(event);

	if(isExposed())
		renderNow();
}

/*
The renderNow() function calls the initialize() function when needed and if the QWindow is already
initialized and prepped calls the render() method.
*/
void QTOgreWindow::renderNow()
{
	if(!isExposed())
		return;

	if(m_ogreRoot == NULL)
	{
		initialize();
	}

	render();

	if(m_animating)
		renderLater();
}

/*
Our event filter; handles the resizing of the QWindow. When the size of the QWindow changes note the
call to the Ogre3D window and camera. This keeps the Ogre3D scene looking correct.
*/
bool QTOgreWindow::eventFilter(QObject *target, QEvent *event)
{
	if(target == this)
	{
		if(event->type() == QEvent::Resize)
		{
			if(isExposed() && m_ogreWindow != NULL)
			{
				m_ogreWindow->resize(this->width(), this->height());
			}
		}
	}

	return false;
}

/*
How we handle keyboard and mouse events.
*/
void QTOgreWindow::keyPressEvent(QKeyEvent * ev)
{
	if(m_cameraMan)
		m_cameraMan->injectKeyDown(*ev);
}

void QTOgreWindow::keyReleaseEvent(QKeyEvent * ev)
{
	if(m_cameraMan)
		m_cameraMan->injectKeyUp(*ev);
}

void QTOgreWindow::mouseMoveEvent(QMouseEvent* e)
{
	static int lastX = e->x();
	static int lastY = e->y();
	int relX = e->x() - lastX;
	int relY = e->y() - lastY;
	lastX = e->x();
	lastY = e->y();

	if(m_cameraMan && (e->buttons() & Qt::LeftButton))
		m_cameraMan->injectMouseMove(relX, relY);
}

void QTOgreWindow::wheelEvent(QWheelEvent *e)
{
	if(m_cameraMan)
		m_cameraMan->injectWheelMove(*e);
}

void QTOgreWindow::mousePressEvent(QMouseEvent* e)
{
	if(m_cameraMan)
		m_cameraMan->injectMouseDown(*e);
}

void QTOgreWindow::mouseReleaseEvent(QMouseEvent* e)
{
	if(m_cameraMan)
		m_cameraMan->injectMouseUp(*e);

	QPoint pos = e->pos();
	Ogre::Ray mouseRay = m_ogreCamera->getCameraToViewportRay(
		(Ogre::Real)pos.x() / m_ogreWindow->getWidth(),
		(Ogre::Real)pos.y() / m_ogreWindow->getHeight());
	Ogre::RaySceneQuery* pSceneQuery = m_ogreSceneMgr->createRayQuery(mouseRay);
	pSceneQuery->setSortByDistance(true);
	Ogre::RaySceneQueryResult vResult = pSceneQuery->execute();
	for(size_t ui = 0; ui < vResult.size(); ui++)
	{
		if(vResult[ui].movable)
		{
			if(vResult[ui].movable->getMovableType().compare("Entity") == 0)
			{
				emit entitySelected((Ogre::Entity*)vResult[ui].movable);
			}
		}
	}
	m_ogreSceneMgr->destroyQuery(pSceneQuery);
}

/*
Function to keep track of when we should and shouldn't redraw the window; we wouldn't want to do
rendering when the QWindow is minimized. This takes care of those scenarios.
*/
void QTOgreWindow::setAnimating(bool animating)
{
	m_animating = animating;

	if(animating)
		renderLater();
}

bool QTOgreWindow::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	m_cameraMan->frameRenderingQueued(evt);
	return true;
}

void QTOgreWindow::log(Ogre::String msg)
{
	if(Ogre::LogManager::getSingletonPtr() != NULL) Ogre::LogManager::getSingletonPtr()->logMessage(msg);
}

void QTOgreWindow::log(QString msg)
{
	log(Ogre::String(msg.toStdString().c_str()));
}

void QTOgreWindow::RenderFoor()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = m_ogreSceneMgr->createEntity("ground");
	m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

	groundEntity->setCastShadows(false);

	groundEntity->setMaterialName("Examples/Rockwall");

	m_ogreSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	m_ogreSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

}

void QTOgreWindow::RenderWall(const double x, const double z,
							  const double x1, const double z1)
{
	Ogre::ManualObject* wall = createCubeMesh(Ogre::String("Wall" + m_wall_numbers), "Material");
	Ogre::SceneNode* mNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
	const double hight = 2;
	const double distance = DistanceBetweenWalls(x, z, x1, z1);
	mNode->setPosition((x + x1) / 2, hight / 2, (z + z1) / 2);
	mNode->setScale(distance, hight, 0.5);
	mNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(AnglBetweenWalls(x, z, x1, z1)));
	mNode->attachObject(wall);
}

void QTOgreWindow::RenderLamp()
{
	//Ogre::Entity* sphereMesh = m_ogreSceneMgr->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);

	//Ogre::SceneNode* childSceneNode = m_ogreSceneMgr->getRootSceneNode()->createChildSceneNode();

	//childSceneNode->attachObject(sphereMesh);

	//Ogre::MaterialPtr sphereMaterial = Ogre::MaterialManager::getSingleton().create("SphereMaterial",
	//                                                                                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);

	//sphereMaterial->getTechnique(0)->getPass(0)->setAmbient(1.1f, 1.1f, 1.1f);
	//sphereMaterial->getTechnique(0)->getPass(0)->setDiffuse(1.2f, 1.2f, 1.2f, 1.0f);
	//sphereMaterial->getTechnique(0)->getPass(0)->setSpecular(1.9f, 1.9f, 1.9f, 1.0f);
	////sphereMaterial->setAmbient(0.2f, 0.2f, 0.5f);
	////sphereMaterial->setSelfIllumination(0.2f, 0.2f, 0.1f);

	//sphereMesh->setMaterialName("SphereMaterial");
	//childSceneNode->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	//childSceneNode->setScale(Ogre::Vector3(0.01f, 0.01f, 0.01f)); // Radius, in theory.
}

Ogre::ManualObject* QTOgreWindow::createCubeMesh(Ogre::String name, Ogre::String matName)
{

	Ogre::ManualObject* cube = new Ogre::ManualObject(name);
	cube->begin("BaseWhiteNoLighting");

	cube->position(0.5, -0.5, 1.0); cube->normal(0.408248, -0.816497, 0.408248); cube->textureCoord(1, 0);
	cube->position(-0.5, -0.5, 0.0); cube->normal(-0.408248, -0.816497, -0.408248); cube->textureCoord(0, 1);
	cube->position(0.5, -0.5, 0.0); cube->normal(0.666667, -0.333333, -0.666667); cube->textureCoord(1, 1);
	cube->position(-0.5, -0.5, 1.0); cube->normal(-0.666667, -0.333333, 0.666667); cube->textureCoord(0, 0);
	cube->position(0.5, 0.5, 1.0); cube->normal(0.666667, 0.333333, 0.666667); cube->textureCoord(1, 0);
	cube->position(-0.5, -0.5, 1.0); cube->normal(-0.666667, -0.333333, 0.666667); cube->textureCoord(0, 1);
	cube->position(0.5, -0.5, 1.0); cube->normal(0.408248, -0.816497, 0.408248); cube->textureCoord(1, 1);
	cube->position(-0.5, 0.5, 1.0); cube->normal(-0.408248, 0.816497, 0.408248); cube->textureCoord(0, 0);
	cube->position(-0.5, 0.5, 0.0); cube->normal(-0.666667, 0.333333, -0.666667); cube->textureCoord(0, 1);
	cube->position(-0.5, -0.5, 0.0); cube->normal(-0.408248, -0.816497, -0.408248); cube->textureCoord(1, 1);
	cube->position(-0.5, -0.5, 1.0); cube->normal(-0.666667, -0.333333, 0.666667); cube->textureCoord(1, 0);
	cube->position(0.5, -0.5, 0.0); cube->normal(0.666667, -0.333333, -0.666667); cube->textureCoord(0, 1);
	cube->position(0.5, 0.5, 0.0); cube->normal(0.408248, 0.816497, -0.408248); cube->textureCoord(1, 1);
	cube->position(0.5, -0.5, 1.0); cube->normal(0.408248, -0.816497, 0.408248); cube->textureCoord(0, 0);
	cube->position(0.5, -0.5, 0.0); cube->normal(0.666667, -0.333333, -0.666667); cube->textureCoord(1, 0);
	cube->position(-0.5, -0.5, 0.0); cube->normal(-0.408248, -0.816497, -0.408248); cube->textureCoord(0, 0);
	cube->position(-0.5, 0.5, 1.0); cube->normal(-0.408248, 0.816497, 0.408248); cube->textureCoord(1, 0);
	cube->position(0.5, 0.5, 0.0); cube->normal(0.408248, 0.816497, -0.408248); cube->textureCoord(0, 1);
	cube->position(-0.5, 0.5, 0.0); cube->normal(-0.666667, 0.333333, -0.666667); cube->textureCoord(1, 1);
	cube->position(0.5, 0.5, 1.0); cube->normal(0.666667, 0.333333, 0.666667); cube->textureCoord(0, 0);

	cube->triangle(0, 1, 2);      cube->triangle(3, 1, 0);
	cube->triangle(4, 5, 6);      cube->triangle(4, 7, 5);
	cube->triangle(8, 9, 10);      cube->triangle(10, 7, 8);
	cube->triangle(4, 11, 12);   cube->triangle(4, 13, 11);
	cube->triangle(14, 8, 12);   cube->triangle(14, 15, 8);
	cube->triangle(16, 17, 18);   cube->triangle(16, 19, 17);
	cube->end();

	return cube;
}

double AnglBetweenWalls(const double x, const double z,
						const double x1, const double z1)
{
	double angle = atan2(z - z1, x - x1);
	angle *= 180 / 3.141519;
	while(angle >= 180)
		angle -= 180;
	while(angle < 0)
		angle += 180;
	return angle;
}

double DistanceBetweenWalls(const double x, const double z,
							const double x1, const double z1)
{
	return std::sqrt(std::pow((x1 - x), 2) + std::pow((z1 - z), 2));
}