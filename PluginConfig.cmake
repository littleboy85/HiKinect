#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for hiKinect
#
#\**********************************************************/

set(PLUGIN_NAME "hiKinect")
set(PLUGIN_PREFIX "HKI")
set(COMPANY_NAME "howlworld")

# ActiveX constants:
set(FBTYPELIB_NAME hiKinectLib)
set(FBTYPELIB_DESC "hiKinect 1.0 Type Library")
set(IFBControl_DESC "hiKinect Control Interface")
set(FBControl_DESC "hiKinect Control Class")
set(IFBComJavascriptObject_DESC "hiKinect IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "hiKinect ComJavascriptObject Class")
set(IFBComEventSource_DESC "hiKinect IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 4a2af81b-69a3-5eac-b330-a89abc716b9d)
set(IFBControl_GUID 79f45142-7c9e-5b30-a5b6-50e3e5a37ff5)
set(FBControl_GUID cb70e64f-bb34-5897-8fa1-6e1f705a50ab)
set(IFBComJavascriptObject_GUID 20532b73-0acf-57c7-8d15-c9f66d63f216)
set(FBComJavascriptObject_GUID d30f91f2-5e2f-5530-a128-d6e8029b8514)
set(IFBComEventSource_GUID a8052a0c-7b4a-5711-86cc-2663c8817a6a)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "howlworld.hiKinect")
set(MOZILLA_PLUGINID "howlworld.com/hiKinect")

# strings
set(FBSTRING_CompanyName "howlworld")
set(FBSTRING_FileDescription "kinect connector")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2011 howlworld")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "hiKinect")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "hiKinect")
set(FBSTRING_MIMEType "application/x-hikinect")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
add_firebreath_library(log4cplus)
