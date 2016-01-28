//
//  TimerSchedule.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/1/24.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef TimeSchedule_hpp
#define TimeSchedule_hpp

#include <stdio.h>
#include <functional>
#include <queue>
#include "Singleton.hpp"
#include <vector>

namespace ffb {
    
    
#define function0st(target, function)       std::bind(&function, target)
#define function1st(target, function)       std::bind(&function, target)
#define function2st(target, function)       std::bind(&function, target)

    
    typedef std::function<void(void * , void *)> TwoParameterFunction;
    typedef std::function<void(void *)> OneParameterFunction;
    typedef std::function<void()> NoneParameterFunction;
    
    struct NoneParameter
    {
        NoneParameterFunction function;
        double delay;
    };
    
    
    
    struct OneParameter
    {
        OneParameterFunction function;
        void * firstParameter;
        double delay;
    };
    
    struct TwoParameter
    {
        TwoParameterFunction function;
        void * firstParameter;
        void * secondParameter;
        double delay;
    };
    
    
    inline bool operator < (const NoneParameter &prorameter1, const NoneParameter &prorameter2)
    {
        return prorameter1.delay > prorameter2.delay;
    }
    
    inline bool operator < (const OneParameter &prorameter1, const OneParameter &prorameter2)
    {
        return prorameter1.delay > prorameter2.delay;
    }
    
    inline bool operator < (const TwoParameter &prorameter1, const TwoParameter &prorameter2)
    {
        return prorameter1.delay > prorameter2.delay;
    }
    
    
    class TimeSchedule:public Singleton<TimeSchedule> {
        

    public:
        
        TimeSchedule();
        ~TimeSchedule() {};
        
        void AddSchedule(NoneParameterFunction function, double delay);
        void AddSchedule(OneParameterFunction function, void * firstParameter, double delay);
        void AddSchedule(TwoParameterFunction function, void * firstParameter, void * secondParameter, double delay);

        
        void Update(double dt);
        
        
    private:
        
        double m_delte;
        
        
        typedef std::priority_queue<NoneParameter> NoneParameterQueue;
        typedef std::priority_queue<OneParameter> OneParameterQueue;
        typedef std::priority_queue<TwoParameter> TwoParameterQueue;
        
        NoneParameterQueue m_noneParaList;
        OneParameterQueue m_oneParaList;
        TwoParameterQueue m_twoParaList;
        
    };

}



#endif /* TimerSchedule_hpp */
