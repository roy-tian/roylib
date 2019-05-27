#ifndef ROYMAP_H
#define ROYMAP_H

struct _RoyMap {
  void           * key;
  void           * value;
  struct _RoyMap * left;
  struct _RoyMap * right;
};


#endif // ROYMAP_H