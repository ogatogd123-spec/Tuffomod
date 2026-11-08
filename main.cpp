
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(TuffoMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = CCMenu::create();
        menu->setID("tuffo-menu"_spr);

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("TUFFO"),
            this,
            menu_selector(TuffoMenuLayer::openTuffo)
        );

        button->setID("tuffo-button"_spr);
        menu->addChild(button);

        menu->setPosition({
            CCDirector::get()->getWinSize().width * 0.18f,
            CCDirector::get()->getWinSize().height * 0.28f
        });

        this->addChild(menu, 100);

        return true;
    }

    void openTuffo(CCObject*) {
        auto popup = FLAlertLayer::create(
            "TUFFO MOD",
            "PLAYER\n"
            "GAMEPLAY\n"
            "INTERFACE\n"
            "MISC\n\n"
            "Configuracoes do Tuffo Mod",
            "FECHAR"
        );

        popup->show();
    }
};
