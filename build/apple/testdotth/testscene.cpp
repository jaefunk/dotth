
#include "testscene.hpp"

void testscene::init(const json& data)
{
    //loadview("resources/views/testscene.xml");
    {
        auto parent = std::make_shared<dotth::cube>();
        parent->init();
        parent->trans().pos_x(0.f);
        parent->trans().scl(0.5f);
        attach(parent);

        {
            auto child = std::make_shared<dotth::cube>();
            child->init();
            child->trans().pos_x(-2.f);
            child->trans().scl(0.5f);
            parent->attach(child);
            auto child2 = std::make_shared<dotth::cube>();
            child2->init();
            child2->trans().pos_x(-2.f);
            child2->trans().scl(0.5f);
            child->attach(child2);
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
        }
        {
            auto child = std::make_shared<dotth::cube>();
            child->init();
            child->trans().pos_x(2.f);
            child->trans().scl(0.5f);
            parent->attach(child);
            auto child2 = std::make_shared<dotth::cube>();
            child2->init();
            child2->trans().pos_x(2.f);
            child2->trans().scl(0.5f);
            child->attach(child2);
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
        }
        {
            auto child = std::make_shared<dotth::cube>();
            child->init();
            child->trans().pos_y(-2.f);
            child->trans().scl(0.5f);
            parent->attach(child);
            auto child2 = std::make_shared<dotth::cube>();
            child2->init();
            child2->trans().pos_y(-2.f);
            child2->trans().scl(0.5f);
            child->attach(child2);
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
        }
        {
            auto child = std::make_shared<dotth::cube>();
            child->init();
            child->trans().pos_y(2.f);
            child->trans().scl(0.5f);
            parent->attach(child);
            auto child2 = std::make_shared<dotth::cube>();
            child2->init();
            child2->trans().pos_y(2.f);
            child2->trans().scl(0.5f);
            child->attach(child2);
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
        }
        {
            auto child = std::make_shared<dotth::cube>();
            child->init();
            child->trans().pos_z(-2.f);
            child->trans().scl(0.5f);
            parent->attach(child);
            auto child2 = std::make_shared<dotth::cube>();
            child2->init();
            child2->trans().pos_z(-2.f);
            child2->trans().scl(0.5f);
            child->attach(child2);
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
        }
        {
            auto child = std::make_shared<dotth::cube>();
            child->init();
            child->trans().pos_z(2.f);
            child->trans().scl(0.5f);
            parent->attach(child);
            auto child2 = std::make_shared<dotth::cube>();
            child2->init();
            child2->trans().pos_z(2.f);
            child2->trans().scl(0.5f);
            child->attach(child2);
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_x(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_y(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
            {
                auto child2 = std::make_shared<dotth::cube>();
                child2->init();
                child2->trans().pos_z(-2.f);
                child2->trans().scl(0.5f);
                child->attach(child2);
            }
        }

        

        
    }

    auto parent = std::make_shared<dotth::rectangle>();
    parent->init();
    parent->set_color({ 1.f, 0.f, 0.f, 1.f });
    parent->trans().size(100.f, 100.f);
    parent->trans().pos_x(200.f);
    attach(parent);

    auto child = std::make_shared<dotth::rectangle>();
    child->init();
    child->set_color({ 0.f, 1.f, 0.f, 1.f });
    child->trans().size(100.f, 100.f);
    child->trans().scl(0.5f);
    child->trans().pos_x(100.f);
    parent->attach(child);

    auto child2 = std::make_shared<dotth::rectangle>();
    child2->init();
    child2->set_color({ 0.f, 0.f, 1.f, 1.f });
    child2->trans().pos_x(100.f);
    child2->trans().scl(0.5f);
    child2->trans().size(100.f, 100.f);
    child->attach(child2);
}

void testscene::on_update(const float& delta)
{
}
