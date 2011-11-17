/**********************************************************\

  Auto-generated hiKinectAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "hiKinectAPI.h"


///////////////////////////////////////////////////////////////////////////////
/// @fn hiKinectAPI::hiKinectAPI(const hiKinectPtr& plugin,
//                               const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your
//          methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
hiKinectAPI::hiKinectAPI(const hiKinectPtr& plugin,
                         const FB::BrowserHostPtr& host)
: m_plugin(plugin), m_host(host) {
    registerMethod("echo",      make_method(this, &hiKinectAPI::echo));
    registerMethod("contextShutdown",
                   make_method(this, &hiKinectAPI::contextShutdown));
    registerMethod("contextWaitAndUpdateAll",
                   make_method(this, &hiKinectAPI::contextWaitAndUpdateAll));
    registerMethod("getSkeleton", make_method(this, &hiKinectAPI::getSkeleton));
    registerMethod("init", make_method(this, &hiKinectAPI::init));

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

FB::VariantMap hiKinectAPI::getPosition(XnSkeletonJoint joint, FB::VariantMap &map){
  XnSkeletonJointPosition pos;
  hiKinectPtr plugin = getPlugin();
  plugin->getPosition(joint, pos);
  map["x"] = pos.position.X;
  map["y"] = pos.position.Y;
  map["z"] = pos.position.Z;
  if (joint == XN_SKEL_HEAD) {
    FBLOG_INFO("getPosition", pos.position.X);
    FBLOG_INFO("getPosition", pos.position.Y);
    FBLOG_INFO("getPosition", pos.position.Z);
  }
  return map;
}

FB::VariantMap hiKinectAPI::getSkeleton(){
  hiKinectPtr plugin = getPlugin();
  plugin->contextWaitAndUpdateAll();
  FB::VariantMap map, head, neck, torso, waist;
  FB::VariantMap l_collar, l_shoulder, l_elbow, l_wrist, l_hand, l_fingertip;
  FB::VariantMap r_collar, r_shoulder, r_elbow, r_wrist, r_hand, r_fingertip;
  FB::VariantMap l_hip, l_knee, l_ankle, l_foot;
  FB::VariantMap r_hip, r_knee, r_ankle, r_foot;
  map["XN_SKEL_HEAD"] = getPosition(XN_SKEL_HEAD, head);
  map["XN_SKEL_NECK"] = getPosition(XN_SKEL_NECK, neck);
  map["XN_SKEL_TORSO"] = getPosition(XN_SKEL_TORSO, torso);
  map["XN_SKEL_WAIST"] = getPosition(XN_SKEL_WAIST, waist);
  map["XN_SKEL_LEFT_COLLAR"] = getPosition(XN_SKEL_LEFT_COLLAR, l_collar);
  map["XN_SKEL_LEFT_SHOULDER"] = getPosition(XN_SKEL_LEFT_SHOULDER, l_shoulder);
  map["XN_SKEL_LEFT_ELBOW"] = getPosition(XN_SKEL_LEFT_ELBOW, l_elbow);
  map["XN_SKEL_LEFT_WRIST"] = getPosition(XN_SKEL_LEFT_WRIST, l_wrist);
  map["XN_SKEL_LEFT_HAND"] = getPosition(XN_SKEL_LEFT_HAND, l_hand);
  map["XN_SKEL_LEFT_FINGERTIP"] = getPosition(XN_SKEL_LEFT_FINGERTIP, l_fingertip);
  map["XN_SKEL_RIGHT_COLLAR"] = getPosition(XN_SKEL_RIGHT_COLLAR, r_collar);
  map["XN_SKEL_RIGHT_SHOULDER"] = getPosition(XN_SKEL_RIGHT_SHOULDER, r_shoulder);
  map["XN_SKEL_RIGHT_ELBOW"] = getPosition(XN_SKEL_RIGHT_ELBOW, r_elbow);
  map["XN_SKEL_RIGHT_WRIST"] = getPosition(XN_SKEL_RIGHT_WRIST, r_wrist);
  map["XN_SKEL_RIGHT_HAND"] = getPosition(XN_SKEL_RIGHT_HAND, r_hand);
  map["XN_SKEL_RIGHT_FINGERTIP"] = getPosition(XN_SKEL_RIGHT_FINGERTIP, r_fingertip);
  map["XN_SKEL_LEFT_HIP"] = getPosition(XN_SKEL_LEFT_HIP, l_hip);
  map["XN_SKEL_LEFT_KNEE"] = getPosition(XN_SKEL_LEFT_KNEE, l_knee);
  map["XN_SKEL_LEFT_ANKLE"] = getPosition(XN_SKEL_LEFT_ANKLE, l_ankle);
  map["XN_SKEL_LEFT_FOOT"] = getPosition(XN_SKEL_LEFT_FOOT, l_foot);
  map["XN_SKEL_RIGHT_HIP"] = getPosition(XN_SKEL_RIGHT_HIP, r_hip);
  map["XN_SKEL_RIGHT_KNEE"] = getPosition(XN_SKEL_RIGHT_KNEE, r_knee);
  map["XN_SKEL_RIGHT_ANKLE"] = getPosition(XN_SKEL_RIGHT_ANKLE, r_ankle);
  map["XN_SKEL_RIGHT_FOOT"] = getPosition(XN_SKEL_RIGHT_FOOT, r_foot);
  return map;
}

bool hiKinectAPI::init(const FB::JSObjectPtr &callback) {
  boost::thread t(boost::bind(&hiKinectAPI::init_thread, this, callback));
  return true;
}

void hiKinectAPI::init_thread(const FB::JSObjectPtr &callback) {
  getPlugin()->init(callback);
}

void hiKinectAPI::contextShutdown(){
  getPlugin()->contextShutdown();
}

void hiKinectAPI::contextWaitAndUpdateAll(){
  getPlugin()->contextWaitAndUpdateAll();
}
