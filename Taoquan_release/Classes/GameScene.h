//
//  GameScene.h
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#ifndef __TaoQuan__GameScene__
#define __TaoQuan__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "ResolvePicture.h"
#include "ShadeLayer.h"
#include "FailedShadeLayer.h"
#include "PauseLayer.h"

USING_NS_CC;

struct tagResource
{
    cocos2d::Vec2 vec2;
    int id;
};

class GameScene :public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void menuBackCallback(cocos2d::Ref* pSender);//返回按钮回调方法
    void menuPauseCallback(Ref* pSender);//暂停按钮回调方法
    void menuHelpCallback(Ref* pSender);//帮助按钮回调方法
    void menuAddQuanCallback(Ref* pSender);//增加圈按钮回调方法
    void spriteQuanMoveCallBack(); //添加圈子飞行结束以后的动作
    
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    void updateTime(float dt);
    void update(float dt);
    
    void setNextLevelPicture(EventCustom* e);//自定义监听，下一关的回调方法
    void resetGame(EventCustom* e);//自定义监听，重新开始的回调方法
    void backSelectLevel(EventCustom* e);//自定义监听，返回主界面回调方法

    std::string randomChoosePictureColor(int num);//随机选择图片颜色
    
    void enterIntoSucceedUI();
    void enterIntoFailedUI();
    
    //按两次退出
    void menuCloseCallback(Ref* pSender);
    void CloseExitSign(float dt);
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    bool _IsNeedExit;
    
    Sprite* _spriteTiao;//指针
    ProgressTimer* _powerProgress;//指针进度条
    Sprite* _ruling;//指针进度条背景
    Sprite* _noMoveSprite;
    Sprite* _spriteQuan;
    
    ProgressTimer* _dottedLineProgress2;//虚线进度条
    
    Vector<ResolvePicture*> spriteVector;//小图
    Vector<ResolvePicture*> hiddenPictureVector;//隐藏的小图
    Vector<ResolvePicture*> showPictureVector;//隐藏的小图
    Vector<Sprite*> dizuoVector;//底座
    Vector<Sprite*> dizuoTouyingVector;//底座投影
    Vector<Sprite*> waterVector;
    
    int _helpNumber;//帮助
    int _loopNumber;//环数
    char _loopNumberLabel[10];
    float x;float y;
    
    bool _isTouch;//判断是否可触摸
    bool _isHelp;
    bool _isTaoZhong;
    
    RepeatForever* repeatPG;
    
    ShadeLayer* _succeedLayer;//过关的层
    FailedShadeLayer* _failLayer;//失败层
    PauseLayer* _pauseLayer;
    
    Sprite* _wholePicture;//全图
    Sprite* _gameBG;
    
    
    RepeatForever* _repeatLineBG;
    ValueVector calculationSatrNumber(int quanNumber,int picNumber);//计算所得星星的个数
    
    float _speedT;//指针摆动速度
    float _speedP;
    float QUAN_SCA;
    
    Speed*_spriteTiaoSpeed;
    Speed* _progressTimerSpeed;//进度条速度
    ~GameScene();

    Vector<ResolvePicture*>vec2Vector;
    
    
    LabelAtlas* _labelLevel;//关卡数字
   
    LabelAtlas* _totalQuanNumber;//关卡数字
    
    void updateToOriginalState();//更新为初始化状态
    tagResource *p_sp[10];
    
private:
    LabelAtlas* labelTime;
    LabelAtlas* labelNumber;
    LabelAtlas* _labelHelpNumber;
    LabelAtlas* _labelPower;
    LabelAtlas* _labelAngle;
    
    
    Size visibleSize ;
    Vec2 origin;
    
    
    
};
#endif /* defined(__TaoQuan__GameScene__) */
