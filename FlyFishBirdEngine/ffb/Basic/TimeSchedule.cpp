//
//  TimerSchedule.cpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/24.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#include "TimeSchedule.hpp"


namespace ffb {
    
    TimeSchedule::TimeSchedule():m_delte(0)
    {

    }
    
    void TimeSchedule::AddSchedule(NoneParameterFunction function, double delay)
    {
        m_noneParaList.push(NoneParameter {function, delay + m_delte});
    }
    
    void TimeSchedule::AddSchedule(OneParameterFunction function, void *firstParameter, double delay)
    {
        m_oneParaList.push(OneParameter {function, firstParameter, delay + m_delte});
    }
    
    void TimeSchedule::AddSchedule(TwoParameterFunction function, void * firstParameter, void * secondParameter, double delay)
    {
        m_twoParaList.push(TwoParameter {function, firstParameter, secondParameter, delay + m_delte});
    }
    
    
    void TimeSchedule::Update(double dt)
    {
        m_delte += dt;

        if (!m_noneParaList.empty()) {
           
            NoneParameter parameter = m_noneParaList.top();
            
            while (parameter.delay < m_delte) {
#if FFBDEBUG
                printf("%f\n", m_delte);
#endif
                parameter.function();
                m_noneParaList.pop();
                if (m_noneParaList.empty()) {
                    break;
                }
                parameter = m_noneParaList.top();
            }
        }
        
        if (!m_oneParaList.empty()) {
            OneParameter parameter = m_oneParaList.top();
            
            while (parameter.delay < m_delte) {
#if FFBDEBUG
                printf("%f\n", m_delte);
#endif
                parameter.function(parameter.firstParameter);
                m_noneParaList.pop();
                
                if (m_oneParaList.empty()) {
                    break;
                }
                
                parameter = m_oneParaList.top();
            }
            
        }
        if (!m_twoParaList.empty()) {
            TwoParameter parameter = m_twoParaList.top();
            
            while (parameter.delay < m_delte) {
#if FFBDEBUG
                printf("%f\n", m_delte);
#endif
                parameter.function(parameter.firstParameter, parameter.secondParameter);
                m_noneParaList.pop();
                
                if (m_twoParaList.empty()) {
                    break;
                }
                
                parameter = m_twoParaList.top();
            }
        }
    }
    
    
}