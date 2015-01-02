#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <CEGUI\RendererModules/OpenGL/GLRenderer.h>
#include <CEGUI\System.h>
#include <CEGUI\DefaultResourceProvider.h>
#include <CEGUI\ImageManager.h>
#include <CEGUI\Font.h>
#include <CEGUI\Scheme.h>
#include <CEGUI\widgets\DefaultWindow.h>
#include <CEGUI\Base.h>
#include <CEGUI\WindowManager.h>
#include <CEGUI\ScriptModule.h>
#include <CEGUI\XMLParser.h>
#include <CEGUI\falagard\WidgetLookManager.h>

#include <CEGUI\widgets\FrameWindow.h>


#include "CEGUIManager.h"



CEGUIManager::CEGUIManager() {

}

CEGUIManager::~CEGUIManager() {

}

void CEGUIManager::init() {
	CEGUI::OpenGLRenderer &m_renderer =
		CEGUI::OpenGLRenderer::bootstrapSystem();

	{
		// initialise the required dirs for the DefaultResourceProvider
		CEGUI::DefaultResourceProvider *resourceProvider = static_cast<CEGUI::DefaultResourceProvider*>
			(CEGUI::System::getSingleton().getResourceProvider());

		// set resource group directories.
		{
			CEGUI::DefaultResourceProvider* rp = resourceProvider;
			rp->setResourceGroupDirectory("schemes", "datafiles/schemes/");
			rp->setResourceGroupDirectory("imagesets", "datafiles/imagesets/");
			rp->setResourceGroupDirectory("fonts", "datafiles/fonts/");
			rp->setResourceGroupDirectory("layouts", "datafiles/layouts/");
			rp->setResourceGroupDirectory("looknfeels", "datafiles/looknfeel/");
			rp->setResourceGroupDirectory("lua_scripts", "datafiles/lua_scripts/");
		}

		// set default resource groups.
		{
			CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
			// setup default group for validation schemas
			CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
			if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
				parser->setProperty("SchemaDefaultResourceGroup", "schemas");


			CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
		}
	}

	CEGUI::System::getSingleton().getDefaultGUIContext().
		getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	// Create windows
	{
		CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


		CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Demo8.layout");
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);

	}

}

void CEGUIManager::update() {

}

void CEGUIManager::render() {
	
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);


	// make sure that before calling renderAllGUIContexts, that any bound textures
	// and shaders used to render the scene above are disabled using
	// glBindTexture(0) and glUseProgram(0) respectively also set
	// glActiveTexture(GL_TEXTURE_0) 
	// draw GUI
	// NB: When not using >=3.2 core profile, this call should not occur
	// between glBegin/glEnd calls.
	CEGUI::System::getSingleton().renderAllGUIContexts();
}


CEGUI::InjectedInputReceiver &CEGUIManager::getInjectedInputReceiver() {
	CEGUI::InjectedInputReceiver &injectedInputReceiver = CEGUI::System::getSingleton().getDefaultGUIContext();
	return injectedInputReceiver;
}