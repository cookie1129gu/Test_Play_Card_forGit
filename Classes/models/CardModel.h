#ifndef CARD_MODEL_H
#define CARD_MODEL_H

#include "configs/CardResConfig.h"

class CardModel
{
public:
	// ���캯��
	CardModel(CardResConfig::CardFaceType face, CardResConfig::CardSuitType suit, bool faceUp = true)
	:_face(face), _suit(suit), _faceUp(faceUp), _selected(false) { }

	// ��ȡ����ֵ
	CardResConfig::CardFaceType getFace() const { return _face; }

	// ���ÿ���ֵ
	void setFace(CardResConfig::CardFaceType face) { _face = face; }

	// ��ȡ��ɫ
	CardResConfig::CardSuitType getSuit() const { return _suit; }

	// ���û�ɫ
	void setSuit(CardResConfig::CardSuitType suit) { _suit = suit; }

	// �Ƿ����泯��
	bool isFaceUp() const { return _faceUp; }

	// �������泯��״̬
	void setFaceUp(bool faceUp) { _faceUp = faceUp; }

	// �Ƿ�ѡ��
	bool isSelected() const { return _selected; }

	// ����ѡ��״̬
	void setSelected(bool selected) { _selected = selected; }

	// �����Ƿ���ƶ�
	bool isMovable() const { return _movable; }

	// ���ÿ��ƶ�״̬
	void setMovable(bool movable) { _movable = movable; }

	// �����Ƿ����ƶ���
	bool isInPile() const { return _inPile; }

	// �����ƶ�״̬
	void setInPile(bool inPile) { _inPile = inPile; }

	// �����Ƿ�ɱ�ѡ��
	bool isSelectable() const { return _selectable; }

	// ���ÿ�ѡ��״̬
	void setSelectable(bool selectable) { _selectable = selectable; }

	// ��ȡ����ΨһID
	int getCardId() const { return _cardId; }

	// ��ȡ����λ��
	const Vec2& getPosition() const { return _position; }

	// ���ÿ���λ��
	void setPosition(const Vec2& pos) { _position = pos; }

	~CardModel() {};

private:
	CardResConfig::CardFaceType _face; // ����ֵ
	CardResConfig::CardSuitType _suit; // ��ɫ
	bool _faceUp; // �Ƿ����泯��
	bool _selected; // �Ƿ�ѡ��
	bool _movable = true; // �Ƿ���ƶ�
	bool _inPile = false; // �Ƿ����ƶ���
	bool _selectable = true; // �Ƿ�ɱ�ѡ��
	Vec2 _position = Vec2::ZERO; // ����λ��

	// ����Ψһ��ʶ��
	int _cardId = -1;
};

#endif // !CARD_MODEL_H
