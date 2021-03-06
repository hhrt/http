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

int *Torrent::id(){
  return &Id;
};

double *Torrent::size(){
  return &Size;
};

std::string *Torrent::name(){
  return &Name;
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
  return Id == *b.id();
};

bool Torrent::operator<(Torrent b) {
  return Id < *b.id();
};

TorrentsList::TorrentsList(std::string r, unsigned int t) {
  Result = r;
  Tag = t;
};

TorrentsList::TorrentsList() {
  Result = "";
  Tag = 0;
};

std::string *TorrentsList::result() {
  return &Result;
};

unsigned int *TorrentsList::tag() {
  return &Tag;
};

std::vector<Torrent> *TorrentsList::torrents() {
  return &Torrents;
};
