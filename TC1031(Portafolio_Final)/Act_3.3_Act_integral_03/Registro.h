#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

class Registro {
private:
  std::vector<Registro> registros;
  std::string mes, dia, horas, minutos, segundos, ip, puerto, falla;
  unsigned int ipDecimal;
  std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  // Info struct tm    https://cplusplus.com/reference/ctime/tm/
  struct tm dateStruct;
  // Unix timestamp (segundos transcurridos desde el 1 de enero de 1970)
  time_t fechaHora;

public:
  Registro();
  Registro(std::string _mes, std::string _dia, std::string _horas,
           std::string _minutos, std::string _segundos, std::string _ip,
           std::string _puerto, std::string _falla);
  Registro(std::string _mes, std::string _dia, std::string _horas,
           std::string _minutos, std::string _segundos);
  //imprime los campos
  std::string getAll() const;
  std::string getIP();
  // Sobre carga de operadores
  bool operator==( Registro &);
  bool operator!=( Registro &);
  bool operator>( Registro &);
  bool operator<( Registro &);
  bool operator>=( Registro &);
  bool operator<=( Registro &);
  friend std::ostream& operator<<(std::ostream& os,const Registro& reg);
};


#endif //_REGISTRO_H_