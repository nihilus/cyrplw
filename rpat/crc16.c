#define POLY 0x8408
/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/

unsigned short crc16(unsigned char *data_p,unsigned short length) 
{
  unsigned char i;
  unsigned int data;
  unsigned int crc = 0xFFFF;

  if ( length == 0 ) return 0;

  do {
    data = *data_p++;
    for ( i=0; i < 8; i++ ) {
      if ( (crc ^ data) & 1 )
        crc = (crc >> 1) ^ POLY;
      else
        crc >>= 1;
      data >>= 1;
    }
  } while (--length);

  crc = ~crc;
  data = crc;
  crc = (crc << 8) | ((data >> 8) & 0xff);
  return (crc);
}
