#pragma once
#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "models/UndoModel.h"
#include "models/GameModel.h"

class UndoManager
{
public:
	explicit UndoManager(GameModel* model);
	
	// ��¼�ƶ����Ƶ��������Ĳ���
	void recordMoveToStack(int playfieldIndex, const CardModel& card, const cocos2d::Vec2& originalPos);

	// ��¼�������Ƶ������Ĳ���
	void recordPromoteToTop(int stackIndex, const CardModel& card, const cocos2d::Vec2& originalPos);

	// ִ�л��˲���
	bool undo();

	// ����Ƿ��ж���
	bool ifUndo();

	// ��ȡ���һ������
	const UndoAction* getLastAction() const {
		return _undoModel.hasActions() ? &_undoModel.peekLastAction() : nullptr;
	}

private:
	GameModel* _model;
	UndoModel _undoModel;
};

#endif // UNDO_MANAGER_H

