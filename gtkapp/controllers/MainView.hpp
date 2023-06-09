#pragma once
#include <gtkapp/Model.hpp>
#include <gtkapp/MainWindow.hpp>
#include <gtkapp/views/MainView.hpp>

namespace gtkapp::controllers
{
    class MainView : public views::MainView
    {
    public:
        MainView(gtkapp::MainWindow& navigation, Model& model);

        void on_request_new_item() override;
        void on_delete_item(const types::Item& item) override;
        void on_update_item(types::Item& item) override;
        void on_selected_item_changed(types::Item* item) override;
    
    private:
        gtkapp::MainWindow& m_navigation;
        Model& m_model;
    };
} // namespace gtkapp
