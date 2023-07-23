#ifndef _KBB_H_
#define _KBB_H_

#define ADDR_A0 7
#define ADDR_A1 19
#define ADDR_A2 18

#define SEG0    4
#define SEG1    12
#define SEG2    6
#define SEG3    8
#define SEG4    9
#define SEG5    10
#define SEG6    5
#define SEG7    13

#define NUMBER_OF_SEGS  8
#define KEYS_IN_SEGS    8


class KBB{
private:
  bool ActualKeyMap[NUMBER_OF_SEGS * KEYS_IN_SEGS];
  bool LastKeyMap[NUMBER_OF_SEGS * KEYS_IN_SEGS];
  bool PressKeyMap[NUMBER_OF_SEGS * KEYS_IN_SEGS];
  bool ReleaseKeyMap[NUMBER_OF_SEGS * KEYS_IN_SEGS];

public:
  void begin();
  void ChangeSegment(unsigned char seg);
  void RefreshActualKeyMap(unsigned char seg);
  bool CompareActualAndLastKeys(unsigned char seg);
  void CopyActualToLastSegment(unsigned char seg);
  void SendChangesToHost(unsigned char seg);
  KBB();
  ~KBB();
};

#endif _KBB_H_






