-----------------------------------------
-- Script Entry Point
-----------------------------------------
local guiSystem = CEGUI.System:getSingleton()
local schemeMgr = CEGUI.SchemeManager:getSingleton()
local winMgr = CEGUI.WindowManager:getSingleton()

-- load our demo8 scheme
schemeMgr:createFromFile("TestA.scheme");
-- load our demo8 window layout
local root = winMgr:loadLayoutFromFile("test2.layout")
-- set the layout as the root
guiSystem:getDefaultGUIContext():setRootWindow(root)
-- set default mouse cursor
guiSystem:getDefaultGUIContext():getMouseCursor():setDefaultImage("TaharezLook/MouseArrow")
-- set the Tooltip type
guiSystem:getDefaultGUIContext():setDefaultTooltipType("TaharezLook/Tooltip")