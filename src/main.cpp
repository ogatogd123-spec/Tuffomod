#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(TuffoMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("TUFFO"),
            this,
            menu_selector(TuffoMenuLayer::onTuffo)
        );

        auto menu = CCMenu::create();
        menu->addChild(button);
        menu->setPosition({ CCDirector::get()->getWinSize().width / 2, 45 });
        this->addChild(menu);

        return true;
    }

    void onTuffo(CCObject*) {
        FLAlertLayer::create(
            "Tuffo Mod",
            "Bem-vindo ao Tuffo Mod!FEITO POR IA",
            "OK"
        )->show();
    }
};
