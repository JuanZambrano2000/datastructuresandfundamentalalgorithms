#ifndef _IPS_H_
#define _IPS_H_

#include <string>
#include <sstream>
#include <iostream>



class IPs{

  private:
  
    std::string ip;
    int numVeces;
  
  public:
    IPs();
    IPs(std::string ip, int numVeces);
    bool operator==(IPs &);
    bool operator!=(IPs &);
    bool operator>(IPs &);
    bool operator<(IPs &);
    bool operator>=(IPs &);
    bool operator<=(IPs &);
    friend std::ostream& operator<<(std::ostream& os,const IPs& ip);
    int getNumVeces();
};
#endif //_IPS_H_