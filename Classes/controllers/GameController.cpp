#include "GameController.h"

USING_NS_CC;

GameController::GameController(GameModel* model)
    : _model(model), _undoManager(model) {
    // ����У��
    CCASSERT(model != nullptr, "GameModel is null");
}

bool GameController::handlePlayfieldCardClick(int cardIndex) {
    // 1. �������
    if (cardIndex < 0 || cardIndex >= _model->getPlayfieldCardCount()) {
        log("index Invalid: %d", cardIndex);
        return false;
    }

    // 2. ��ȡ������
    const CardModel* topStackCard = _model->getTopStackCard();
    if (!topStackCard) {
        log("There are no available top cards in the pile area");
        return false;
    }

    // 3. ���ƥ��
    const CardModel* card1 = _model->getTopStackCard(); // ԭ���Ķ���model
    const CardModel& clickedCard = _model->getPlayfieldCard(cardIndex); // �¶���model

    log("cardIndex: %d", cardIndex);
    log("clickedCard,Px = %.2f, Py = %.2f", clickedCard.getPosition().x, clickedCard.getPosition().y);

    if (_model->isMatch(clickedCard, *topStackCard)) {
        // ��¼����
        _undoManager.recordMoveToStack(cardIndex, *card1, clickedCard.getPosition());
        // 4. ִ���ƶ���ͨ��ģ�ͷ����޸�״̬��
        const_cast<GameModel*>(_model)->moveCardToStack(cardIndex);

        
        return true;
    }

    log("Card is not match: %d and %d",
        static_cast<int>(clickedCard.getFace()),
        static_cast<int>(topStackCard->getFace()));
    return false;
}

bool GameController::handleStackCardClick(int cardIndex) {
    // 1. �������
    if (cardIndex < 0 || cardIndex >= _model->getStackCardCount()) {
        log("stack index Invalid: %d", cardIndex);
        return false;
    }

    // 2. ����Ƿ��Ѿ��Ƕ�����
    if (cardIndex == _model->getStackCardCount() - 1) {
        log("This card is already the top card");
        return false;
    }

    // ��¼����
    const CardModel* card1 = _model->getTopStackCard(); // ԭ���Ķ���model
    const CardModel& clickedCard = _model->getStackCard(cardIndex); // �¶���model
    _undoManager.recordPromoteToTop(cardIndex, *card1, clickedCard.getPosition());

    // 3. ִ������������ͨ��ģ�ͷ����޸�״̬��
    const_cast<GameModel*>(_model)->promoteCardToTop(cardIndex);

    return true;
}

bool GameController::handleUndo()
{
    return _undoManager.undo();
}

bool GameController::emptyUndo() 
{
    return !_undoManager.ifUndo();
}