#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "cocos2d.h"

class GameController {
public:
    // ʹ��constģ��ָ���ʼ��
    explicit GameController(GameModel* model);

    // �������������Ƶ��
    bool handlePlayfieldCardClick(int cardIndex);

    // ������������Ƶ��
    bool handleStackCardClick(int cardIndex);

    // ���˹���
    bool handleUndo();

    // ��鵱ǰ�Ƿ���Ի���
    bool emptyUndo();

    // ��ȡģ������
    const GameModel* getModel() const { return _model; }

    // ��ȡ����ģ��
    UndoManager* getUndoManager() { return &_undoManager; }

private:
    const GameModel* _model;
    UndoManager _undoManager;
};

#endif // GAME_CONTROLLER_H
