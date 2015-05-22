#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
USING_NS_CC;

using namespace cocostudio::timeline;
#define TranRate 0.03375 //0.03796875
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    m_armatureIndex = 1000;
    m_sprite = NULL;
    _layerBillBoard = Layer::create();
    this->addChild(_layerBillBoard,0);
    
    auto s = Director::getInstance()->getWinSize();
    auto camera = Camera::createPerspective(60.0, (GLfloat)s.width/s.height, 1, 4000.0);
    camera->setCameraFlag(CameraFlag::USER1);//设置相机Flag，便于相机识别节点
    _layerBillBoard->addChild(camera);
    
    camera->setPosition3D(Vec3(s.width/2, s.height/2, 150));
    camera->lookAt(Vec3(s.width/2, s.height/2,0), Vec3(0,1,0));
    
    
//    {
//        m_sprite = Sprite3D::create("bianfuyu.c3b");
//        m_sprite->setScale(0.2f);
//        m_sprite->setPosition(s/2);
//        //2，Sprite3D对象加入层
//        _layerBillBoard->addChild(m_sprite);
//        
//        
//        auto animation = Animation3D::create("bianfuyu.c3b");
//        if (animation)
//        {
//            auto animate = Animate3D::create(animation, 0 * TranRate, 37 * TranRate);
//            animate->setSpeed(1);
//            auto _swim = RepeatForever::create(animate);
//            
//            m_sprite->runAction(_swim);
//        }
//    }
 
    _layerBillBoard->setCameraMask(2);//设置mask使得对相机可见

    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    auto rootNode = CSLoader::createNode("MainScene.csb");


  
    
    //rootNode->setPositionZ(-1000);
    this->addChild(rootNode);
    
    {
        Panel_open_file = static_cast<Layout*>(rootNode->getChildByName("Panel_open_file"));
        TextField_open_file = static_cast<TextField*>(Helper::seekWidgetByName(Panel_open_file, "TextField_open_file"));
        Button_open_file = static_cast<Button*>(Helper::seekWidgetByName(Panel_open_file, "Button_open_file"));
        Button_open_file->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_open_file_event, this));
    }
    
    {
        Panel_position = static_cast<Layout*>(rootNode->getChildByName("Panel_position"));
        Slider_position_x = static_cast<Slider*>(Helper::seekWidgetByName(Panel_position, "Slider_position_x"));
        Slider_position_y = static_cast<Slider*>(Helper::seekWidgetByName(Panel_position, "Slider_position_y"));
        Slider_position_z = static_cast<Slider*>(Helper::seekWidgetByName(Panel_position, "Slider_position_z"));
        Button_position_reset = static_cast<Button*>(Helper::seekWidgetByName(Panel_position, "Button_position_reset"));
        
        Slider_position_x->addEventListener(CC_CALLBACK_2(HelloWorld::Slider_position_x_event, this));
        Slider_position_y->addEventListener(CC_CALLBACK_2(HelloWorld::Slider_position_y_event, this));
        Slider_position_z->addEventListener(CC_CALLBACK_2(HelloWorld::Slider_position_z_event, this));
        Button_position_reset->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_position_reset_event, this));
        
    }
    
    {
        Panel_angle = static_cast<Layout*>(rootNode->getChildByName("Panel_angle"));
        Slider_angle_x = static_cast<Slider*>(Helper::seekWidgetByName(Panel_angle, "Slider_angle_x"));
        Slider_angle_y = static_cast<Slider*>(Helper::seekWidgetByName(Panel_angle, "Slider_angle_y"));
        Slider_angle_z = static_cast<Slider*>(Helper::seekWidgetByName(Panel_angle, "Slider_angle_z"));
        Button_angle_reset = static_cast<Button*>(Helper::seekWidgetByName(Panel_angle, "Button_angle_reset"));
        
        Slider_angle_x->addEventListener(CC_CALLBACK_2(HelloWorld::Slider_angle_x_event, this));
        Slider_angle_y->addEventListener(CC_CALLBACK_2(HelloWorld::Slider_angle_y_event, this));
        Slider_angle_z->addEventListener(CC_CALLBACK_2(HelloWorld::Slider_angle_z_event, this));
        Button_angle_reset->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_angle_reset_event, this));
    }
    
    
    {
        Panel_animation_mode = static_cast<Layout*>(rootNode->getChildByName("Panel_animation_mode"));
        ListView_animation = static_cast<ListView*>(rootNode->getChildByName("ListView_animation"));
        Button_add_animation = static_cast<Button*>(rootNode->getChildByName("Button_add_animation"));
        Button_add_animation->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_add_animation_event, this));
        
        auto Button_delete_myself_animation = static_cast<Button*>(Helper::seekWidgetByName(Panel_animation_mode, "Button_delete_myself_animation"));
        Button_delete_myself_animation->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_delete_myself_animation_event, this));
        
        
        auto Button_play_animation = static_cast<Button*>(Helper::seekWidgetByName(Panel_animation_mode, "Button_play_animation"));
        Button_play_animation->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_play_animation_event, this));
        
    }
    
    {
        Panel_armature_mode = static_cast<Layout*>(rootNode->getChildByName("Panel_armature_mode"));
        auto Panel_armature = static_cast<Layout*>(rootNode->getChildByName("Panel_armature"));
        {
            ListView_armature = static_cast<ListView*>(Helper::seekWidgetByName(Panel_armature, "ListView_armature"));
            TextField_armature_name = static_cast<TextField*>(Helper::seekWidgetByName(Panel_armature, "TextField_armature_name"));
            
            auto Button_add_armature = static_cast<Button*>(Helper::seekWidgetByName(Panel_armature, "Button_add_armature"));
            Button_add_armature->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_add_armature_event, this));
        }
        
    }
    {
        Text_x = static_cast<Text*>(rootNode->getChildByName("Text_x"));
        Text_y = static_cast<Text*>(rootNode->getChildByName("Text_y"));
        Text_z = static_cast<Text*>(rootNode->getChildByName("Text_z"));
        
        Text_px = static_cast<Text*>(rootNode->getChildByName("Text_px"));
        Text_py = static_cast<Text*>(rootNode->getChildByName("Text_py"));
        Text_pz = static_cast<Text*>(rootNode->getChildByName("Text_pz"));
    }

    this->scheduleUpdate();
    
    return true;
}

