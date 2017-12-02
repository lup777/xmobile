// CTaskStack.h
#ifndef __CTASKSTACK_H__
#define __CTASKSTACK_H__

#include <stdint.h>
#include "CList.h"

#include "ePaper_CFAP200200A0154.h"
#include "lup_200x200_24.h"

namespace TaskStack
{
    class ITask;
    class CImagePart;
    class CStack;
    
    enum task_type
    {
        screen_task,
        gsm_task,
        error_task
    };
    
    class CStack
    {
    public:
        CStack();
        
        ITask* Next();
        
        void Add(ITask* new_task);
        
        void Remove(ITask* task_to_del);

        void Do(void);
        
    private:
        list<ITask*> m_task_list;
        list<ITask*>::iterator it;
    };

    class ITask
    {
    public:
        virtual task_type Type() = 0;
        virtual uint8_t Id() = 0;
        virtual void Do() = 0; 
        
    private:
        task_type type;
        uint8_t id;
    };

    class CGSMTask : public ITask
    {
    public:
        virtual task_type Type();
        virtual uint8_t Id();
        virtual void Do();
        
    private:
        uint8_t m_id;
    };
    
    class CScreenTask : public ITask
    {
    public:
        CScreenTask(uint8_t id);

        virtual task_type Type();
        virtual uint8_t Id();
        virtual void Do();
        
        void AddPart(CImagePart& part);
        
        void RemovePart(CImagePart* part);
        void RemoveLastPart();
    private:
        uint8_t m_id;
        CScreenTask() {};
        list<CImagePart> m_imagePartsList; // list of image fragments for partial update
        list<CImagePart>::iterator it;
    };

    class CPoint {
    public:
    CPoint(int x, int y)
      : x_((uint8_t)x)
	, y_((uint8_t)y) {};
	  
    CPoint(uint8_t x, uint8_t y)
      : x_(x)
	, y_(y) {};
      
    CPoint(const CPoint& p)
      : x_(p.x())
	, y_(p.y()) {};

      CPoint() {
	Serial.println("EMPTY CPoint CONTSTRUCTOR. THIS SHOULD NEVER HAPPEND");
      };

      uint8_t x() { return x_; };
      uint8_t y() { return y_; };

    private:
      uint8_t x_;
      uint8_t y_;
    };
    
    class CSize {
    public:

    CSize(int w, int h )
      : w_((uint8_t)w)
	, h_((uint8_t)h) {};
      
    CSize(uint8_t w, uint8_t h)
      : w_(w)
	, h_(h) {};
      
    CSize(const CSize& s)
      : w_(s.w())
	, h_(s.h()) {};

      CSize() {
	Serial.println("EMPTY CSize CONTSTRUCTOR. THIS SHOULD NEVER HAPPEND");
      }
      
      uint8_t w() { return w_; };
      uint8_t h() { return h_; };
      
    private:
      uint8_t w_;
      uint8_t h_;
    };
    
    class CImagePart {
    public:
      CImagePart(uint8_t* data, uint8_t id,
		 CPoint p,
		 CSize data_size,
		 CSize image_size);
      CImagePart(const CImagePart& ip);
      CImagePart();
        uint8_t        Id();
        const uint8_t* Data();
	const CPoint& Point() { return m_point; };
	CSize DataSize() { return m_data_size; };
	const CSize ImageSize() { return m_image_size; };
	void setPosition(uint8_t x, uint8_t y) { m_point = CPoint(x, y); };
	~CImagePart();
    private:
        uint8_t m_id;
        const uint8_t* m_data;
	CPoint m_point;
	CSize m_data_size; // size of data matrix (bytes, pixels)
	CSize m_image_size; // size of image (pixels, pixels)
    };
}

#endif
