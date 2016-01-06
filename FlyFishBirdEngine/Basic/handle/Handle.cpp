//
//  Handle.cpp
//  test1
//
//  Created by weitoo on 15/12/30.
//  Copyright © 2015年 weitoo. All rights reserved.
//

#include "Handle.hpp"


namespace ffb {
    
    
    
    template <typename TAG>
    void Handle<TAG>:: Init(unsigned int index) {
        
        assert(IsNull());                   //不允许重新赋值
        assert(index <= MAX_INDEX);         //有效范围验证
        
        static unsigned int s_AutoMagic = 0;
        if (++s_AutoMagic > MAX_MAGIC)
        {
            s_AutoMagic = 1;                //0用于“空句柄”
        }
        
        m_index = index;
        m_Magic = s_AutoMagic;
    }

}