void createFromAngle( Vec3 angle, Quaternion* dst)
{
    GP_ASSERT(dst);
    {
        float halfAngle = angle.x * 0.5f;
        float sinHalfAngle = sinf(halfAngle);
        
        dst->x = sinHalfAngle;
        dst->w = cosf(halfAngle);
    }
    {
        float halfAngle = angle.y * 0.5f;
        float sinHalfAngle = sinf(halfAngle);
        
        dst->y = sinHalfAngle;
        dst->w = cosf(halfAngle);
    }
    {
        float halfAngle = angle.z * 0.5f;
        float sinHalfAngle = sinf(halfAngle);
        
        dst->z = sinHalfAngle;
        dst->w = cosf(halfAngle);
    }
    
}
void HelloWorld::update(float dt)
{
    if (m_sprite) {
        auto _r = m_sprite->getRotation3D();
        auto _p = m_sprite->getPosition3D();
        char ch[20];
        sprintf(ch, "angle_x:%d", int(_r.x));
        Text_x->setString(ch);
        
        sprintf(ch, "angle_y:%d", int(_r.y));
        Text_y->setString(ch);
        
        sprintf(ch, "angle_z:%d", int(_r.z));
        Text_z->setString(ch);
        
        sprintf(ch, "position_x:%d", int(_p.x));
        Text_px->setString(ch);
        
        sprintf(ch, "position_y:%d", int(_p.y));
        Text_py->setString(ch);
        
        sprintf(ch, "position_z:%d", int(_p.z));
        Text_pz->setString(ch);
    }
    
    
    
    
   
}
void HelloWorld::Button_add_animation_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        auto _clone = Panel_animation_mode->clone();
        

        ListView_animation->pushBackCustomItem(_clone);
    }
}
void HelloWorld::Button_delete_myself_animation_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        auto _button = (Button*)pSender;
        auto _panel = (Layout*)_button->getParent();
        ListView_animation->cocos2d::ui::ScrollView::removeChild(_panel);
    }
}
void HelloWorld::Button_play_animation_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        auto _button = (Button*)pSender;
        auto _panel = (Layout*)_button->getParent();
        
        auto TextField_start_time = static_cast<TextField*>(Helper::seekWidgetByName(_panel, "TextField_start_time"));
        float _startTime =std::atof(TextField_start_time->getString().c_str());
        
        auto TextField_end_time = static_cast<TextField*>(Helper::seekWidgetByName(_panel, "TextField_end_time"));
        float _endTime =std::atof(TextField_end_time->getString().c_str());
        
        auto TextField_action_speed = static_cast<TextField*>(Helper::seekWidgetByName(_panel, "TextField_action_speed"));
        float _actionSpeed=std::atof(TextField_action_speed->getString().c_str());
        
        m_sprite->stopAllActions();
        std::string fileName = TextField_open_file->getString();
        auto animation = Animation3D::create(fileName+".c3b");
        if (animation)
        {
            auto animate = Animate3D::create(animation, _startTime * TranRate, _endTime * TranRate);
            animate->setSpeed(_actionSpeed);
            auto _swim = RepeatForever::create(animate);
            
            m_sprite->runAction(_swim);
        }
    }
}
void HelloWorld::Button_open_file_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        std::string fileName = TextField_open_file->getString();
        if (fileName != "")
        {
            if (m_sprite)
            {
                m_sprite->removeFromParentAndCleanup(true);
            }
            
            m_sprite = Sprite3D::create(fileName+".c3b");
            if (m_sprite)
            {
                m_sprite->setScale(1);
                auto s = Director::getInstance()->getWinSize();
                m_sprite->setPosition(s/2);
                _layerBillBoard->addChild(m_sprite);
                
                
            }
            
        }
    }
}
void HelloWorld::Button_position_reset_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        auto s = Director::getInstance()->getWinSize();
        m_sprite->setPosition3D(Vec3(s.width/2,s.height/2,0));
    }
}
void HelloWorld::Button_angle_reset_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        m_sprite->setRotation3D(Vec3::ZERO);
    }
}
void HelloWorld::Slider_position_x_event(Ref *pSender, Slider::EventType type)
{
    if( Slider::EventType::ON_PERCENTAGE_CHANGED == type)
    {
        Slider* _slider = (Slider*) pSender;
        auto s = Director::getInstance()->getWinSize();
        m_sprite->setPositionX(s.width * _slider->getPercent() / 100.0);
    }
}
void HelloWorld::Slider_position_y_event(Ref *pSender, Slider::EventType type)
{
    if( Slider::EventType::ON_PERCENTAGE_CHANGED == type)
    {
        Slider* _slider = (Slider*) pSender;
        auto s = Director::getInstance()->getWinSize();
        m_sprite->setPositionY(s.height * _slider->getPercent() / 100.0);
    }
}
void HelloWorld::Slider_position_z_event(Ref *pSender, Slider::EventType type)
{
    if( Slider::EventType::ON_PERCENTAGE_CHANGED == type)
    {
        Slider* _slider = (Slider*) pSender;
        m_sprite->setPositionZ(1000 * _slider->getPercent() / 100.0 - 500);
    }
}

