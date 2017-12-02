// CString.h
#ifndef __CSTRING_H__
#define __CSTRING_H__

#include "fonts/fonts.h"
#include "CTaskStack.h"

//namespace CString {

void show_string(uint8_t* msg, TaskStack::CScreenTask* task, uint8_t x, uint8_t y);

void show_string(uint8_t* msg, TaskStack::CScreenTask* task, uint8_t x, uint8_t y)
{
  for(size_t i = 0; msg[i] != 0 ; ++i)
    {    
      TaskStack::CImagePart ip = Fonts::GetFontImagepart(*(msg + i));
        
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


  enum enum_encoding {
    enc_8_bit,
    enc_16_bit,
  };
  
  class CString {
  public:
  CString(const uint8_t* str, enum_encoding encoding)
    : data8_(str)
      , data16_((uint16_t*)str)
      , encoding_(encoding)
      , len_(0)
      {
	
	switch(encoding) {
	case enc_16_bit:
	  for(; data16_[len_] != 0; ++len_) {}

	  for(size_t i = 0; i < len_; ++i) {
	    Serial.print(" ");
	    Serial.print(data16_[i], HEX);
	  }
	  break;
	case enc_8_bit:
	  for(; data8_[len_] != 0; ++len_) {}
	  
	  for(size_t i = 0; i < len_; ++i) {
	    Serial.print(" ");
	    Serial.print(data8_[i]);
	  }
	  break;
	default:
	  Serial.println("ERROR: this string encodig can not be handled");
	  break;
	}
	Serial.print(" String len: ");
	Serial.println(len_);
      }
    /*
      void AddToScreenTask(TaskStack::CScreenTask* task, uint8_t x, uint8_t y) {
      uint8_t i;

      if(encoding_ == 1) {
      Serial.print("TEXT TO SHOW: ");
      for(int i = 0; i < size_; ++i) {
      Serial.print(str_[i]);
      Serial.print(" ");
      }
      }
      else if(encoding_ == 2) {
      
      Serial.print("TEXT TO SHOW: ");
      for(int i = 0; i < size_; ++i) {
      Serial.print(str16_[i]);
      Serial.print(" ");
      }
      }
      else {
      Serial.println("!! ERROR ENCODING INVALID!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      }
    
      Serial.println("");
      
      for(i = 0; i < size_; ++i) {

      TaskStack::CImagePart* ip = Fonts::GetFontImagepart(str_[i]);
      
      task->AddPart(ip);
      
      ip->setPosition(x, y);
      
      x += ip->DataSize().w();
      } //for
      }
    */
    size_t Size() {
      return len_;
    }

    uint16_t* GetData16Ptr() {
      return data16_;
    }

    uint8_t* GetData8Ptr() {
      return data8_;
    }
    
  private:
    uint8_t size_;
    uint8_t* data8_;
    uint16_t* data16_;
    uint8_t encoding_;
    size_t len_;
  }; //class
//} namespace //CString

#endif
