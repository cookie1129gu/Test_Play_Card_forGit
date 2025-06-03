#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const std::string kLevelConfigPath = "res/level_01.json";

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    if (!Scene::init()) return false;

    // 1. ��ʼ������
    setupGameAreas();
    setupUI();

    // 2. ��ʼ��ģ�ͺͿ�����
    _model = new GameModel();
    auto levelConfig = LevelConfigLoader::loadConfig(kLevelConfigPath);
    _model->loadLevel(levelConfig);
    _controller = new GameController(_model);

    // 3. ����������ͼ
    initializeCards();

    // 4. �����¼�����
    setupCardEventListeners();

    return true;
}

void HelloWorld::setupUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto undoLabel = Label::createWithTTF("back", "fonts/Marker Felt.ttf", 90);

    _undoButton = MenuItemLabel::create(undoLabel, CC_CALLBACK_1(HelloWorld::onUndoClicked, this));
#if 1
    _undoButton->setPosition(Vec2(
        origin.x + visibleSize.width - 100,
        origin.y + visibleSize.height - 1700));
#endif
    auto menu = Menu::create(_undoButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void HelloWorld::setupGameAreas() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����������
    auto playfield = LayerColor::create(Color4B(170, 121, 66, 255),
        1080, 1500);
    playfield->setPosition(origin.x, origin.y + visibleSize.height - 1500);
    addChild(playfield, 0);

    // ����������
    auto stackArea = LayerColor::create(Color4B(148, 33, 146, 255),
        1080, 580);
    stackArea->setPosition(origin);
    addChild(stackArea, 0);
}

void HelloWorld::initializeCards() {
    // ��������������
    for (size_t i = 0; i < _controller->getModel()->getPlayfieldCardCount(); ++i) {
        auto cardView = CardView::create(&_controller->getModel()->getPlayfieldCard(i), nullptr);
        cardView->setPosition(_controller->getModel()->getPlayfieldCard(i).getPosition());
        _playfieldCards.push_back(cardView);
        addChild(cardView, 1);
    }

    // ��������������
    for (size_t i = 0; i < _controller->getModel()->getStackCardCount(); ++i) {
        auto cardView = CardView::create(&_controller->getModel()->getStackCards()[i], nullptr);
        cardView->setPosition(_controller->getModel()->getStackCards()[i].getPosition());
        _stackCards.push_back(cardView);
        addChild(cardView, 1);
    }
}

void HelloWorld::setupCardEventListeners() {
    // �����������¼� - ʹ�õ�����
    for (auto it = _playfieldCards.begin(); it != _playfieldCards.end(); ++it) {
        auto cardView = *it;

        setupPlayfieldCardEventListeners(cardView);
    }
    
    // �����������¼�
    for (auto it = _stackCards.begin(); it != _stackCards.end(); ++it) {
        log("AAA: _stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());
        auto cardView = *it;

        setupStackCardEventListeners(cardView);
    }
    
}

void HelloWorld::setupPlayfieldCardEventListeners(CardView* cardView) 
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<CardView*>(event->getCurrentTarget());
        return target->getBoundingBox().containsPoint(touch->getLocation());
        };

    listener->onTouchEnded = [this, cardView](Touch* touch, Event* event) {
        // ��̬���ҿ����ڵ�ǰ�����е�����
        auto it = std::find(_playfieldCards.begin(), _playfieldCards.end(), cardView);
        if (it == _playfieldCards.end()) return; // �����ѱ��Ƴ�
        size_t index = std::distance(_playfieldCards.begin(), it);

        if (_stackCards.empty()) return;
        auto beforeTopCard = _stackCards.back();
        auto targetPos = beforeTopCard->getPosition();
        
        bool isNext = _controller->handlePlayfieldCardClick(static_cast<int>(index));
        
        
        
        if (isNext) {

            test();

            // �����¿��Ʋ�ִ�ж���
            auto newCardView = CardView::create(_controller->getModel()->getTopStackCard(), nullptr);
            newCardView->setPosition(cardView->getPosition());
            newCardView->setVisible(false);
            addChild(newCardView, 1);

            newCardView->setVisible(true);
            newCardView->runAction(Sequence::create(
                MoveTo::create(0.3f, targetPos),
                CallFunc::create([this, cardView, newCardView, index]() {
                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    // ���ҵ�ǰ�����������е�λ��
                    auto it = std::find(_playfieldCards.begin(), _playfieldCards.end(), cardView);
                    if (it != _playfieldCards.end()) {
                        _eventDispatcher->removeEventListenersForTarget(cardView);
                        removeChild(cardView);
                        _playfieldCards.erase(it);
                    }

                    // ���¶�����
                    if (!_stackCards.empty()) {
                        _stackCards.pop_back();
                    }
                    _stackCards.push_back(newCardView);

                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    CCLOG("Card moved successfully. Stack now has %zu cards", _stackCards.size());
                    }),
                nullptr
            ));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardView);
}

