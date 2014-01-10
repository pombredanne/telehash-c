#include <stdio.h>
#include <string.h>

#include "switch.h"
#include "util.h"

int main(void)
{
  unsigned char out[4096];
  hn_t id;
  switch_t s;
  hnt_t seeds;
  chan_t c;
  packet_t p;

  crypt_init();
  s = switch_new();

  id = hn_getfile(s->index, "id.json");
  if(!id)
  {
    printf("failed to load id.json: %s\n", crypt_err());
    return -1;
  }
  if(switch_init(s, id))
  {
    printf("failed to init switch\n");
    return -1;
  }
  printf("loaded hashname %s\n",s->id->hexname);

  seeds = hn_getsfile(s->index, "seeds.json");
  if(!seeds || !hnt_get(seeds, 0))
  {
    printf("failed to load seeds.json: %s\n", crypt_err());
    return -1;
  }
  
  c = chan_new(s, hnt_get(seeds, 0), "seek", 0);
  p = chan_packet(c);
  printf("chan packet %s\n",util_hex(packet_raw(p),packet_len(p),out));

  return 0;
}
