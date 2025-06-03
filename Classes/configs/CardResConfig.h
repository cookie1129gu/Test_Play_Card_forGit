// ����ui��Դ������
#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include "cocos2d.h"

USING_NS_CC;

class CardResConfig {
public:
	// ��ɫ����
	enum CardSuitType
	{
		CST_NONE = -1,
		CST_CLUBS,      // ÷��
		CST_DIAMONDS,   // ����
		CST_HEARTS,     // ����
		CST_SPADES,     // ����
		CST_NUM_CARD_SUIT_TYPES
	};

	// ��������
	enum CardFaceType
	{
		CFT_NONE = -1,
		CFT_ACE,
		CFT_TWO,
		CFT_THREE,
		CFT_FOUR,
		CFT_FIVE,
		CFT_SIX,
		CFT_SEVEN,
		CFT_EIGHT,
		CFT_NINE,
		CFT_TEN,
		CFT_JACK,
		CFT_QUEEN,
		CFT_KING,
		CFT_NUM_CARD_FACE_TYPES
	};

	// ��ȡ��ɫ��Դ·��
	static std::string getSuitResource(CardSuitType suit) {
		std::string path = "res/suits/";
		
		switch (suit) {
			case CST_CLUBS: return path + "club.png";
			case CST_DIAMONDS: return path + "diamond.png";
			case CST_HEARTS:   return path + "heart.png";
			case CST_SPADES:   return path + "spade.png";
			default:     return "";
		}
	}

	// ��ȡ��ɫ��ɫ
	static Color3B getSuitColor(CardSuitType suit) {
		return (suit == CST_DIAMONDS || suit == CST_HEARTS) ? Color3B::RED : Color3B::BLACK;
	}

	// ��ȡ����ֵͼƬ��Դ·��
	static std::string getBigNumberResource(CardFaceType face, CardSuitType suit) {
		std::string color = (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
		return "res/number/big_" + color + "_" + faceToString(face) + ".png";
	}
	// ��ȡС��ֵͼƬ��Դ·��
	static std::string getSmallNumberResource(CardFaceType face, CardSuitType suit) {
		std::string color = (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
		return "res/number/small_" + color + "_" + faceToString(face) + ".png";
	}
	// ��ȡ���Ʊ���ͼƬ��Դ·��
	static std::string getCardBackgroundResource() {
		return "res/card_general.png";
	}

private:
	// ������ֵת��Ϊ�ַ�����ʾ
	static std::string faceToString(CardFaceType face) {
		switch (face) {
			case CFT_ACE:   return "A";
			case CFT_JACK:  return "J";
			case CFT_QUEEN: return "Q";
			case CFT_KING:  return "K";
			default: {
				// ���������ƣ�2-10��
				int value = static_cast<int>(face) + 1; // CFT_TWO��Ӧ2���Դ�����
				if (value >= 2 && value <= 10) {
					return std::to_string(value);
				}
				return ""; // δ֪���Ĭ�Ϸ��ؿ��ַ���
			}
		}
	}

};

#endif
