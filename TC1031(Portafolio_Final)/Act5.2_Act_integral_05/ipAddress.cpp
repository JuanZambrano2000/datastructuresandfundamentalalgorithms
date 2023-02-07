#include "ipAddress.h"
#include <cmath>
#include <exception>

ipAddress::ipAddress() {
  ipString = "0.0.0.0";
  ipIndex = 0;
  outDegree = 0;
  ipValue = 0;
  inDegree = 0;
}

ipAddress::ipAddress(std::string _ip, int idx) {
  ipString = _ip;
  ipIndex = idx;
  outDegree = 0;
  inDegree = 0;
  // Convertir IP a formato decimal
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;
  while (posFound >= 0) {
    posFound = ipString.find(".", posInit);
    splitted = ipString.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
      
  }
  ipValue = std::stoi(results[0]) * (pow(256, 3)) +
            std::stoi(results[1]) * (pow(256, 2)) +
            std::stoi(results[2]) * 256 + std::stoi(results[3]);
}

std::string ipAddress::getIp() { return ipString; }

unsigned int ipAddress::getIpValue() { return ipValue; }

int ipAddress::getIpIndex() { return ipIndex; }

void ipAddress::addToOutDegree() { outDegree++; }

void ipAddress::addtoInDegree() { inDegree++; }

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

std::ostream &operator<<(std::ostream &os, const ipAddress &ip) {
  os << "IP: " << ip.ipString << " | Direcciones accesadas: " << ip.outDegree
     << " | Direcciones que accesaron esta IP: " << ip.inDegree << " |";
  return os;
}

int ipAddress::getOutDegree() { return outDegree; }

int ipAddress::getInDegree() { return inDegree; }
