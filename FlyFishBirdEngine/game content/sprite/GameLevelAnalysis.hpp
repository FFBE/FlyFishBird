//
//  GameLevelAnalysis.hpp
//  FlyFishBirdEngine
//
//  Created by weitoo on 16/3/1.
//  Copyright © 2016年 FlyFishBird. All rights reserved.
//

#ifndef GameLevelAnalysis_hpp
#define GameLevelAnalysis_hpp

#include <stdio.h>
#include <vector>
#include <string>

typedef struct
{
    std::string         fileName;
    float               height;
    float               width;
    float               x;
    float               y;
}GameItem;


void CopyItem(GameItem formItem, GameItem &toItem);

typedef std::vector<GameItem> GameItems;

void AnalysisGameByLevel(GameItems &gameitems, int level);
GameItem AnalysisString(std::string string);



#endif /* GameLevelAnalysis_hpp */
