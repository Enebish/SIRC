/*
 * sony.c
 *
 *  Created on: 01.02.2016
 *      Author: b_ene_000
 */
#include <ir_sony.h>

/** @defgroup Samsung SIRC_Exported_Constants
  * @{
  */

/* Table of SIRC commands */
void* IR_SonyCommands[128] = {
        "      Dual 1-2      ",   /* 0 */
        "       Source       ",   /* 1 */
        "        Power       ",   /* 2 */
        "                    ",   /* 3 */
        "        Num1        ",   /* 4 */
        "        Num2        ",   /* 5 */
        "        Num3        ",   /* 6 */
        "      Volume Up     ",   /* 7 */
        "        Num4        ",   /* 8 */
        "        Num5        ",   /* 9 */
        "        Num6        ",   /* 10 */
        "     Volume Down    ",   /* 11 */
        "        Num7        ",   /* 12 */
        "        Num8        ",   /* 13 */
        "        Num9        ",   /* 14 */
        "        Mute        ",   /* 15 */
        "     Channel Down   ",   /* 16 */
        "        Num0        ",   /* 17 */
        "     Channel Up     ",   /* 18 */
        "      Pre Channel   ",   /* 19 */
        "                    ",   /* 20 */
        "        Power       ",   /* 21 */
        "        Reset       ",   /* 22 */
        "      Audio Mode    ",   /* 23 */
        "      Picture Up    ",   /* 24 */
        "     Picture Down   ",   /* 25 */
        "        Menu        ",   /* 26 */
        "     Colour Down    ",   /* 27 */
        "      Reserved      ",   /* 28 */
        "      Reserved      ",   /* 29 */
        "    Brightness Up   ",   /* 30 */
        "        Info        ",   /* 31 */
        "       Hue Up       ",   /* 32 */
        "      Hue Down      ",   /* 33 */
        "    Sharpness Up    ",   /* 34 */
        "   Sharpness Down   ",   /* 35 */
        "   Select TV Tuner  ",   /* 36 */
        "    AD/Subtitel     ",   /* 37 */
        "   Balance Right    ",   /* 38 */
        "      Reserved      ",   /* 39 */
        "    Picture Mode    ",   /* 40 */
        "    Surround on/off ",   /* 41 */
        "      Reserved      ",   /* 42 */
        "      Reserved      ",   /* 43 */
        "        Text        ",   /* 44 */
        "        Exit        ",   /* 45 */
        "      Reserved      ",   /* 46 */
        "     Power off      ",   /* 47 */
        "     Time Display   ",   /* 48 */
        "      Reserved      ",   /* 49 */
        "      Reserved      ",   /* 50 */
        "      Reserved      ",   /* 51 */
        "      Reserved      ",   /* 52 */
        "      Reserved      ",   /* 53 */
        "     Sleep Timer    ",   /* 54 */
        "      Reserved      ",   /* 55 */
        "      Reserved      ",   /* 56 */
        "      Reserved      ",   /* 57 */
        "   Channel Display  ",   /* 58 */
        "    Channel Jump    ",   /* 59 */
        "      Reserved      ",   /* 60 */
        "      Reserved      ",   /* 61 */
        "    Picture Size    ",   /* 62 */
        "      E-Manual      ",   /* 63 */
        " Select Input video1",   /* 64 */
        " Select Input video2",   /* 65 */
        " Select Input video3",   /* 66 */
        "      Reserved      ",   /* 67 */
        "      Reserved      ",   /* 68 */
        "         <<         ",   /* 69 */
        "        Stop        ",   /* 70 */
        "        Play        ",   /* 71 */
        "         >>         ",   /* 72 */
        "       Record       ",   /* 73 */
        "       Pause        ",   /* 74 */
        "       Tools        ",   /* 75 */
        "      Reserved      ",   /* 76 */
        "      Reserved      ",   /* 77 */
        "  Cable/Broadcast   ",   /* 78 */
        "        Guide       ",   /* 79 */
        "      Reserved      ",   /* 80 */
        "      Reserved      ",   /* 81 */
        "      Reserved      ",   /* 82 */
        "      Reserved      ",   /* 83 */
        "      Reserved      ",   /* 84 */
        "      Reserved      ",   /* 85 */
        "      Reserved      ",   /* 86 */
        "      Reserved      ",   /* 87 */
        "        Return      ",   /* 88 */
        "   PIP Channel Down ",   /* 89 */
        "      Reserved      ",   /* 90 */
        "      PIP on        ",   /* 91 */
        "    Freeze Screen   ",   /* 92 */
        "      Reserved      ",   /* 93 */
        "     PIP Position   ",   /* 94 */
        "      PIP Swap      ",   /* 95 */
        "         Up         ",   /* 96 */
        "        Down        ",   /* 97 */
        "        Right       ",   /* 98 */
        "     Exit Setup     ",   /* 99 */
        "      Reserved      ",   /* 100 */
        "        Lift        ",   /* 101 */
        "      Reserved      ",   /* 102 */
        "      Reserved      ",   /* 103 */
        "        Enter       ",   /* 104 */
        "      Reserved      ",   /* 105 */
        "      Reserved      ",   /* 106 */
        "    Channel List    ",   /* 107 */
        "      Reserved      ",   /* 108 */
        "      Reserved      ",   /* 109 */
        "         SRS        ",   /* 110 */
        "       PIP off      ",   /* 111 */
        "       Treble Up    ",   /* 112 */
        "      Treble Down   ",   /* 113 */
        "       Bass Up      ",   /* 114 */
        "      Bass Down     ",   /* 115 */
        "       + Key        ",   /* 116 */
        "       - Key        ",   /* 117 */
        "      Reserved      ",   /* 118 */
        "    Slipt Screen    ",   /* 119 */
        "    Add Channel     ",   /* 120 */
        "      Contents      ",   /* 121 */
        "      Reserved      ",   /* 122 */
        "      Reserved      ",   /* 123 */
        "      Reserved      ",   /* 124 */
        "  Trinitone on/off  ",   /* 125 */
        "      Reserved      ",   /* 126 */
        "Display a red Rtests"    /* 127 */
};

