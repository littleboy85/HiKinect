/**********************************************************\

  Auto-generated hiKinect.cpp

  This file contains the auto-generated main plugin object
  implementation for the hiKinect project

\**********************************************************/

#include "hiKinectAPI.h"

#include "hiKinect.h"

#define POSE_TO_USE "Psi"
xn::UserGenerator g_UserGenerator;

void XN_CALLBACK_TYPE
User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie) {
  printf("New User: %d\n", nId);
  FBLOG_INFO("User_NewUser", nId);
  XnUInt16 nUsers = g_UserGenerator.GetNumberOfUsers();
  XnUserID aUsers[nUsers];
  g_UserGenerator.GetUsers(aUsers, nUsers);
  for (int i = 0; i < nUsers; ++i) {
    if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i])) {
      return;
    }
  }
  g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(POSE_TO_USE, nId);
}

void XN_CALLBACK_TYPE
User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie) {}

void XN_CALLBACK_TYPE
Pose_Detected(xn::PoseDetectionCapability& pose, const XnChar* strPose,
              XnUserID nId, void* pCookie) {
  printf("Pose %s for user %d\n", strPose, nId);
  FBLOG_INFO("Pose_Detected()", "Pose_Detected");
  g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
  g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}

void XN_CALLBACK_TYPE
Calibration_Start(xn::SkeletonCapability& capability, XnUserID nId,
                  void* pCookie) {
  printf("Starting calibration for user %d\n", nId);
  FBLOG_INFO("Calibration_Start", "Starting calibration");
}

void XN_CALLBACK_TYPE
Calibration_End(xn::SkeletonCapability& capability, XnUserID nId,
                XnBool bSuccess, void* pCookie) {
  if (bSuccess) {
    printf("User calibrated\n");
    FBLOG_INFO("Calibration_End", "User calibrated");
    g_UserGenerator.GetSkeletonCap().StartTracking(nId);
  } else {
    printf("Failed to calibrate user %d\n", nId);
    FBLOG_INFO("Calibration_End", "Failed to calibrate user");
    g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(POSE_TO_USE,
                                                             nId);
  }
}


///////////////////////////////////////////////////////////////////////////////
/// @fn hiKinect::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void hiKinect::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn hiKinect::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void hiKinect::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  hiKinect constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
hiKinect::hiKinect() {
  /*
  */
  // TODO: check error code
  /*
  while (TRUE) {
    // Update to next frame
    nRetVal = context.WaitAndUpdateAll();
    // TODO: check error code
    // Extract head position of each tracked user 
    XnUserID aUsers[15];
    XnUInt16 nUsers = 15;
    g_UserGenerator.GetUsers(aUsers, nUsers);
    for (int i = 0; i < nUsers; ++i) {
      if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i])) {
        XnSkeletonJointPosition Head;
        g_UserGenerator.GetSkeletonCap()
            .GetSkeletonJointPosition(aUsers[i], XN_SKEL_HEAD, Head);
        printf("%d: (%f,%f,%f) [%f]\n",
               aUsers[i], Head.position.X,
               Head.position.Y, Head.position.Z, Head.fConfidence);
      }
    }
  }
  */
  // Clean up
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  hiKinect destructor.
///////////////////////////////////////////////////////////////////////////////
hiKinect::~hiKinect()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void hiKinect::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void hiKinect::shutdown() {
  contextShutdown();
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<hiKinect> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr hiKinect::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<hiKinectAPI>(FB::ptr_cast<hiKinect>(shared_from_this()), m_host);
}

bool hiKinect::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool hiKinect::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool hiKinect::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
bool hiKinect::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return false;
}

bool hiKinect::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}

XnUserID hiKinect::getTrackedUserID(){
  XnUInt16 nUsers = g_UserGenerator.GetNumberOfUsers();
  XnUserID aUsers[nUsers];
  g_UserGenerator.GetUsers(aUsers, nUsers);
  xn::SkeletonCapability cap = g_UserGenerator.GetSkeletonCap();
  for (int i = 0; i < nUsers; ++i) {
    if (cap.IsTracking(aUsers[i])) {
      return aUsers[i];
    }
  }
  return 0;
}

XnStatus hiKinect::contextInit() {
  XnStatus nRetVal = XN_STATUS_OK;
  nRetVal = context.Init();
  if (nRetVal != XN_STATUS_OK) return nRetVal;
  // Create the user generator
  nRetVal = g_UserGenerator.Create(context);
  if (nRetVal != XN_STATUS_OK) return nRetVal;
  XnCallbackHandle h1, h2, h3;
  g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, h1);

  g_UserGenerator.GetPoseDetectionCap()
      .RegisterToPoseCallbacks(Pose_Detected, NULL, NULL, h2);
  g_UserGenerator.GetSkeletonCap()
      .RegisterCalibrationCallbacks(Calibration_Start, Calibration_End,
                                    NULL, h3);
  // Set the profile￼
  g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);
  // Start generating
  nRetVal = context.StartGeneratingAll();
  while (getTrackedUserID() == 0){
    contextWaitAndUpdateAll();
  }
  FBLOG_INFO("contextInit", "Init finish");
  return nRetVal;
}

void hiKinect::getPosition(XnSkeletonJoint joint, XnSkeletonJointPosition &pos){
  XnUserID id = getTrackedUserID();
  if (id != 0) {
    g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(id, joint, pos);
  }else{
    return;
  }
}

void hiKinect::contextWaitAndUpdateAll(){
  context.WaitAndUpdateAll();
}

void hiKinect::contextShutdown() {
  context.Shutdown();
}

