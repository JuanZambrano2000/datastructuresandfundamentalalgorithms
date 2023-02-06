#ifndef _GRADOIP_H_
#define _GRADOIP_H_

#include "ipAddress.h"
#include <string>

class GradoIP {
private:
  std::string ip;
  int grado;

public:
  GradoIP();
  GradoIP(ipAddress ip);
  int getGrado();
  std::string getDireccion();
  bool operator==(const GradoIP &) const;
  bool operator!=(const GradoIP &) const;
  bool operator>(const GradoIP &) const;
  bool operator>=(const GradoIP &) const;
  bool operator<(const GradoIP &) const;
  bool operator<=(const GradoIP &) const;
  friend std::ostream &operator<<(std::ostream &os, const GradoIP &ip);
};

#endif //_GRADOIP_H
