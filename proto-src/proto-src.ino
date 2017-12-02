
// The display is SPI, include the library header.


// Include the ePaper module header.
#include "CTaskStack.h"
#include "fonts/fonts.h"
#include "CString.h"

// Include the images. These images were prepared with "bmp_to_epaper" which
// is available on the Crystalfontz site.
//#include "Images_for_CFAP200200A00154.h"
// This module is 200x200 pixels. Make sure that the image files make sense.
//#if ((HEIGHT_PIXELS != (200)) || (WIDTH_PIXELS  != (200)))
//#error "IMAGE INCLUDE FILE IS WRONG SIZE"
//#endif

void show_string(CString msg, TaskStack::CPoint point);

TaskStack::CStack stack;

void setup() {
  // put your setup code here, to run once:
  //Debug port / Arduino //Serial Monitor
  //Serial.begin(9600);
  
  // Configure the pin directions
  pinMode(EPD_BUSY, INPUT);
  pinMode(EPD_RESET , OUTPUT);   
  pinMode(EPD_CS, OUTPUT);     
  pinMode(EPD_DC, OUTPUT);     
  pinMode(EPD_BUSSEL, OUTPUT);
  // Set output pins' default state
  digitalWrite(EPD_RESET, HIGH);   //active low
  digitalWrite(EPD_CS, HIGH);      //active low
  digitalWrite(EPD_DC, HIGH);      //active low 
  digitalWrite(EPD_BUSSEL, LOW);   // 4 wire mode
  
  //Set up SPI interface
  SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
  SPI.begin();
  //Initialize the display controller hardware 
  ePaper_Init();
  
  TaskStack::CScreenTask scr_task(0);
  TaskStack::CScreenTask scr_task2(1);
    
  stack.Add(&scr_task);
  stack.Add(&scr_task2);

  Show_Full_Screen_Image(Mono_lup_1BPP,      //image data
                         WIDTH_PIXELS,   //X size
                         HEIGHT_PIXELS); //Y size

  //абвгдеёжзийклмнопрстуфхцчшщъыьэюя\0"
  //show_string( CString("абвгдеёжзийклмнопрстуфхцчшщъыьэюя\0", enc_8_bit),
  /*  uint8_t* str PROGMEM = "марковка, я тебя люблю!\0";
  show_string( CString(str, enc_8_bit),
	       &scr_task,
	       TaskStack::CPoint(1, 170));
  
  uint8_t* str2 PROGMEM = "о как :)!\0";
  show_string( str2, &scr_task,1, 146);
  */

  
  uint8_t* str3 PROGMEM = "abcdefghijklmnopqrstuvwxyz\0";
  show_string( str3, &scr_task,1, 130);
  
  
}


void show_string(CString msg, TaskStack::CScreenTask* task, TaskStack::CPoint point)
{
  uint8_t x = 24 - point.x();
  uint8_t y = point.y();
  
  for(size_t i = 0; i < msg.Size(); ++i)
    {    
      TaskStack::CImagePart ip = Fonts::GetFontImagepart(*(msg.GetData8Ptr() + i));
        
      if(x <= 2) {
	x = 23;
	y -= ip.DataSize().h();
      }
      else {
	x -= ip.DataSize().w();
      }
      x -= ip.DataSize().w();
      
      ip.setPosition(x, y);
      x++;

      task->AddPart(ip);
    } //for
}

void loop() {
  //Serial.println("hey!");
  // put your main code here, to run repeatedly:
  
  delay(3000);
  
  stack.Do();
  
}
