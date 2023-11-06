/*
TeenySevenSeg - Header file for the TeenySevenSeg Arduino Library.
Copyright (C) *** Need copyright statement here ***

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _TEENYSEVENSEG_H
#define _TEENYSEVENSEG_H

#include <Arduino.h>

/********************************************************************/
template <class T>
class TeenySevenSeg {

  public:

    TeenySevenSeg(T& displayObj) : _displayObj(displayObj) {};

    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
      _displayObj.drawFastHLine(x, y, w, color);
    }

    void drawFastVLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
      _displayObj.drawFastVLine(x, y, w, color);
    }

    void drawSSDigit(int16_t value, int16_t x, int16_t y, int16_t l, int16_t w, uint16_t color) {
      switch(value) {
        case -1:
          drawSSDigitSegs(_digitSegV_blank, x, y, l, w, color);
          break;
        case 0:
          drawSSDigitSegs(_digitSegV_0, x, y, l, w, color);
          break;
        case 1:
          drawSSDigitSegs(_digitSegV_1, x, y, l, w, color);
          break;
        case 2:
          drawSSDigitSegs(_digitSegV_2, x, y, l, w, color);
          break;
        case 3:
          drawSSDigitSegs(_digitSegV_3, x, y, l, w, color);
          break;
        case 4:
          drawSSDigitSegs(_digitSegV_4, x, y, l, w, color);
          break;
        case 5:
          drawSSDigitSegs(_digitSegV_5, x, y, l, w, color);
          break;
        case 6:
          drawSSDigitSegs(_digitSegV_6, x, y, l, w, color);
          break;
        case 7:
          drawSSDigitSegs(_digitSegV_7, x, y, l, w, color);
          break;
        case 8:
          drawSSDigitSegs(_digitSegV_8, x, y, l, w, color);
          break;
        case 9:
          drawSSDigitSegs(_digitSegV_9, x, y, l, w, color);
          break;
        default:
          drawSSDigitSegs(_digitSegV_error, x, y, l, w, color);
          break;
      }
    }

    void drawSSTwoDigit(int16_t value, int16_t x, int16_t y, int16_t l, int16_t w, int16_t s, uint16_t color) {
      int16_t _value = min(value, 99);
      int digitOffset = 0;
      if(_value < 10) {
        drawSSDigit(0, x+digitOffset, y, l, w, color);
      } else {
        drawSSDigit((_value/10), x+digitOffset, y, l, w, color);
      }
      digitOffset+=l+s;
      drawSSDigit((_value%10), x+digitOffset, y, l, w, color);
    }

    void drawSSClock(uint32_t time, int16_t x, int16_t y, int16_t l, int16_t w, uint16_t color) {
      drawSSClock(time, x, y, l, w, w, w, w, color);
    }

    void drawSSClock(uint32_t time, int16_t x, int16_t y, int16_t l, int16_t w, int16_t s, int16_t cw, int16_t cs, uint16_t color) {
      uint32_t _time = min(time, (uint32_t) 5999);
      int mins = _time / 60;
      int secs = _time % 60;
      int digitOffset = 0;
      if(mins < 10) {
        drawSSDigit(0, x+digitOffset, y, l, w, color);
      } else {
        drawSSDigit((mins/10), x+digitOffset, y, l, w, color);
      }
      digitOffset+=l+s;
      drawSSDigit((mins%10), x+digitOffset, y, l, w, color);
      digitOffset+=l+cs;
      drawSSColon(x+digitOffset, y, l, w, cw, color);
      digitOffset+=cw+cs;
      if(secs < 10) {
        drawSSDigit(0, x+digitOffset, y, l, w, color);
      } else {
        drawSSDigit((secs/10), x+digitOffset, y, l, w, color);
      }
      digitOffset+=l+s;
      drawSSDigit((secs%10), x+digitOffset, y, l, w, color);
    }

  protected:

  private:

    T& _displayObj;

    typedef enum{ SegA, SegB, SegC, SegD, SegE, SegF, SegG } segName_t;
    typedef enum{ SegH, SegV } segDir_t;

    uint8_t _digitSegV_blank[7] = {0, 0, 0, 0, 0, 0, 0};
    uint8_t _digitSegV_0[7]     = {1, 1, 1, 1, 1, 1, 0};
    uint8_t _digitSegV_1[7]     = {0, 1, 1, 0, 0, 0, 0};
    uint8_t _digitSegV_2[7]     = {1, 1, 0, 1, 1, 0, 1};
    uint8_t _digitSegV_3[7]     = {1, 1, 1, 1, 0, 0, 1};
    uint8_t _digitSegV_4[7]     = {0, 1, 1, 0, 0, 1, 1};
    uint8_t _digitSegV_5[7]     = {1, 0, 1, 1, 0, 1, 1};
    uint8_t _digitSegV_6[7]     = {1, 0, 1, 1, 1, 1, 1};
    uint8_t _digitSegV_7[7]     = {1, 1, 1, 0, 0, 0, 0};
    uint8_t _digitSegV_8[7]     = {1, 1, 1, 1, 1, 1, 1};
    uint8_t _digitSegV_9[7]     = {1, 1, 1, 0, 0, 1, 1};
    uint8_t _digitSegV_error[7] = {1, 0, 0, 1, 1, 1, 1};

    // Segment Map
    //
    //     A
    //   F   B
    //     G
    //   E   C
    //     D
    //

    void drawSSSegStripe(segName_t segName, int16_t n, int16_t x, int16_t y, int16_t l, int16_t w, uint16_t color) {
      struct SegInfo { segDir_t segDir; int16_t xOffset, yOffset; } segInfo;
      // Get raw segment x0,y0
      switch(segName) {
        case SegA : segInfo={SegH, 0,     n           }; break;
        case SegB : segInfo={SegV, l-n-1, 0           }; break;
     // case SegC : segInfo={SegV, l-n-1, l-w         }; break;
        case SegC : segInfo={SegV, l-n-1, l-w+(w<3 ? 0 : (w%2==0 ? 0 : 1))       }; break;
        case SegD : segInfo={SegH, 0,     (2*l)-w-n-1 }; break;
     // case SegE : segInfo={SegV, n,     l-w         }; break;
        case SegE : segInfo={SegV, n,     l-w+(w<3 ? 0 : (w%2==0 ? 0 : 1))       }; break;
        case SegF : segInfo={SegV, n,     0           }; break;
        case SegG : segInfo={SegH, 0,     l-n-1       }; break;
        default   : segInfo={SegH, 0,     n           }; break;
      }
      // Clip segment ends (this needs aesthetic tuning)
      int16_t segClip = 0;
      if(w < 2) {
        segClip = 1;
      } else {
        if(segName==SegG) {
          if(n > (w/2)) segClip=n-(w/2);
          if(w%2==0) {
            if(n < ((w/2)-1)) segClip=((w/2)-1)-n;
          } else {
            if(n < ((w/2)-0)) segClip=((w/2)-0)-n;
          }
          segClip++;
        } else {
          if(n < (w/2)) segClip=(w/2)-n;
        }
      }
      if(segInfo.segDir==SegH) {
        //for(int16_t x0=(x+segInfo.xOffset+segClip);
        //    x0<=(x+segInfo.xOffset+l-1-segClip); x0++) {
        //  drawPixel(x0, (y+segInfo.yOffset), color);
        //}
        drawFastHLine(x+segInfo.xOffset+segClip, y+segInfo.yOffset, l-(segClip*2), color);
      } else {
        //for(int16_t y0=(y+segInfo.yOffset+segClip);
        //     y0<=(y+segInfo.yOffset+l-1-segClip); y0++) {
        //  drawPixel((x+segInfo.xOffset), y0, color);
        //}
        drawFastVLine(x+segInfo.xOffset, y+segInfo.yOffset+segClip, l-(segClip*2)-(w<3 ? 0 : (w%2==0 ? 0 : 1)), color);
      }
    }

    void drawSSSeg(segName_t segName, int16_t x, int16_t y, int16_t l, int16_t w, uint16_t color) {
      for(int16_t i=0; i<w; i++) {
        drawSSSegStripe(segName, i, x, y, l, w, color);
      }
    }

    void drawSSDigitSegs(const uint8_t segMask[7], int16_t x, int16_t y, int16_t l, int16_t w, uint16_t color) {
      segName_t segNameList[7] = {SegA, SegB, SegC, SegD, SegE, SegF, SegG};
      for(int i=0; i<7; i++) {
        if(segMask[i]==1) drawSSSeg(segNameList[i], x, y, l, w, color);
      }
    }

    void drawSSColon(int16_t x, int16_t y, int16_t l, int16_t cl, int16_t cw, uint16_t color) {
      struct SegInfo { segDir_t segDir; int16_t xOffset, yOffset; } segInfo;
      int16_t colonOffset = (l/2)-1;
      for(int16_t i=0; i<2; i++) {     //i=segment count
        for(int16_t j=0; j<cw; j++) {   //j=stripe count
          segInfo={SegV, j, i*(l-cw)};
          //for(int16_t k=0; k<cl; k++) {   //k=pixel count
          //  drawPixel((x+segInfo.xOffset), (y+segInfo.yOffset+colonOffset+k), color);
          //}
          drawFastVLine(x+segInfo.xOffset, y+segInfo.yOffset+colonOffset, cl, color);
        }
      }
    }

};

#endif // _TEENYSEVENSEG_H