void HelloWorld::Slider_angle_x_event(Ref *pSender, Slider::EventType type)
{
    if( Slider::EventType::ON_PERCENTAGE_CHANGED == type)
    {
        Slider* _slider = (Slider*) pSender;
        auto _pre = m_sprite->getRotation3D();
        m_sprite->setRotation3D(Vec3(360 * _slider->getPercent() / 100.0, _pre.y, _pre.z));
    }
}
void HelloWorld::Slider_angle_y_event(Ref *pSender, Slider::EventType type)
{
    if( Slider::EventType::ON_PERCENTAGE_CHANGED == type)
    {
        Slider* _slider = (Slider*) pSender;
        auto _pre = m_sprite->getRotation3D();
        m_sprite->setRotation3D(Vec3(_pre.x, 360 * _slider->getPercent() / 100.0, _pre.z));
    }
}
void HelloWorld::Slider_angle_z_event(Ref *pSender, Slider::EventType type)
{
    if( Slider::EventType::ON_PERCENTAGE_CHANGED == type)
    {
        Slider* _slider = (Slider*) pSender;
        auto _pre = m_sprite->getRotation3D();
        m_sprite->setRotation3D(Vec3(_pre.x, _pre.y, 360 * _slider->getPercent() / 100.0));
    }
}
















bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    m_prePosition = touch->getLocation();
    return true;
}
void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    m_sprite->setPosition(Vec2(touch->getLocation()));
//    m_sprite->setRotation3D(Vec3
//                            (
//                             (m_prePosition.y-touch->getLocation().y),
//                             (-m_prePosition.x+touch->getLocation().x),
//                             m_sprite->getRotation3D().z));
//    
//    m_sprite->setPosition3D(Vec3(m_sprite->getPosition3D().x, m_sprite->getPosition3D().y, m_prePosition.y-touch->getLocation().y));
    //m_prePosition = touch->getLocation();
}
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    
}
void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}
void HelloWorld::Button_add_armature_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        std::string fileName = TextField_armature_name->getString();
        if (fileName != "")
        {
            auto _clone = Panel_armature_mode->clone();
            _clone->setTag(m_armatureIndex);
            
            auto Text_armature_name = static_cast<Text*>(Helper::seekWidgetByName(_clone, "Text_armature_name"));
            auto Button_armature_ok = static_cast<Button*>(Helper::seekWidgetByName(_clone, "Button_armature_ok"));
            Button_armature_ok->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_armature_ok_event, this));
            auto Button_armature_delete = static_cast<Button*>(Helper::seekWidgetByName(_clone, "Button_armature_delete"));
            Button_armature_delete->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Button_armature_delete_event, this));
            
            Text_armature_name->setString(fileName);
            ListView_armature->pushBackCustomItem(_clone);
            

            
            //std::string fileName2 = "yun";
            cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(fileName+".ExportJson");
            cocostudio::CCArmature* _armature = cocostudio::CCArmature::create(fileName);
            _armature->getAnimation()->playWithIndex(0);
            BillBoard* _billBoard = BillBoard::create();
            _billBoard->addChild(_armature);
            _billBoard->setPosition3D(Vec3::ZERO);
            
//            billboard->setMode(BillBoard::Mode::VIEW_PLANE_ORIENTED);
            _billBoard->setTag(m_armatureIndex);
            m_sprite->addChild(_billBoard);
            
            
            m_armatureIndex++;
            
        }
    }
}

void HelloWorld::Button_armature_ok_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        auto _button = (Button*)pSender;
        auto _parent = (Layout*)_button->getParent();
        auto Text_armature_name = static_cast<Text*>(Helper::seekWidgetByName(_parent, "Text_armature_name"))->getString();
        auto TextField_armature_x = static_cast<TextField*>(Helper::seekWidgetByName(_parent, "TextField_armature_x"))->getString();
        auto TextField_armature_y = static_cast<TextField*>(Helper::seekWidgetByName(_parent, "TextField_armature_y"))->getString();
        auto TextField_armature_z = static_cast<TextField*>(Helper::seekWidgetByName(_parent, "TextField_armature_z"))->getString();
        auto TextField_armature_scale =  static_cast<TextField*>(Helper::seekWidgetByName(_parent, "TextField_armature_scale"))->getString();
        
        auto _billBoard = (BillBoard*)m_sprite->getChildByTag(_parent->getTag());
        _billBoard->setPosition3D(Vec3(std::atof(TextField_armature_x.c_str()) ,std::atof(TextField_armature_y.c_str()),std::atof(TextField_armature_z.c_str())));
        _billBoard->setScale(std::atof(TextField_armature_scale.c_str()));
    }
}
void HelloWorld::Button_armature_delete_event(Ref *pSender, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED == type)
    {
        auto _button = (Button*)pSender;
        auto _panel = (Layout*)_button->getParent();
        ListView_armature->cocos2d::ui::ScrollView::removeChild(_panel);
        
        m_sprite->removeChildByTag(_panel->getTag());
    }
}
///////////
BillBoardDemo::BillBoardDemo()
:_camera(nullptr)
{
    
}

bool BillBoardDemo::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!Layer::init());
        
        //注册事件监听
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesMoved = CC_CALLBACK_2(BillBoardDemo::onTouchesMoved, this);//事件回调
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
        //添加层
        auto layer3D = Layer::create();
        addChild(layer3D,0);
        _layerBillBoard = layer3D;
        
        auto winSize = Director::getInstance()->getWinSize();
        //创建摄像机
        if(_camera == nullptr)
        {
            //参数1:透视相机的视野。参数2:相机的长宽比。参数3:近点平面距离。参数4:远点平面距离
            _camera = Camera::createPerspective(60, (GLfloat)winSize.width / winSize.height, 1, 500);
            _camera->setCameraFlag(CameraFlag::USER1);//设置相机Flag，便于相机识别节点
            _layerBillBoard->addChild(_camera);//相机加入层
        }
        
