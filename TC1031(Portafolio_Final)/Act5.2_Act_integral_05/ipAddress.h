#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include <cmath>
#include <iostream>
#include <vector>

class ipAddress {
private:
  std::string ipString;
  int ipIndex;
  unsigned int ipValue;
  int outDegree;
  int inDegree;

public:
  ipAddress();
  ipAddress(std::string _ip, int idx);
  std::string getIp();
  unsigned int getIpValue();
  int getIpIndex();
  void addToOutDegree();
  void addtoInDegree();
  int getOutDegree();
  int getInDegree();
  bool operator==(const ipAddress &) const;
  bool operator!=(const ipAddress &) const;
  bool operator>(const ipAddress &) const;
  bool operator>=(const ipAddress &) const;
  bool operator<(const ipAddress &) const;
  bool operator<=(const ipAddress &) const;
  friend std::ostream &operator<<(std::ostream &os, const ipAddress &ip);
};

#endif
