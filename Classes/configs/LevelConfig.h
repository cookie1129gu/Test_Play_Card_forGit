#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H

#include "cocos2d.h"
#include "CardResConfig.h"

USING_NS_CC;

/*
�ؿ�������
����洢�������ļ��ж�ȡ�Ĺؿ�����
*/
class LevelConfig{
public:
	/**
	 * @struct CardConfig
	 * @brief ���ſ��Ƶ�������Ϣ
	*/
	struct CardConfig
	{
		CardResConfig::CardFaceType cardFace; // ������������
		CardResConfig::CardSuitType cardSuit; // ��ɫ����
		Vec2 position; // �����ڳ����е�λ��
		bool faceUp = true; // Ĭ�����泯��

		/**
		* @brief ���캯��
		* @param face ��������ö��ֵ
		* @param suit ��ɫ����ö��ֵ
		* @param pos λ������
		* @param up ����״̬
		*/
		CardConfig(CardResConfig::CardFaceType face,
			CardResConfig::CardSuitType suit, 
			const Vec2& pos,
			bool up = true)
			: cardFace(face), cardSuit(suit), position(pos), faceUp(up){ }
	};

	/**
	 * @brief ��ȡ���������������б�
	 * @return ������������������
	*/
	const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }

	/**
	 * @brief ��ȡ���������������б�
	 * @return ������������������
	*/
	const std::vector<CardConfig>& getStackCards() const { return _stackCards; }

private:
	std::vector<CardConfig> _playfieldCards; // ��������������
	std::vector<CardConfig> _stackCards; // ��������������

	// ��ֹĬ�Ϲ��캯������ͨ��Loader����ʵ��
	LevelConfig() = default;

	// ����Loader����˽�й���
	friend class LevelConfigLoader;
};

#endif

