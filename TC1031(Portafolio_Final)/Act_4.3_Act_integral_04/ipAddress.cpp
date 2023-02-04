#include <cmath>
#include "ipAddress.h"

ipAddress::ipAddress(){
  ipString = "0.0.0.0";
  ipIndex = 0;
  outDegree = 0;
  ipValue = 0;
}

ipAddress::ipAddress(std::string _ip, int idx){
  ipString=_ip;
  ipIndex = idx;
  outDegree = 0;
  // Convertir IP a formato decimal
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;   
  while(posFound >= 0) {
    posFound = ipString.find(".", posInit);
    splitted = ipString.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
  ipValue = std::stoi(results[0])*(pow(256,3)) + std::stoi(results[1])*(pow(256,2)) + std::stoi(results[2])*256 + std::stoi(results[3]);
}

std::string ipAddress::getIp(){
  return ipString;
}

unsigned int ipAddress::getIpValue(){
  return ipValue;
}

int ipAddress::getIpIndex(){
  return ipIndex;
}

void ipAddress::setOutDegree(int g){
  outDegree = g;
}

void ipAddress::addToOutDegree(){
  outDegree++;
}

int ipAddress::getOutDegree(){
  return outDegree;
}

bool ipAddress::operator==(const ipAddress &other) const {
  return this->ipValue == other.ipValue;
}

bool ipAddress::operator!=(const ipAddress &other) const {
  return this->ipValue != other.ipValue;
}

bool ipAddress::operator>(const ipAddress &other) const {
  return this->ipValue > other.ipValue;
}

bool ipAddress::operator>=(const ipAddress &other) const {
  return this->ipValue >= other.ipValue;
}

bool ipAddress::operator<(const ipAddress &other) const {
  return this->ipValue < other.ipValue;
}

bool ipAddress::operator<=(const ipAddress &other) const {
  return this->ipValue <= other.ipValue;
}

std::ostream& operator<<(std::ostream& os, const ipAddress& ip) {
    os << ip.ipString << " " << ip.ipIndex << " " << ip.outDegree; 
    return os;
}

