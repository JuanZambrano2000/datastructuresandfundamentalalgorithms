#include "Registro.h"

Registro::Registro() {
  mes = "";
  dia = "";
  horas = "";
  minutos = "";
  segundos = "";
  ip = "";
  puerto = "";
  falla = "";
  fechaHora = 0;
}
// Constructor que recibe la fecha y nos regresa un numero para poder ser
// comparado
Registro::Registro(std::string _mes, std::string _dia, std::string _horas,
                   std::string _minutos, std::string _segundos, std::string _ip,
                   std::string _puerto, std::string _falla) {
  mes = _mes;
  dia = _dia;
  horas = _horas;
  minutos = _minutos;
  segundos = _segundos;
  ip = _ip;
  puerto = _puerto;
  falla = _falla;
  // Almacenar los campos en el struct tm
  dateStruct.tm_hour = std::stoi(horas);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_mday = std::stoi(dia);
  // Resolver problemas de compatibilidad Windows
  dateStruct.tm_isdst = 0;
  for (int i = 0; i < (int)meses.size(); i++) {
    if (meses[i] == mes)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2023 - 1900; // Asumimos el año 2023
  // Obtener el Linux timestamp
  // https://cplusplus.com/reference/ctime/mktime/
  fechaHora = mktime(&dateStruct);
  // std::cout << "fechaHora: " << fechaHora << std::endl;

  std::istringstream iss(ip);
  std::string primero, segundo, tercero, cuarto;
  int i, j, k, l;
  //unsigned int resp;
  std::getline(iss, primero, '.');
  std::getline(iss, segundo, '.');
  std::getline(iss, tercero, '.');
  std::getline(iss, cuarto);
  i = std::stoi(primero);
  j = std::stoi(segundo);
  k = std::stoi(tercero);
  l = std::stoi(cuarto);
  ipDecimal = i * pow(256, 3) + j * pow(256, 2) + k * 256 + l;
  
}
// Constructor usado para comparar dos fechas (sin ip, puerto y falla ya que no
// son necesarios)
Registro::Registro(std::string _mes, std::string _dia, std::string _horas,
                   std::string _minutos, std::string _segundos) {
  mes = _mes;
  dia = _dia;
  horas = _horas;
  minutos = _minutos;
  segundos = _segundos;
  ip = "";
  puerto = "";
  falla = "";
  // Almacenar los campos en el struct tm
  dateStruct.tm_hour = std::stoi(horas);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_mday = std::stoi(dia);
  // Resolver problemas de compatibilidad Windows
  dateStruct.tm_isdst = 0;
  for (int i = 0; i < (int)meses.size(); i++) {
    if (meses[i] == mes)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2023 - 1900; // Asumimos el año 2023
  // Obtener el Linux timestamp
  // https://cplusplus.com/reference/ctime/mktime/
  fechaHora = mktime(&dateStruct);
  // std::cout << "fechaHora: " << fechaHora << std::endl;
  ipDecimal = 0;
}

std::string Registro::getAll() const {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " +
         ip + ":" + puerto + " " + falla;
}

std::string Registro::getIP(){
  return ip;
}

// Comparacion de objetos de la clase Registro usando el Linux timestamp
bool Registro::operator==(Registro &other) {
  return this->ipDecimal == other.ipDecimal;
}

bool Registro::operator!=( Registro &other) {
  return this->ipDecimal != other.ipDecimal;
}

bool Registro::operator>=(Registro &other) {
  return this->ipDecimal >= other.ipDecimal;
}

bool Registro::operator<=(Registro &other) {
  return this->ipDecimal <= other.ipDecimal;
}

bool Registro::operator>(Registro &other) { 
  return this->ipDecimal > other.ipDecimal; 
  }

bool Registro::operator<(Registro &other) { 
  return this->ipDecimal < other.ipDecimal; 
  }

// declarado como firend de la clase Registro
std::ostream& operator<<(std::ostream& os,const Registro& reg) {
    os << reg.getAll();
    return os;
}

/*
unsigned int Registro::getIpDecimal() {
  std::istringstream iss(ip);
  std::string primero, segundo, tercero, cuarto;
  int i, j, k, l;
  unsigned int resp;
  std::getline(iss, primero, '.');
  std::getline(iss, segundo, '.');
  std::getline(iss, tercero, '.');
  std::getline(iss, cuarto);
  i = std::stoi(primero);
  j = std::stoi(segundo);
  k = std::stoi(tercero);
  l = std::stoi(cuarto);
  resp = i * pow(256, 3) + j * pow(256, 2) + k * 256 + l;

  return resp;
}
*/
