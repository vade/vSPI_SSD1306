/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution


--11/20/2012--
Modified to use hardware SPI on both Arduino Uno and Akafuino X by Nathan Duprey
*********************************************************************/

#include "Arduino.h"

#include <Adafruit_GFX.h>
#include <SPI.h>

#define BLACK 0
#define WHITE 1


#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

//Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

class vSPI_SSD1306 : public Adafruit_GFX
{
	public:
 
		vSPI_SSD1306(int8_t CS, int8_t RESET, int8_t DC, uint8_t* buffer, uint8_t width, uint8_t height);

		void begin(uint8_t switchvcc = SSD1306_SWITCHCAPVCC);
		void display();
		void clearDisplay(void);

		void invertDisplay(uint8_t i);
		void drawPixel(int16_t x, int16_t y, uint16_t color);

		void startscrollright(uint8_t start, uint8_t stop);
		void startscrollleft(uint8_t start, uint8_t stop);

		void startscrolldiagright(uint8_t start, uint8_t stop);
		void startscrolldiagleft(uint8_t start, uint8_t stop);
		void stopscroll(void);

	private:

		int8_t dc, rst, cs;
		uint8_t* buffer;
	
		#if defined(__AVR_XMEGA__)
		volatile uint16_t *csport, *dcport;
		#else
		volatile uint8_t *csport, *dcport;
		#endif
		uint8_t cspinmask, dcpinmask;

		void SPItransfer(uint8_t command);
 };