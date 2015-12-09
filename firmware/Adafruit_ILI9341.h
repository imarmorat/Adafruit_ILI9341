/***************************************************
This is an Arduino Library for the Adafruit 2.2" SPI display.
This library works with the Adafruit 2.2" TFT Breakout w/SD card
----> http://www.adafruit.com/products/1480

Check out the links above for our tutorials and wiring diagrams
These displays use SPI to communicate, 4 or 5 pins are required to
interface (RST is optional)
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution
****************************************************/

#ifndef ADAFRUIT_ILI9341_H
#define ADAFRUIT_ILI9341_H

// Hack to get this to work in Spark IDE
#include "../Adafruit_mfGFX/Adafruit_mfGFX.h"
//#include "Adafruit_mfGFX.h"

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))

// https://community.particle.io/t/photon-and-the-pin-map-challenge/12223
#if defined(PLATFORM_ID)  //Only defined if a Particle device
  #include "application.h"
  STM32_Pin_Info* PIN_MAP = HAL_Pin_Map(); // Pointer required for highest access speed
#if (PLATFORM_ID == 0)  // Core
  #define pinLO(_pin) (PIN_MAP[_pin].gpio_peripheral->BRR = PIN_MAP[_pin].gpio_pin)
  #define pinHI(_pin) (PIN_MAP[_pin].gpio_peripheral->BSRR = PIN_MAP[_pin].gpio_pin)
#elif (PLATFORM_ID == 6) // Photon
  #define pinLO(_pin) (PIN_MAP[_pin].gpio_peripheral->BSRRH = PIN_MAP[_pin].gpio_pin)
  #define pinHI(_pin) (PIN_MAP[_pin].gpio_peripheral->BSRRL = PIN_MAP[_pin].gpio_pin)
#else
  #error "*** PLATFORM_ID not supported by this library. PLATFORM should be Core or Photon ***"
#endif
#endif

//typedef unsigned char prog_uchar;

#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 320

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0A
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29

#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR   0x30
#define ILI9341_MADCTL  0x36


#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

#define ILI9341_PIXFMT  0x3A

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1

// Color definitions
#define	ILI9341_BLACK   0x0000
#define	ILI9341_BLUE    0x001F
#define	ILI9341_RED     0xF800
#define	ILI9341_GREEN   0x07E0
#define ILI9341_CYAN    0x07FF
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW  0xFFE0
#define ILI9341_WHITE   0xFFFF


class Adafruit_ILI9341 : public Adafruit_GFX {

public:
	Adafruit_ILI9341(uint8_t CS, uint8_t RS, uint8_t RST);

	void     begin(void),
		setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1),
		pushColor(uint16_t color),
		fillScreen(uint16_t color),
		drawPixel(int16_t x, int16_t y, uint16_t color),
		drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
		drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
		fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
		uint16_t color),
		setRotation(uint8_t r),
		invertDisplay(boolean i);

	uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);

	/* These are not for current use, 8-bit protocol only! */
	uint8_t  readdata(void), readcommand8(uint8_t);
	
	void     spiwrite(uint8_t),
		writecommand(uint8_t c),
		writedata(uint8_t d),
		commandList(uint8_t *addr);
	uint8_t  spiread(void);

private:

	uint8_t  tabcolor;

	volatile uint8_t *mosiport, *clkport, *dcport, *rsport, *csport;

	uint8_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
};

#endif