/* Table of SIRC address */
void* IR_SonyDevices[32] = {
         "        SAT         ",  /* 0 */
         "         TV         ",  /* 1 */
         "        VTR1        ",  /* 2 */
         "      Teletext      ",  /* 3 */
         "     widescreen     ",  /* 4 */
         "                    ",  /* 5 */
         "     laser Disk     ",  /* 6 */
         "         TV         ",  /* 7 */
         "                    ",  /* 8 */
         "                    ",  /* 9 */
         "                    ",  /* 10 */
         "        VTR3        ",  /* 11 */
         "Surround Sound Proc ",  /* 12 */
         "                    ",  /* 13 */
         "                    ",  /* 14 */
         "                    ",  /* 15 */
         "    Audio/Cassette  ",  /* 16 */
         "         CD         ",  /* 17 */
         "     Equalizer      ",  /* 18 */
         "                    ",  /* 19 */
         "                    ",  /* 20 */
         "                    ",  /* 21 */
         "                    ",  /* 22 */
         "                    ",  /* 23 */
         "                    ",  /* 24 */
         "                    ",  /* 25 */
         "      DVD Player    ",  /* 26 */
         "                    ",  /* 27 */
         "                    ",  /* 28 */
         "                    ",  /* 29 */
         "                    ",  /* 30 */
         "                    ",  /* 31 */
};

