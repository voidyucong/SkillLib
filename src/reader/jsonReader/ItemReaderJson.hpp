//
//  ItemReaderJson.hpp
//  SkillLib
//
//  Created by yucong on 2017/10/17.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef ItemReaderJson_hpp
#define ItemReaderJson_hpp

#include <iostream>
#include "ReaderJsonUtil.h"

class CItem;

class ItemReaderJson {
public:
    ItemReaderJson();
    ~ItemReaderJson();
    static ItemReaderJson* getInstance();
    
    CItem* ItemFromFile(std::string fileName);
    CItem* CreateItem(const rapidjson::Value& json);
    void ParseItem(const rapidjson::Value& json, CItem* item);
};

#endif /* ItemReaderJson_hpp */