//        std::string imgs[3] = {"Icon.png","r2.png"};
//        for(unsigned int i = 0; i < 4; i++)
//        {
//            Layer* layer = Layer::create();
//            //随机创建BillBoard对象
//            auto billboard = BillBoard::create(imgs[(unsigned int)(CCRANDOM_0_1()*1+0.5)]);
//            billboard->setScale(0.5);//设置缩放
//            //CCRANDOM_MINUS1_1返回一个-1到1的float值
//            billboard->setPosition3D(Vec3(0.0f,0.0f,CCRANDOM_MINUS1_1()*150.0f));//设置3D坐标
//            //ALPHA_NON_PREMULTIPLIED混合方式 {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}
//            //源因子使用源颜色的透明度，目标因子使用减去源颜色的透明度
//            billboard->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);//设置颜色混合
//            billboard->setOpacity(CCRANDOM_0_1()*128+128);//设置可见性
//            _billboards.push_back(billboard);
//            layer->addChild(billboard);
//            //1，层对象加入层
//            _layerBillBoard->addChild(layer);//加入层
//            layer->runAction(RepeatForever::create(RotateBy::create(CCRANDOM_0_1(),Vec3(0.0f,45.0f,0.0f))));//层执行翻转动作
//        }
        {
            auto billboard = BillBoard::create("Icon.png");
            billboard->setScale(0.2f);
            billboard->setPosition3D(Vec3(0.0f,30.0f,0.0f));
//
//            auto billboard2 = BillBoard::create("r2.png");
//            billboard2->setPosition3D(Vec3(0.0f,0.0f,100.0f));
//            billboard->addChild(billboard2);
//            _billboards.push_back(billboard);
//            _billboards.push_back(billboard2);
            
            auto sprite3D = Sprite3D::create("orc.c3t");
            sprite3D->setScale(2.0f);
            sprite3D->addChild(billboard);
            sprite3D->runAction(RepeatForever::create(RotateBy::create(10.0f, Vec3(0.0f,360.0f,0.0f))));
            //2，Sprite3D对象加入层
            _layerBillBoard->addChild(sprite3D);
        }
        
//        //添加新的billboard
//        addNewBillBoardWithCoords(Vec3(20,5,0));
//        addNewBillBoardWithCoords(Vec3(60,5,0));
//        addNewBillBoardWithCoords(Vec3(100,5,0));
//        addNewBillBoardWithCoords(Vec3(140,5,0));
//        addNewBillBoardWithCoords(Vec3(180,5,0));
//        addNewAniBillBoardWithCoords(Vec3(-20,0,0));
//        addNewAniBillBoardWithCoords(Vec3(-60,0,0));
//        addNewAniBillBoardWithCoords(Vec3(-100,0,0));
//        addNewAniBillBoardWithCoords(Vec3(-140,0,0));
//        addNewAniBillBoardWithCoords(Vec3(-180,0,0));
        _camera->setPosition3D(Vec3(0,100,230));//设置相机的3D位置
        _camera->lookAt(Vec3(0,0,0), Vec3(0,1,0));//设置相机的，参数1:目标的中心位置，参数2:向上的向量
        
        
        //添加菜单
        TTFConfig ttfConfig("fonts/arial.ttf",30);
        auto label1 = Label::createWithTTF(ttfConfig, "rotate+");
        auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(BillBoardDemo::rotateCameraCallback, this,10));
        auto label2 = Label::createWithTTF(ttfConfig, "rotate-");
        auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(BillBoardDemo::rotateCameraCallback, this, -10));
        auto menu = Menu::create(menuItem1,menuItem2,nullptr);
        menu->setPosition(Vec2::ZERO);
        menuItem1->setPosition(Vec2(winSize.width - 80,VisibleRect::top().y - 160));
        menuItem2->setPosition(Vec2(winSize.width - 80,VisibleRect::top().y - 190));
        addChild(menu,0);
        _layerBillBoard->setCameraMask(2);//设置mask使得对相机可见
        
        //设置billboard观察模式
