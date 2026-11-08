#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

namespace {
    class TuffoPopup : public Popup<> {
    protected:
        bool setup() override {
            this->setTitle("Tuffo Mod");

            auto center = ccp(
                m_mainLayer->getContentSize().width / 2.f,
                m_mainLayer->getContentSize().height / 2.f
            );

            auto info = CCLabelBMFont::create("Bem-vindo ao Tuffo Mod!", "bigFont.fnt");
            info->setScale(0.42f);
            info->setPosition(center + ccp(0, 34));
            m_mainLayer->addChild(info);

            auto hint = CCLabelBMFont::create(
                "Configure as funcoes nas opcoes do Geode.",
                "goldFont.fnt"
            );
            hint->setScale(0.32f);
            hint->setPosition(center + ccp(0, 5));
            m_mainLayer->addChild(hint);

            auto close = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
                this,
                menu_selector(TuffoPopup::onDismiss)
            );
            auto menu = CCMenu::create();
            menu->addChild(close);
            menu->setPosition(center + ccp(0, -43));
            m_mainLayer->addChild(menu);

            return true;
        }

        void onDismiss(CCObject*) {
            this->removeFromParentAndCleanup(true);
        }

    public:
        static TuffoPopup* create() {
            auto ret = new TuffoPopup();
            if (ret && ret->init(320.f, 190.f, "GJ_square01.png")) {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
    };
}

class $modify(TuffoMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        if (!Mod::get()->getSettingValue<bool>("show-menu-button")) {
            return true;
        }

        auto sprite = CCLabelBMFont::create("TUFFO", "goldFont.fnt");
        sprite->setScale(0.48f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(TuffoMenuLayer::onTuffoButton)
        );

        auto menu = CCMenu::create();
        menu->addChild(button);
        menu->setID("tuffo-mod-menu");
        menu->setPosition(45.f, 32.f);
        this->addChild(menu, 100);

        return true;
    }

    void onTuffoButton(CCObject*) {
        if (!Mod::get()->getSettingValue<bool>("custom-interface")) {
            FLAlertLayer::create(
                "Tuffo Mod",
                "A interface personalizada esta desativada nas configuracoes do Geode.",
                "OK"
            )->show();
            return;
        }

        TuffoPopup::create()->show();
    }
};
