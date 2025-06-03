#pragma once
#ifndef GAME_MODEL_H
#define GAME_MODEL_H
#include <configs/LevelConfig.h>
#include "CardModel.h"

class GameModel {
public:
    // ���عؿ�����
    void loadLevel(const LevelConfig* config);

    // ����������
    void moveCardToStack(int playfieldIndex);
    const CardModel& getPlayfieldCard(int index) const;
    size_t getPlayfieldCardCount() const;
    const std::vector<CardModel>& getPlayfieldCards() const;

    // ����������
    void promoteCardToTop(int stackIndex);
    const CardModel* getTopStackCard() const;
    size_t getStackCardCount() const;
    const std::vector<CardModel>& getStackCards() const;

    // ���˲���
    void undoMoveCardToStack(int originalPlayfieldIndex, const CardModel& card, const cocos2d::Vec2& originalPos);
    void undoPromoteCardToTop(int originalStackIndex, const CardModel& card, const cocos2d::Vec2& originalPos);

    // ��Ϸ����
    bool isMatch(const CardModel& card1, const CardModel& card2) const;

    const CardModel& getStackCard(size_t index) const {
        return _stackCards.at(index);
    }

    void test();

private:
    std::vector<CardModel> _playfieldCards; // ����������
    std::vector<CardModel> _stackCards;     // ����������, �����Ƕ����������һ��

};

#endif // !GAME_MODEL_H
