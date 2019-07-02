#pragma once

#include "pitem.h"

#include <map>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include <QObject>

#include <QMap>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(QNetworkAccessManager)

using json = nlohmann::json;

class ItemAPI : public QObject
{
    Q_OBJECT

public:
    ItemAPI(QObject* parent = nullptr);

    PItem* parse(QString itemText);

    QString toJson(PItem* item);

    void simplePriceCheck(std::shared_ptr<PItem> item);
    void advancedPriceCheck(std::shared_ptr<PItem> item);

signals:
    void humour(QString msg);
    void priceCheckFinished(std::shared_ptr<PItem> item, QString results);

private:
    enum filter_type_e : uint8_t
    {
        weapon_filter = 0,
        armour_filter,
        socket_filter,
        req_filter,
        misc_filter,
        special_filter // manual parse
    };

    enum weapon_filters_e : uint8_t
    {
        weapon_filter_aps = 0,
        weapon_filter_crit,
        weapon_filter_pdps,
        weapon_filter_edps
    };

    enum armour_filters_e : uint8_t
    {
        armour_filter_ar = 0,
        armour_filter_ev,
        armour_filter_es,
        armour_filter_block
    };

    enum req_filters_e : uint8_t
    {
        req_filter_lvl = 0,
        req_filter_str,
        req_filter_dex,
        req_filter_int
    };

    enum misc_filters_e : uint8_t
    {
        misc_filter_quality = 0,
        misc_filter_ilvl,
        misc_filter_gem_level,
        misc_filter_gem_level_progress,
        misc_filter_shaper_item,
        misc_filter_elder_item,
        misc_filter_synthesised_item,
        misc_filter_identified,
        misc_filter_corrupted,
        misc_filter_mirrored,
        misc_filter_crafted,
        misc_filter_veiled,
        misc_filter_enchanted,
        misc_filter_talisman_level
    };

    const QMap<QString, QVector<uint8_t>> c_propMap = {{"Quality", {misc_filter, misc_filter_quality}},
                                                       {"Evasion Rating", {armour_filter, armour_filter_ev}},
                                                       {"Energy Shield", {armour_filter, armour_filter_es}},
                                                       {"Armour", {armour_filter, armour_filter_ar}},
                                                       {"Chance to Block", {armour_filter, armour_filter_block}},
                                                       {"Requirements", {special_filter}},
                                                       {"Level", {special_filter}},
                                                       {"req_level", {req_filter, req_filter_lvl}},
                                                       {"gem_level", {misc_filter, misc_filter_gem_level}},
                                                       {"Str", {req_filter, req_filter_str}},
                                                       {"Dex", {req_filter, req_filter_dex}},
                                                       {"Int", {req_filter, req_filter_int}},
                                                       {"Sockets", {socket_filter}},
                                                       {"Item Level", {misc_filter, misc_filter_ilvl}},
                                                       {"Physical Damage", {weapon_filter, weapon_filter_pdps}},
                                                       {"Critical Strike Chance", {weapon_filter, weapon_filter_crit}},
                                                       {"Attacks per Second", {weapon_filter, weapon_filter_aps}},
                                                       {"Elemental Damage", {weapon_filter, weapon_filter_edps}},
                                                       {"Experience", {misc_filter, misc_filter_gem_level_progress}}};

    json c_baseCat;

    std::map<std::string, std::string> c_baseMap;

    int              readPropInt(QString prop);
    mmv_t            readPropIntRange(QString prop);
    double           readPropFloat(QString prop);
    socket_filters_t readSockets(QString prop);
    int              readPropExp(QString prop);
    std::string      readName(QString name);
    std::string      readType(PItem* item, QString type);

    void parseProp(PItem* item, QString prop);
    void parseStat(PItem* item, QString stat);

    void processPriceResults(std::shared_ptr<PItem> item, json results);

    QString m_section;

    QNetworkAccessManager* m_manager;

    json                                       m_leagues;
    std::unordered_multimap<std::string, json> m_stats_by_text;
    std::unordered_multimap<std::string, json> m_stats_by_id;
    std::unordered_multimap<std::string, json> m_uniques;

    std::string m_mapdisc = "warfortheatlas"; // default map discriminator
};