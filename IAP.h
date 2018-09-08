#ifndef	__IAP_H__
#define	__IAP_H__

u8 IapReadByte(u16 addr);
void IapProgramByte(u16 addr, u8 dat);
void IapEraseSector(u16 addr);

#endif