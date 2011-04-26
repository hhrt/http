#include "torrent.h"

Torrent::Torrent( int i, double s, std::string n) {
  Id = i;
  Size = s;
  Name = n;
};

Torrent::Torrent() {
  Id = 0;
  Size = 0;
  Name = "";
};

Torrent::Torrent(Json::Value j) {

  Id = j.get("id", "0").asUInt();
  Size = j.get("totalSize", "0").asDouble();
  Name = j.get("name", "").asString();

}

int Torrent::id() const {
  return Id;
};

double Torrent::size() const {
  return Size;
};

std::string Torrent::name() const {
  return Name;
};

void Torrent::set_id(int i) {
  Id = i;
};

void Torrent::set_size(double s) {
  Size = s;
};

void Torrent::set_name(std::string n) {
  Name = n;
};

bool Torrent::operator==(Torrent b) {
  return Id == b.id();
};

bool Torrent::operator<(Torrent b) {
  return Id < b.id();
};
