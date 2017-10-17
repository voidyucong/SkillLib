//
//  CItem.hpp
//  SkillLib
//
//  Created by yucong on 2017/10/16.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CItem_hpp
#define CItem_hpp

#include <iostream>
#include "CAbility.hpp"
#include "CItemData.hpp"


class CItem : public CAbility {
public:
    CItem();
    virtual ~CItem();
    
    void SetItemData(CItemData* data) { itemData_ = data; }
    CItemData* GetItemData() { return itemData_; }
private:
    CItemData* itemData_;
};

#endif /* CItem_hpp */
