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
#include <CEGUI\ScriptModules\Lua\ScriptModule.h>


#include "CEGUIManager.h"

#include <CEGUI\WindowFactoryManager.h>
#include <CEGUI\WindowRendererManager.h>

// Include custom CEGUI objects:
#include "InventoryItem.h"
#include "InventoryItemRenderer.h"
#include "InventoryReceiver.h"

#include <iostream>


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
			CEGUI::SchemeManager::getSingleton().createFromFile("GameMenu.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("HUDDemo.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("TestA.scheme");

			
		}

		// Register custom objects with CEGUI:
		{
			// register custom objects with CEGUI.
			CEGUI::WindowFactoryManager::addFactory<CEGUI::TplWindowFactory<CEGUI::InventoryReceiver>>();
			CEGUI::WindowFactoryManager::addFactory<CEGUI::TplWindowFactory<CEGUI::InventoryItem>>();
			CEGUI::WindowRendererManager::addFactory<CEGUI::TplWindowRendererFactory<CEGUI::InventoryItemRenderer>>();

			// load looknfeel for custom inventory components (needs TaharezLook images)
			CEGUI::WidgetLookManager::getSingleton().parseLookNFeelSpecificationFromFile("InventoryComponents.looknfeel");

			// create mapping for the item type
			// This is the equivalent to the following entry in a scheme xml file:
			// <FalagardMapping WindowType="TaharezLook/InventoryItem" TargetType="InventoryItem" LookNFeel="TaharezLook/InventoryItem" Renderer="InventoryItemRenderer" />
			CEGUI::WindowFactoryManager::getSingleton().addFalagardWindowMapping(
				"TaharezLook/InventoryItem",    // type to create
				"InventoryItem",                // 'base' widget type
				"TaharezLook/InventoryItem",    // WidgetLook to use.
				"InventoryItemRenderer");       // WindowRenderer to use.
		}
	}

	CEGUI::System::getSingleton().getDefaultGUIContext().
		getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	// Create windows
	{
		CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


		CEGUI::Window* root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("test2.layout"); // test.layout
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);


		//CEGUI::Window *dragContainerTemplate = CEGUI::WindowManager::getSingleton().loadLayoutFromString(CEGUI::String(
		//	"<Window type = \"Generic/Image\" name = \"Image\" >"
		//	"	<Property name = \"Area\" value = \"{{0,0},{0,0},{0,64},{0,128}}\" / >"
		//	"	<Property name = \"Image\" value = \"TestA2/MadBug\" / >"
		//	"	<Property name = \"MaxSize\" value = \"{{1,0},{1,0}}\" / >"
		//	"	<Property name = \"ClippedByParent\" value = \"false\" / >"
		//	"	<Property name = \"VerticalAlignment\" value = \"Centre\" / >"
		//	"	<Property name = \"HorizontalAlignment\" value = \"Centre\" / >"
		//	"	<Property name = \"MousePassThroughEnabled\" value = \"true\" / >"
		//	"< / Window>"));

		//for (int i = 0; i < 10; ++i) {

		//}
		

		//// create a script module.
		//CEGUI::LuaScriptModule& scriptmod(CEGUI::LuaScriptModule::create());

		//// tell CEGUI to use this scripting module
		//CEGUI::System::getSingleton().setScriptingModule(&scriptmod);


		//CEGUI::System::getSingleton().executeScriptFile("test2.lua");



		// Inventory testing:
		{
			// Create Backpack window
			CEGUI::Window* wnd = wmgr.createWindow("TaharezLook/FrameWindow");
			root->addChild(wnd);
			wnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f, 0), CEGUI::UDim(0.1f, 0)));
			wnd->setSize(CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.4f, 0)));
			wnd->setText("Backpack");

			CEGUI::InventoryReceiver& receiver1 = dynamic_cast<CEGUI::InventoryReceiver&>(*wmgr.createWindow("InventoryReceiver"));
			wnd->addChild(&receiver1);
			receiver1.setPosition(CEGUI::UVector2(cegui_reldim(0.0f), cegui_reldim(0.0f)));
			receiver1.setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
			receiver1.setContentSize(3, 6);
			receiver1.setUserString("BlockImage", "TaharezLook/GenericBrush");

			// Create vault window
			CEGUI::Window* wnd2 = wmgr.createWindow("TaharezLook/FrameWindow");
			root->addChild(wnd2);
			wnd2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.48f, 0), CEGUI::UDim(0.2f, 0)));
			wnd2->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.5f, 0)));
			wnd2->setText("Bank Vault");

			CEGUI::InventoryReceiver& receiver2 = dynamic_cast<CEGUI::InventoryReceiver&>(*wmgr.createWindow("InventoryReceiver"));
			wnd2->addChild(&receiver2);
			receiver2.setPosition(CEGUI::UVector2(cegui_reldim(0.0f), cegui_reldim(0.0f)));
			receiver2.setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim(1.0f)));
			receiver2.setContentSize(10, 10);
			receiver2.setUserString("BlockImage", "TaharezLook/GenericBrush");

			// create some items and add them to the vault.
			CEGUI::InventoryItem& item1 = dynamic_cast<CEGUI::InventoryItem&>(*wmgr.createWindow("TaharezLook/InventoryItem"));
			item1.setContentSize(2, 2);
			receiver2.addItemAtLocation(item1, 0, 0);
			item1.setProperty("Image", "TaharezLook/MouseArrow");

			CEGUI::InventoryItem& item2 = dynamic_cast<CEGUI::InventoryItem&>(*wmgr.createWindow("InventoryItem"));
			item2.setUserString("BlockImage", "TaharezLook/GenericBrush");
			item2.setContentSize(3, 1);
			receiver2.addItemAtLocation(item2, 1, 3);

			CEGUI::InventoryItem& item3 = dynamic_cast<CEGUI::InventoryItem&>(*wmgr.createWindow("InventoryItem"));
			item3.setUserString("BlockImage", "TaharezLook/GenericBrush");
			item3.setContentSize(1, 4);
			receiver2.addItemAtLocation(item3, 5, 2);

			CEGUI::InventoryItem& item4 = dynamic_cast<CEGUI::InventoryItem&>(*wmgr.createWindow("InventoryItem"));
			item4.setUserString("BlockImage", "TaharezLook/GenericBrush");
			item4.setContentSize(1, 1);
			receiver2.addItemAtLocation(item4, 8, 6);

			CEGUI::InventoryItem& item5 = dynamic_cast<CEGUI::InventoryItem&>(*wmgr.createWindow("InventoryItem"));
			item5.setUserString("BlockImage", "TaharezLook/GenericBrush");
			item5.setContentSize(2, 3);
		}

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