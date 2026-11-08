
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(TuffoPlayLayer, PlayLayer) {
    void onEnter() {
        PlayLayer::onEnter();

        auto winSize = CCDirector::get()->getWinSize();

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("TUFFO"),
            this,
            menu_selector(TuffoPlayLayer::onTuffo)
        );

        button->setPosition({
            winSize.width - 55.f,
            winSize.height * 0.55f
        });

        menu->addChild(button);
        this->addChild(menu, 9999);
    }

    void onTuffo(CCObject*) {
        FLAlertLayer::create(
            "TUFFO MOD",
            "Bem-vindo ao Mod Menu!\n\n"
            "PLAYER - Personalizacao\n"
            "GAMEPLAY - Opcoes de jogo\n"
            "INTERFACE - Aparencia\n"
            "MISC - Outras opcoes",
            "FECHAR"
        )->show();
    }
};

