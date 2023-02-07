#include "GradoIP.h"

GradoIP::GradoIP() {
  ip = " ";
  grado = 0;
}

GradoIP::GradoIP(ipAddress ip) {
  this->ip = ip.getIp();
  grado = ip.getOutDegree();
}

bool GradoIP::operator==(const GradoIP &otro) const {
  return grado == otro.grado;
}

bool GradoIP::operator!=(const GradoIP &otro) const {
  return this->grado != otro.grado;
}

bool GradoIP::operator>(const GradoIP &otro) const {
  return this->grado > otro.grado;
}

bool GradoIP::operator>=(const GradoIP &otro) const {
  return this->grado >= otro.grado;
}

bool GradoIP::operator<(const GradoIP &otro) const {
  return this->grado < otro.grado;
}

bool GradoIP::operator<=(const GradoIP &otro) const {
  return this->grado <= otro.grado;
}

std::ostream &operator<<(std::ostream &os, const GradoIP &gradoIP) {
  os << "Direccion IP: " << gradoIP.ip << ", Grado de salida: " << gradoIP.grado
     << std::endl;
  return os;
}

int GradoIP::getGrado() { return grado; }

std::string GradoIP::getDireccion() { return ip; }