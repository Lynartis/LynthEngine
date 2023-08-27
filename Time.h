#ifndef TIME_CLASS_H
#define TIME_CLASS_H


#include<GLFW/glfw3.h>

class Time

{
	public:
	
		

		Time(float time = 0.0f)
				: m_Time(time)
	{

	}
		float RunTime()
		{
			m_Time = (float)glfwGetTime(); 
			return m_Time;
		}
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
		float DeltaTime()  
		{
			float time = (float)glfwGetTime();			
			float delta = time - m_LastFrameTime; 
			 m_LastFrameTime = time;
			return delta;

		}
	private: 
		float m_Time;
		float m_LastFrameTime ;


};




#endif