#include "IPs.h"

IPs::IPs(){
  this->ip="";
  this->numVeces = 0;
}

IPs::IPs(std::string ip, int numVeces){
  this->ip=ip;
  this->numVeces = numVeces;
}

bool IPs::operator==(IPs &other) {
  return this->numVeces == other.numVeces;
}

bool IPs::operator!=(IPs &other) {
  return this->numVeces != other.numVeces;
}

bool IPs::operator>=(IPs &other) {
  return this->numVeces >= other.numVeces;
}

bool IPs::operator<=(IPs &other) {
  return this->numVeces <= other.numVeces;
}

bool IPs::operator>(IPs &other) { 
  return this->numVeces > other.numVeces; 
  }

bool IPs::operator<(IPs &other) { 
  return this->numVeces < other.numVeces; 
  }

std::ostream& operator<<(std::ostream& os,const IPs& ip) {
    os << "IP Registrado: " << ip.ip << " | Número de veces encontrado: " << ip.numVeces << std::endl;
    return os;
}

int IPs::getNumVeces(){return numVeces;}
