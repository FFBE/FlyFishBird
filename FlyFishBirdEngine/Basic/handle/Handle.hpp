//
//  Handle.hpp
//  test1
//
//  Created by weitoo on 15/12/30.
//  Copyright © 2015年 weitoo. All rights reserved.
//

#ifndef Handle_hpp
#define Handle_hpp

#include <stdio.h>
#include <cassert>

namespace ffb {
    template <typename TAG>
    class Handle
    {
        
        enum
        {
            //使用位域（bit fields）的大小
            MAX_BITS_INDEX = 16,
            MAX_BITS_MAGIC = 16,
            
            //解引用断言中需要比较的大小
            MAX_INDEX = ( 1 << MAX_BITS_INDEX) -1,
            MAX_MAGIC = ( 1 << MAX_BITS_MAGIC) -1,
        };
        
        union
        {
            struct
            {
                unsigned m_index : MAX_BITS_INDEX; //资源数组的索引
                unsigned m_Magic : MAX_BITS_MAGIC; //需要检查的魔术数
            };
            unsigned int m_Handle;
        };
        
    public:
        
        //生命期
        
        Handle(void):m_Handle(0){};
        
        void Init(unsigned int index);
        
        //查询
        unsigned int GetIndex (void) const {return m_index;}
        unsigned int GetMagic (void) const {return m_Magic;}
        unsigned int GetHandle(void) const {return m_Handle;}
        bool IsNull()   const {return !m_Handle;}
        
        operator unsigned int (void)const {return m_Handle;}
    };
    
    
    template <typename TAG>
    inline bool operator != (Handle<TAG> l, Handle<TAG> r)
    {  return l.GetHandle() != r.GetHandle(); }
    
    
    template <typename TAG>
    inline bool operator == (Handle<TAG> l, Handle<TAG> r)
    { return l.GetHandle() == r.GetHandle(); }
}




#endif /* Handle_hpp */
