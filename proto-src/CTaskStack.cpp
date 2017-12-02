// CTaskStack.cpp

#include "CTaskStack.h"

namespace TaskStack
{
  CStack::CStack() {
    m_task_list.clear();
  }
    
  ITask* CStack::Next() {
    return m_task_list.back();
  }
        
  void CStack::Add(ITask* new_task) {
    m_task_list.push_back(new_task);
        
    if(m_task_list.size() > 0)
      it = m_task_list.begin();
  }
    
  void CStack::Remove(ITask* task_to_del) {
    // search for task_to_del->id in list and remove the entry
  }

  void CStack::Do() {
    if(m_task_list.size() <= 0) 
      return;

    ITask* task = *it;
#ifndef ENABLE_SERIAL
    std::cout << "task stack size: " << m_task_list.size() << std::endl;
#endif
    task->Do();

    ++it;

    if(it == m_task_list.end()) {
      it = m_task_list.begin();
    }
  }

    
  task_type CGSMTask::Type() { return gsm_task; };

  uint8_t CGSMTask::Id() { return m_id; };

  void CGSMTask::Do() {};

    
  CScreenTask::CScreenTask(uint8_t id) {
    m_id = id;
  }

  task_type CScreenTask::Type() { return screen_task; };

  uint8_t CScreenTask::Id() { return m_id; };

  void CScreenTask::Do() { //print parts from imagePartsList
    //apply images from imagePartsList and do partial update

    if(m_imagePartsList.size() == 0)
      return;
    
    Load_LUT_For_Partial_Update();

    ePaper_POWERON();

    //Fill entire display RAM with background image.
    SetDisplayArea(0,                  // X start
		   WIDTH_MONO_BYTES-1, // X end
		   HEIGHT_PIXELS-1,    // Y start
		   0);                 // Y end
    Load_Flash_Image_To_Display_RAM(WIDTH_PIXELS,  //X size
				    HEIGHT_PIXELS, //Y size
				    Mono_lup_1BPP);    //Image

    //Swap foreground and background, this will
    //show the full-screen image we just put up.
    ePaper_Update_Partial();

    //Now again fill entire display RAM with the same
    //background image. This will make it so the parts
    //of the dispaly that are not changed by the partial
    //update do not flicker.
    //If you instead load Diag_1BPP, you can see the
    //background swap out on every other update.
    SetDisplayArea(0,                  // X start
		   WIDTH_MONO_BYTES-1, // X end
		   HEIGHT_PIXELS-1,    // Y start
		   0);                 // Y end

    Load_Flash_Image_To_Display_RAM(WIDTH_PIXELS,  //X size
				    HEIGHT_PIXELS, //Y size
				    Mono_lup_1BPP);    //Image
      
    for(it = m_imagePartsList.begin(); it != m_imagePartsList.end();
	++it) {
      CImagePart* image = &(*it);
      
#ifndef ENABLE_SERIAL
      std::cout << "image part id: "
		<< (int)((*it).Id()) << std::endl;
#else
      //Serial.print("image part id: "); //Serial.println((int)((*it).Id()));
      //Serial.print(" x = "); //Serial.println(image->Point().x());
      //Serial.print(" y = "); //Serial.println(image->Point().y());
#endif
            
      SetDisplayArea(image->Point().x(),         // X start
		     image->Point().x() + (image->DataSize().w() - 1),
		     //WIDTH_MONO_BYTES-1, // X end
		     image->Point().y(),
		     //HEIGHT_PIXELS-1,    // Y start
		     image->Point().y() + (image->DataSize().h() - 1));                 // Y end

      Load_Flash_Image_To_Display_RAM(image->ImageSize().w(),
				      //WIDTH_PIXELS,  //X size
				      image->ImageSize().h(),
				      //HEIGHT_PIXELS, //Y size
				      image->Data()
				      //Mono_lup_1BPP
				      );    //Image
    }
    
    ePaper_Update_Partial();
    ePaper_POWEROFF();
  }
  
  void CScreenTask::AddPart(CImagePart& part) {
    m_imagePartsList.push_back(part);
    if(m_imagePartsList.size() == 1) {
      it = m_imagePartsList.begin();
    }
  }
        
  void CScreenTask::RemovePart(CImagePart* part) {
    // find part id and remove the part
  }

  void CScreenTask::RemoveLastPart() {
    m_imagePartsList.pop_back();
  }

    
  CImagePart::CImagePart(uint8_t* data, uint8_t id,
			 CPoint p,
			 CSize data_size,
			 CSize image_size)
    : m_data(data)
    , m_id(id)
    , m_point(p)
    , m_data_size(data_size)
    , m_image_size(image_size)
  {
    //Serial.println("CImagePart constructor");
  }

  CImagePart::CImagePart(const CImagePart& ip)
    : m_data(ip.Data())
    , m_point(ip.Point())
    , m_id(ip.Id())
    , m_data_size(ip.DataSize())
    , m_image_size(ip.ImageSize())
  {
    //Serial.println("CImagePart copy constructor");
  }

  CImagePart::CImagePart() {
    //Serial.println("EMPTY CImagePart CONTSTRUCTOR. THIS SHOULD NEVER HAPPEND");
  }

  CImagePart::~CImagePart() {
    //Serial.println("~CImagePart");
  }
  
  uint8_t        CImagePart::Id()   { return m_id; };

  const uint8_t* CImagePart::Data() { return m_data; };
}