//        label1 = Label::createWithTTF(ttfConfig, "Point Oriented");
//        menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(BillBoardDemo::menuCallback_orientedPoint, this));
//        label2 = Label::createWithTTF(ttfConfig, "Plane Oriented");
//        menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(BillBoardDemo::menuCallback_orientedPlane, this));
//        menuItem1->setPosition(Vec2(winSize.width -80,VisibleRect::top().y - 100));
//        menuItem2->setPosition(Vec2(winSize.width -80,VisibleRect::top().y - 130));
//        
//        menu = Menu::create(menuItem1,menuItem2,nullptr);
//        menu->setPosition(Vec2::ZERO);
//        this->addChild(menu,10);
//        menuCallback_orientedPoint(nullptr);
        
        
        bRet = true;
    }while(0);
    return bRet;
}

void BillBoardDemo::menuCallback_orientedPoint(cocos2d::Ref *sender)
{
    for(auto& billboard : _billboards)
    {
        billboard->setMode(BillBoard::Mode::VIEW_POINT_ORIENTED);
    }
}
void BillBoardDemo::menuCallback_orientedPlane(cocos2d::Ref *sender)
{
    for(auto& billboard : _billboards)
    {
        billboard->setMode(BillBoard::Mode::VIEW_PLANE_ORIENTED);
    }
}

BillBoardDemo::~BillBoardDemo()
{
    if(_camera)
    {
        _camera = nullptr;
    }
}
//创建新的BillBoard
void BillBoardDemo::addNewBillBoardWithCoords(Vec3 p)
{
    std::string imgs[3] = {"Icon.png","r2.png"};
    for(unsigned int i = 0; i < 10; i++)
    {
        //随机图片
        auto billboard = BillBoard::create(imgs[(unsigned int)(CCRANDOM_0_1()*1+0.5)]);
        billboard->setScale(0.5f);
        billboard->setPosition3D(Vec3(p.x,p.y,-150.0f+30*i));//Z轴值越来越大
        billboard->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);//设置颜色混合方式
        billboard->setOpacity(CCRANDOM_0_1()*128+128);
        _layerBillBoard->addChild(billboard);//3，加入新的billboard对象
        _billboards.push_back(billboard);
    }
}
//创建新的BillBoard
void BillBoardDemo::addNewAniBillBoardWithCoords(cocos2d::Vec3 p)
{
    for(unsigned i = 0; i < 10; i++)
    {
        auto billboardAni = BillBoard::create("grossini.png");
        billboardAni->setScale(0.5);
        billboardAni->setPosition3D(Vec3(p.x,p.y,-150.0f+30*i));
        _layerBillBoard->addChild(billboardAni);//4，加入新的billboard对象
        //使用帧动画
        auto animation = Animation::create();
        for(int i = 1; i < 15; i++)
        {
            char szName1[100] = {0};
            sprintf(szName1, "grossini_dance_%02d.png",i);
            animation->addSpriteFrameWithFile(szName1);
        }
        animation->setDelayPerUnit(2.8f/14.0f);//设置一帧的时间
        animation->setRestoreOriginalFrame(true);//重复播放
        
        auto action = Animate::create(animation);
        billboardAni->runAction(RepeatForever::create(action));
        billboardAni->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);//设置颜色混合方式
        billboardAni->setOpacity(CCRANDOM_0_1()*128+128);
        _billboards.push_back(billboardAni);
    }
}

void BillBoardDemo::update(float dt)
{
    
}
//触摸事件，改变摄像机的坐标
void BillBoardDemo::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *event)
{
    if(touches.size() == 1)
    {
        auto touch = touches[0];
        auto location = touch->getLocation();
        auto PreviousLocation = touch->getPreviousLocation();
        Vec2 newPos = PreviousLocation - location;
        
        Vec3 cameraDir;
        Vec3 cameraRightDir;
        _camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
        cameraDir.normalize();
        cameraDir.y = 0;
        _camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
        cameraRightDir.normalize();
        cameraRightDir.y = 0;
        Vec3 cameraPos = _camera->getPosition3D();
        cameraPos+= cameraDir*newPos.y*0.5;
        cameraPos+= cameraRightDir*newPos.x*0.5;
        _camera->setPosition3D(cameraPos);
    }
}
//翻转摄像机
void BillBoardDemo::rotateCameraCallback(cocos2d::Ref *sender, float value)
{
    Vec3 rotation3D = _camera->getRotation3D();
    rotation3D.y += value;
    _camera->setRotation3D(rotation3D);
}











