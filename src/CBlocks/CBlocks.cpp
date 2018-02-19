#include "CBlocks.h"
#include "Util.h"

CBlocks::CBlocks(unsigned int objectID, unsigned int instanceID, Network* network){
  this->objectID = objectID;
  this->instanceID = instanceID;
  this->network = network;
}

void CBlocks::begin(){
  network->init();
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
