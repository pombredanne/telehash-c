#ifndef packet_h
#define packet_h

#include "hn.h"
#include "path.h"

// the maximum index size of how many top level elements there are in the json (each keypair is 4)
#define JSONDENSITY 64

typedef struct packet_struct
{
  unsigned char *raw;
  unsigned char *body;
  unsigned short body_len;
  unsigned char *json;
  unsigned short json_len;
  unsigned short js[JSONDENSITY];
  struct packet_struct *next;
  hn_t to, from;
  path_t in, out, direct;
} *packet_t;

// these all allocate/free memory
packet_t packet_new();
packet_t packet_copy(packet_t p);
void packet_free(packet_t p);

// initialize json/body from raw
void packet_init(packet_t p, unsigned char *raw, unsigned short len);
// return raw info from stored json/body
unsigned char *packet_raw(packet_t p);
unsigned short packet_len(packet_t p);

// set/store these in the current packet
void packet_json(packet_t p, unsigned char *json, unsigned short len);
void packet_body(packet_t p, unsigned char *body, unsigned short len);

// convenient json setters
void packet_set(packet_t p, char *key, char *val); // raw
void packet_set_str(packet_t p, char *key, char *val); // escapes value
void packet_set_int(packet_t p, char *key, int val);

#endif