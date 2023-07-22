#ifndef _KBB_H_
#define _KBB_H_

#define ADDR_A0 7
#define ADDR_A1 19
#define ADDR_A2 18
#define NUMBER_OF_SEG 8

class KBB{
private:
  bool CapsLockActualState;
  bool NumLockActualState;
  bool ScrollLockActualState;
public:
  bool CapsLockState;
  bool NumLockState;
  bool ScrollLockState;

  void ChangeSegment(unsigned char seg);
  void begin();
  void CheckSegment(unsigned char seg);
  KBB();
  ~KBB();
};

#endif _KBB_H_