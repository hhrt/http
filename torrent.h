#ifndef TORRENT_H
#define TORRENT_H

#include <string>
#include <json/json.h>
class Torrent {

  int Id;
  double Size;
  std::string Name;

  public:
  Torrent(int i, double s, std::string n);
  Torrent(Json::Value j);
  Torrent();
  int id() const;
  double size() const;
  std::string name() const;

  void set_id(int i);
  void set_size(double s);
  void set_name(std::string n);

  bool operator==(Torrent b);
  bool operator<(Torrent b);
};


#endif