void ConvertSony(void)
{
  DecDeviceID = 0;
//  DecCommandID = 0;
//  comL = 0;
//  comH = 0;
//  devL = 0;
//  devH = 0;
//  memset(CommandIDL, 0, sizeof(CommandIDL));
//  memset(CommandIDH, 0, sizeof(CommandIDH));
//  memset(DeviceIDL, 0, sizeof(DeviceIDL));
//  memset(DeviceIDH, 0, sizeof(DeviceIDH));
//
//  DecDeviceID = (uint16_t) IRTmpPacket.data & 0xFFFF;
//  DecCommandID = (uint16_t) (IRTmpPacket.data >> 16);
//
//  devL = (uint8_t)  IRTmpPacket.data & 0xFF;
//  devH = (uint8_t) (IRTmpPacket.data >> 8) & 0xFF;
//  comL = (uint8_t) (IRTmpPacket.data >> 16) & 0xFF;
//  comH = (uint8_t) (IRTmpPacket.data >> 24) & 0xFF;
//
//  for (uint8_t i=0; i<8; i++)
//  {
//    if (1 & (comL >> i))
//      CommandIDL[7-i] = 49;
//    else
//      CommandIDL[7-i] = 48;
//
//    if (1 & (comH >> i))
//      CommandIDH[7-i] = 49;
//    else
//      CommandIDH[7-i] = 48;
//
//    if (1 & (devL >> i))
//      DeviceIDL[7-i] = 49;
//    else
//      DeviceIDL[7-i] = 48;
//
//    if (1 & (devH >> i))
//      DeviceIDH[7-i] = 49;
//    else
//      DeviceIDH[7-i] = 48;
//  }
//  BSP_LCD_SetFont(&Font16);
//  snprintf(Buffer, 7, "%*d", 4, DecDeviceID);
//  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//  BSP_LCD_DisplayStringAt(10, 60, (uint8_t*) "Device ID:               ", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(180, 60, (uint8_t*)Buffer, LEFT_MODE);
//  BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
//  BSP_LCD_DisplayStringAt(10, 85, (uint8_t*) "         L", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 85, (uint8_t*) DeviceIDL, LEFT_MODE);
//  snprintf(Buffer, 7, "%*d", 4, devL);
//  BSP_LCD_DisplayStringAt(180, 95, (uint8_t*) Buffer, LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 110, (uint8_t*) "         H", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 110, (uint8_t*) DeviceIDH, LEFT_MODE);
//  snprintf(Buffer, 7, "%*d", 4, devH);
//  BSP_LCD_DisplayStringAt(180, 110, (uint8_t*) Buffer, LEFT_MODE);
//
//  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//  snprintf(Buffer, 7, "%*d", 4, DecCommandID);
//  BSP_LCD_DisplayStringAt(10, 140, (uint8_t*) "Command ID:              ", LEFT_MODE);
//  BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
//  BSP_LCD_DisplayStringAt(180, 140, (uint8_t*)Buffer, LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 170, (uint8_t*) "         L", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 170, (uint8_t*) CommandIDL, LEFT_MODE);
//  snprintf(Buffer, 7, "%*d", 4, comL);
//  BSP_LCD_DisplayStringAt(180, 170, (uint8_t*) Buffer, LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 195, (uint8_t*) "         H", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 195, (uint8_t*) CommandIDH, LEFT_MODE);
//  snprintf(Buffer, 7, "%*d", 4, comH);
//  BSP_LCD_DisplayStringAt(180, 195, (uint8_t*) Buffer, LEFT_MODE);
//
//  Cnt++;
//  snprintf(Buffer, 7, "%*d", 4, Cnt);
//  BSP_LCD_DisplayStringAt(120, 230, (uint8_t*) "      ", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(120, 230, (uint8_t*) Buffer, LEFT_MODE);
//
//  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//
//  sprintf(hex, "%x", IRTmpPacket.data);
//  BSP_LCD_DisplayStringAt(10, 230, (uint8_t*) "          ", LEFT_MODE);
//  BSP_LCD_DisplayStringAt(10, 230, (uint8_t*) hex, LEFT_MODE);
//
//  uint8_t temp;
//  temp = ~comH;
//#if defined SONY_SIRC
//  if (comL == temp)
//  {
//    BSP_LCD_SetFont(&Font20);
//    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//    BSP_LCD_DisplayStringAt(1, 255, (uint8_t*) IR_Commands[comL], CENTER_MODE);
//  }
//#endif
}




