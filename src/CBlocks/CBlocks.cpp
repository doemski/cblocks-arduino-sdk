#include "CBlocks.h"
#include "Util.h"
#include "UpdateTimer.h"

namespace CBlocks{
  CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, Network* network, PowerManager* powerManager){
    this->objectID = objectID;
    this->instanceID = instanceID;
    this->network = network;
    this->powerManager = powerManager;
    this->batteryStatusUpdateTimer = new UpdateTimer(BATTERY_STATUS_UPDATE_INTERVAL_MS);
  }

  void CBlocks::begin(){
    network->init();
  }

  void CBlocks::heartBeat(){
    publishBatteryStatus();

    if(!powerManager->isPowerButtonOn() || powerManager->isBatteryLow()){
      network->disconnect();
      powerManager->turnOff();
    }else{
      network->keepOnline();
    }
  }

  void CBlocks::publishBatteryStatus(){
    if(batteryStatusUpdateTimer->updateIntervalExceeded()){
      updateResource(BATTERY_STATUS_RESOURCE_ID, (unsigned int)powerManager->getBatteryStatus());
    }
  }

  void CBlocks::updateResource(unsigned int resourceID, String value){
    network->publish(getOutputTopicFor(resourceID), value);
  }

  void CBlocks::updateResource(unsigned int resourceID, unsigned int value){
    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  String CBlocks::getOutputTopicFor(unsigned int resourceID){
    return Util::getOutputTopic(objectID, instanceID, resourceID);
  }

  void CBlocks::updateResource(unsigned int resourceID, float value){
    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::updateResource(unsigned int resourceID, bool value){
    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::updateResource(unsigned int resourceID, JsonObject& value){
    network->publish(getOutputTopicFor(resourceID), Util::getPayloadFor(value));
  }

  void CBlocks::registerCommand(unsigned int resourceID, commandCallback cb){
    network->subscribe(getInputTopicFor(resourceID), cb);
  }

  String CBlocks::getInputTopicFor(unsigned int resourceID){
    return Util::getInputTopic(objectID, instanceID, resourceID);
  }
}
