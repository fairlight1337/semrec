#ifndef __INTERACTIVE_OBJECT_H__
#define __INTERACTIVE_OBJECT_H__


// System
#include <iostream>

// ROS
#include <interactive_markers/interactive_marker_server.h>
#include <interactive_markers/menu_handler.h>

using namespace std;
using namespace visualization_msgs;
using namespace interactive_markers;


namespace beliefstate {
  typedef struct {
    string strLabel;
    string strIdentifier;
    string strParameter;
    uint8_t unMenuEntryID;
  } InteractiveMenuEntry;
  
  class InteractiveObject {
  private:
    Marker m_mkrMarker;
    MenuHandler m_mhMenu;
    InteractiveMarker m_imMarker;
    InteractiveMarkerServer* m_imsServer;
    InteractiveMarkerControl m_imcControl;
    list<InteractiveMenuEntry> m_lstMenuEntries;
    
  public:
    InteractiveObject(string strName);
    ~InteractiveObject();
    
    void insertIntoServer(InteractiveMarkerServer* imsServer);
    void clickCallback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
    
    void setMarker(visualization_msgs::Marker mkrMarker);
    void setPose(string strFixedFrame, geometry_msgs::Pose posPose);
    
    string name();
    void addMenuEntry(string strLabel, string strIdentifier, string strParameter);
    void removeMenuEntry(string strIdentifier, string strParameter);
  };
}


#endif /* __INTERACTIVE_OBJECT_H__ */
