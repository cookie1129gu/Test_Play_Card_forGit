#include "GameModel.h"

void GameModel::loadLevel(const LevelConfig* config)
{
    _playfieldCards.clear();
    _stackCards.clear();

    // ����������
    for (const auto& cardConfig : config->getPlayfieldCards()) {
        CardModel card(cardConfig.cardFace, cardConfig.cardSuit, cardConfig.faceUp);
        card.setPosition(cardConfig.position);
        card.setInPile(false);
        _playfieldCards.push_back(card);
    }

    // ���ض�����
    for (const auto& cardConfig : config->getStackCards()) {
        CardModel card(cardConfig.cardFace, cardConfig.cardSuit, cardConfig.faceUp);
        card.setPosition(cardConfig.position);
        card.setInPile(true);
        _stackCards.push_back(card);
    }
}

// ����������
void GameModel::moveCardToStack(int playfieldIndex) {
    if (playfieldIndex < 0 || playfieldIndex >= _playfieldCards.size()) return;
    //log("AAA:%d and %d", _playfieldCards.size(), _stackCards.size());

    auto& card = _playfieldCards[playfieldIndex];

    _stackCards.pop_back();
    _stackCards.push_back(card);
    _playfieldCards.erase(_playfieldCards.begin() + playfieldIndex);

    //log("BBB:%d and %d", _playfieldCards.size(), _stackCards.size());
}

const CardModel& GameModel::getPlayfieldCard(int index) const {
    return _playfieldCards.at(index);
}

size_t GameModel::getPlayfieldCardCount() const {
    return _playfieldCards.size();
}

// ����������
void GameModel::promoteCardToTop(int stackIndex) {
    if (stackIndex < 0 || stackIndex >= _stackCards.size()) return;
    if (stackIndex == _stackCards.size() - 1) return; // �Ѿ��Ƕ�����
    log("AAA:%d and %d", _playfieldCards.size(), _stackCards.size());
    _stackCards.pop_back();

    auto card = _stackCards[stackIndex];
    _stackCards.erase(_stackCards.begin() + stackIndex);
    _stackCards.push_back(card);
    log("AAA:%d and %d", _playfieldCards.size(), _stackCards.size());
    
}

const CardModel* GameModel::getTopStackCard() const {
    return _stackCards.empty() ? nullptr : &_stackCards.back();
}

size_t GameModel::getStackCardCount() const {
    return _stackCards.size();
}

// ��Ϸ����
bool GameModel::isMatch(const CardModel& card1, const CardModel& card2) const {
    int diff = abs(static_cast<int>(card1.getFace()) - static_cast<int>(card2.getFace()));
    log("diff: %d", diff);

    return diff == 1 || diff == 12; // A��KҲƥ��
}

const std::vector<CardModel>& GameModel::getPlayfieldCards() const {
    return _playfieldCards;
}

const std::vector<CardModel>& GameModel::getStackCards() const {
    return _stackCards;
}

void GameModel::undoMoveCardToStack(int originalPlayfieldIndex, const CardModel& card, const cocos2d::Vec2& originalPos)
{
    log("CCC:%d and %d", _playfieldCards.size(), _stackCards.size());
    if (_stackCards.empty()) return;

    // �����������ǵ���
    CardModel restoredCard = card;
    restoredCard.setPosition(originalPos);

    // �������ƶ�������������
    CardModel card1 = _stackCards.back();
    _stackCards.pop_back();

    _stackCards.push_back(restoredCard);
    _playfieldCards.push_back(card1);

    log("DDD:%d and %d", _playfieldCards.size(), _stackCards.size());
}

void GameModel::undoPromoteCardToTop(int originalStackIndex, const CardModel& card, const cocos2d::Vec2& originalPos)
{
    CardModel restoredCard = card; // ԭ����
    restoredCard.setPosition(originalPos);
    _stackCards.push_back(restoredCard);
    

    log("EEE:%d and %d", _playfieldCards.size(), _stackCards.size());
}

void GameModel::test() {
    log("_playfieldCards:");
    for (const auto& cardModel : _playfieldCards) { // ���� CardModel ����
        log("Card Face: %d, Position: (%.2f, %.2f)",
            cardModel.getFace(),                // ֱ�ӻ�ȡ Face ֵ
            cardModel.getPosition().x,          // ֱ�ӻ�ȡλ��
            cardModel.getPosition().y);
    }
}
