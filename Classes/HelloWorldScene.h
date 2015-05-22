#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    Layer* _layerBillBoard;
    Sprite3D* m_sprite;
    Vec2 m_prePosition;

    Layout* Panel_open_file;
    Button* Button_open_file;
    TextField* TextField_open_file;
    void Button_open_file_event(Ref *pSender, Widget::TouchEventType type);
    
    Layout* Panel_position;
    Button* Button_position_reset;
    Slider* Slider_position_x;
    Slider* Slider_position_y;
    Slider* Slider_position_z;
    void Slider_position_x_event(Ref *pSender, Slider::EventType type);
    void Slider_position_y_event(Ref *pSender, Slider::EventType type);
    void Slider_position_z_event(Ref *pSender, Slider::EventType type);
    void Button_position_reset_event(Ref *pSender, Widget::TouchEventType type);
    
    Layout* Panel_angle;
    Button* Button_angle_reset;
    Slider* Slider_angle_x;
    Slider* Slider_angle_y;
    Slider* Slider_angle_z;
    void Slider_angle_x_event(Ref *pSender, Slider::EventType type);
    void Slider_angle_y_event(Ref *pSender, Slider::EventType type);
    void Slider_angle_z_event(Ref *pSender, Slider::EventType type);
    void Button_angle_reset_event(Ref *pSender, Widget::TouchEventType type);
    
    Layout* Panel_animation_mode;
    ListView* ListView_animation;
    Button* Button_add_animation;
    void Button_add_animation_event(Ref *pSender, Widget::TouchEventType type);
    void Button_delete_myself_animation_event(Ref *pSender, Widget::TouchEventType type);
    void Button_play_animation_event(Ref *pSender, Widget::TouchEventType type);
    
    Text* Text_x;
    Text* Text_y;
    Text* Text_z;
    
    Text* Text_px;
    Text* Text_py;
    Text* Text_pz;
    
    
    
    Layout* Panel_armature_mode;
    ListView* ListView_armature;
    TextField* TextField_armature_name;
    void Button_add_armature_event(Ref *pSender, Widget::TouchEventType type);
    void Button_armature_ok_event(Ref *pSender, Widget::TouchEventType type);
    void Button_armature_delete_event(Ref *pSender, Widget::TouchEventType type);
    void update(float dt);

    int m_armatureIndex;
    
    float m_accAngle;
};

class BillBoardDemo : public cocos2d::Layer
{
public:
    CREATE_FUNC(BillBoardDemo);
    virtual bool init();
    virtual void update(float dt) override;
    void addNewBillBoardWithCoords(Vec3 p);
    void addNewAniBillBoardWithCoords(Vec3 p);
    void rotateCameraCallback(Ref* sender,float value);
    void onTouchesMoved(const std::vector<Touch*>& touches,Event* event);
    
    void menuCallback_orientedPoint(Ref* sender);
    void menuCallback_orientedPlane(Ref* sender);
    
    BillBoardDemo();
    virtual ~BillBoardDemo();
    
protected:
    Camera*   _camera;
    Layer*    _layerBillBoard;
    std::vector<BillBoard*> _billboards;
};

#endif // __HELLOWORLD_SCENE_H__