void HelloWorld::setupStackCardEventListeners(CardView* cardView)
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<CardView*>(event->getCurrentTarget());
        return target->getBoundingBox().containsPoint(touch->getLocation());
        };

    listener->onTouchEnded = [this, cardView](Touch* touch, Event* event) {
        // ��̬���ҿ����ڵ�ǰ�����е�����
        auto it = std::find(_stackCards.begin(), _stackCards.end(), cardView);
        if (it == _stackCards.end()) return; // �����ѱ��Ƴ�
        size_t index = std::distance(_stackCards.begin(), it);

        if (_stackCards.empty()) return;
        auto beforeTopCard = _stackCards.back();
        auto targetPos = beforeTopCard->getPosition();

        if (_controller->handleStackCardClick(index)) {
            auto newCardView = CardView::create(_controller->getModel()->getTopStackCard(), nullptr);
            newCardView->setPosition(cardView->getPosition());
            newCardView->setVisible(false);
            addChild(newCardView, 1);

            newCardView->setVisible(true);


            newCardView->runAction(Sequence::create(
                MoveTo::create(0.3f, targetPos),
                CallFunc::create([this, cardView, newCardView, index]() {
                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    // ���¶�����
                    if (!_stackCards.empty()) {
                        _eventDispatcher->removeEventListenersForTarget(cardView);
                        removeChild(cardView); 
                        _stackCards.pop_back(); // ȥ���ɶ���

                        _stackCards.erase(_stackCards.begin() + index); // ȥ��ԭ�����¶���
         
                    }
                    _stackCards.push_back(newCardView); // �����¶���

                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    log("Stacking area card %zu promoted to the top", index);
                    }),
                nullptr
            ));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardView);
}

void HelloWorld::onUndoClicked(cocos2d::Ref* sender)
{
    log("Undo Click!");
    
    if (!_controller->emptyUndo()) {
        // ִ����ͼ����
        animateUndo();
    }
    else {
        log("Undo is null");
    }
}

void HelloWorld::animateUndo() {
    // ��ȡ���һ������
    const UndoAction& action = *_controller->getUndoManager()->getLastAction();


    // ���ݲ�������ִ�в�ͬ�Ķ���
    switch (action.type) {
        case UndoAction::MOVE_TO_STACK: {
            log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

            // �Ӷ������ƻ�������
            auto card1 = _stackCards.back();
            Vec2 pos = card1->getPosition();

            card1->runAction(MoveTo::create(0.3f, action.originalPosition)); // λ�Ƶ�ԭ����λ��

            _playfieldCards.push_back(card1);
            _stackCards.pop_back();

            // ��ӱ����ǵ�ԭ����
            auto newCardView = CardView::create(&(action.cardState), nullptr);
            newCardView->setPosition(pos);
            _stackCards.push_back(newCardView);

            // ���ô�������
            setupPlayfieldCardEventListeners(newCardView);

            addChild(newCardView, 1);
            log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

            break;
        }
        case UndoAction::PROMOTE_TO_TOP: {
            auto card1 = _stackCards.back();

            Vec2 pos = card1->getPosition();

            card1->runAction(MoveTo::create(0.3f, action.originalPosition)); // λ�Ƶ�ԭ����λ��

            // ��ӱ����ǵ�ԭ����
            auto newCardView = CardView::create(&(action.cardState), nullptr);
            newCardView->setPosition(pos);
            _stackCards.push_back(newCardView);

            // ���ô�������
            setupStackCardEventListeners(newCardView);

            addChild(newCardView, 1);
            log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

            break;
        }
    }

    _controller->handleUndo();
}

void HelloWorld::test() {
    log("_playfieldCards:");
    for (CardModel cardView : _controller->getModel()->getPlayfieldCards()) {
        if (1){
            log("Card Face: %d, Position: (%.2f, %.2f)",
                cardView.getFace(),
                cardView.getPosition().x,
                cardView.getPosition().y);
        }
    }
}