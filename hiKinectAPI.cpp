/**********************************************************\

  Auto-generated hiKinectAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "hiKinectAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn hiKinectAPI::hiKinectAPI(const hiKinectPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
hiKinectAPI::hiKinectAPI(const hiKinectPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &hiKinectAPI::echo));
    registerMethod("testEvent", make_method(this, &hiKinectAPI::testEvent));

    // Read-write property
    registerProperty("testString",
                     make_property(this,
                        &hiKinectAPI::get_testString,
                        &hiKinectAPI::set_testString));

    // Read-only property
    registerProperty("version",
                     make_property(this,
                        &hiKinectAPI::get_version));
}

///////////////////////////////////////////////////////////////////////////////
/// @fn hiKinectAPI::~hiKinectAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
hiKinectAPI::~hiKinectAPI()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @fn hiKinectPtr hiKinectAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
hiKinectPtr hiKinectAPI::getPlugin()
{
    hiKinectPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string hiKinectAPI::get_testString()
{
    return m_testString;
}
void hiKinectAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string hiKinectAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

// Method echo
FB::variant hiKinectAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo(msg, n++);
    return msg;
}

void hiKinectAPI::testEvent(const FB::variant& var)
{
    fire_fired(var, true, 1);
}

