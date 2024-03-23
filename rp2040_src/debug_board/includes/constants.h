#ifndef MSX_DEBUG_CONSTANTS_H
#define MSX_DEBUG_CONSTANTS_H

#define D_UART_TX 0
#define D_UART_RX 1
#define D_AD0 2
#define D_AL_PULSE  10
#define D_AH_PULSE  11
#define D_UNCONNECTED_1  12
#define D_UNCONNECTED_2  13
#define D_UNCONNECTED_3  14
#define D_UNCONNECTED_4  15
#define D_nDOUT  16
#define D_nDOE  17
#define D_nWAIT  18
#define D_nCS1  19
#define D_nCS2  20
#define D_nWRITE  21
#define D_nREAD  22
#define D_SDA  26
#define D_SCL  27
#define D_nSLTSEL  28


#define D_GPIO_INIT_MASK                                                         \
  (1 << D_AL_PULSE | 1 << D_AH_PULSE | 1 << D_nDOUT | 1 << D_nDOE |            \
   1 << D_nWAIT | 1 << D_nCS1 | 1 << D_nCS2 | 1 << D_nWRITE | 1 << D_nREAD |   \
   1 << D_nSLTSEL)


#endif


