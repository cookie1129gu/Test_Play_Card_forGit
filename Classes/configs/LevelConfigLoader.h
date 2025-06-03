#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H

#include "LevelConfig.h"
#include "cocos2d.h"
#include "rapidjson/document.h"


class LevelConfigLoader {
public:
    /**
     * @brief ���عؿ������ļ�
     * @param filename JSON�ļ�����λ��resĿ¼�£�
     * @return �������LevelConfigʵ����ʧ�ܷ���nullptr
     */
    static LevelConfig* loadConfig(const std::string& filename);

private:
    /**
     * @brief ����������������
     * @param doc JSON�ĵ�����
     * @param config Ŀ��LevelConfigʵ��
     * @return �Ƿ�����ɹ�
     */
    static bool parseCardConfigs(const rapidjson::Value& doc, LevelConfig* config);

    // ������������
    static bool parseCardArray(const rapidjson::Value& array, 
        std::vector<LevelConfig::CardConfig>& outCards);

    // �������ſ���
    static LevelConfig::CardConfig parseSingleCard(const rapidjson::Value& item);

    /**
     * @brief ��ֹ���캯������̬�����ࣩ
     */
    LevelConfigLoader() = delete;
};

#endif
