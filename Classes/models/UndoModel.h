#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include "CardModel.h"

struct UndoAction {
    enum ActionType {
        MOVE_TO_STACK,
        PROMOTE_TO_TOP
    };

    ActionType type;
    int cardIndex; // �����Ŀ�������
    CardModel cardState; // ����״̬
    cocos2d::Vec2 originalPosition; // ԭʼλ��

    UndoAction()
        : type(MOVE_TO_STACK),
        cardIndex(-1),
        cardState(CardResConfig::CFT_NONE, CardResConfig::CST_NONE),
        originalPosition(cocos2d::Vec2::ZERO) {
    }
};

class UndoModel {
public:
    void addAction(const UndoAction& action);
    bool hasActions() const;
    UndoAction popLastAction();
    void clear();

    // ��������ж���
    int getCount();

    // �鿴���һ�����������Ƴ�
    const UndoAction& peekLastAction() const {
        CCASSERT(!_actions.empty(), "No actions to peek");
        return _actions.back();
    }

private:
    std::vector<UndoAction> _actions;
};

#endif 
