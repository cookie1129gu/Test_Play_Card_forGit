#include "LevelConfigLoader.h"

USING_NS_CC;
//using namespace rapidjson;

LevelConfig* LevelConfigLoader::loadConfig(const std::string& filename) {
	// ��ȡJSON�ļ�
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
	std::string content = FileUtils::getInstance()->getStringFromFile(fullPath);

	if (content.empty()) {
		CCLOG("�޷��Ķ��ؿ�%s�ļ���", filename.c_str());
		return nullptr;
	}

	// ����JSON
	rapidjson::Document doc;
	if (doc.Parse(content.c_str()).HasParseError()) {
		CCLOG("JSON parse error in %s", filename.c_str());
		return nullptr;
	}
	if (!doc.IsObject()) {
		CCLOG("Invalid JSON structure in %s", filename.c_str());
		return nullptr;
	}

	// ��������ʵ��
	auto* config = new LevelConfig();

	// �����������Ͷ�����
	if (!parseCardConfigs(doc, config)) {
		delete config;
		return nullptr;
	}

	return config;
}

bool LevelConfigLoader::parseCardConfigs(const rapidjson::Value& doc, LevelConfig* config) {
	bool hasValidCards = false;

	// ��������������
	if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
		hasValidCards |= parseCardArray(doc["Playfield"], config->_playfieldCards);
	}

	// ��������������
	if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
		hasValidCards |= parseCardArray(doc["Stack"], config->_stackCards);
	}

	return hasValidCards;
}

bool LevelConfigLoader::parseCardArray(const rapidjson::Value& array, std::vector<LevelConfig::CardConfig>& outCards)
{
	bool hasValidCards = false;

	for (auto& item : array.GetArray()) {
		if (!item.IsObject()) continue;

		auto cardConfig = parseSingleCard(item);
		if (cardConfig.cardFace != CardResConfig::CardFaceType::CFT_NONE && cardConfig.cardSuit != CardResConfig::CardSuitType::CST_NONE) {
			outCards.push_back(cardConfig);
			hasValidCards = true;
		}
	}

	return hasValidCards;
}

LevelConfig::CardConfig LevelConfigLoader::parseSingleCard(const rapidjson::Value& item)
{
	CardResConfig::CardFaceType face = CardResConfig::CardFaceType::CFT_NONE;
	CardResConfig::CardSuitType suit = CardResConfig::CardSuitType::CST_NONE;
	Vec2 pos;

	// ����CardFace
	if (item.HasMember("CardFace") && item["CardFace"].IsInt()) {
		int faceValue = item["CardFace"].GetInt();
		if (faceValue >= 0 && faceValue < CardResConfig::CFT_NUM_CARD_FACE_TYPES) {
			face = static_cast<CardResConfig::CardFaceType>(faceValue);
		}
	}

	// ����CardSuit
	if (item.HasMember("CardSuit") && item["CardSuit"].IsInt()) {
		int suitValue = item["CardSuit"].GetInt();
		if (suitValue >= 0 && suitValue < CardResConfig::CardSuitType::CST_NUM_CARD_SUIT_TYPES) {
			suit = static_cast<CardResConfig::CardSuitType>(suitValue);
		}
	}

	// ����Position
	if (item.HasMember("Position") && item["Position"].IsObject()) {
		const rapidjson::Value& posObj = item["Position"];
		pos.x = posObj["x"].GetFloat();
		pos.y = posObj["y"].GetFloat();
	}

	// �������泯��
	bool faceUp = true; // Ĭ�����泯��

	// �����FaceUp�ֶ��������û����ʹ��Ĭ��ֵ
	if (item.HasMember("FaceUp") && item["FaceUp"].IsBool()) {
		faceUp = item["FaceUp"].GetBool();
	}

	return { face, suit, pos, faceUp };
}
