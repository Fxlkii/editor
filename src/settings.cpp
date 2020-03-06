/*******************************************
 * Zira Editor
 * A lightweight PHP Editor
 * (C)2019 https://github.com/ziracms/editor
 *******************************************/

#include "settings.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QColor>

const QString COLOR_SCHEME_TYPE = "scheme";
const QString COLOR_SCHEME_LIGHT = "light";
const QString COLOR_SCHEME_DARK = "dark";

const QString THEME_SYSTEM = "system";
const QString THEME_LIGHT = "light";
const QString THEME_DARK = "dark";

const QString CUSTOM_THEME_CSS_FILE = "theme.css";
const QString CUSTOM_THEME_SCHEME_FILE = "scheme.css";
const QString CUSTOM_THEME_COLORS_FILE = "colors";

const QString CUSTOM_THEMES_FALLBACK_FOLDER = "themes";
const QString PHP_MANUAL_FALLBACK_FOLDER = "php-chunked-xhtml";

const std::string PHP_MANUAL_ENCODING = "UTF-8";

Settings::Settings(QObject * parent) : QObject(parent)
{
    data = {
        {"file_dialog_filter", "Project files (*.php *.phtml *.html *.xml *.tpl *.css *.less *.scss *.sass *.js *.htaccess *.txt);;All files (*)"},
        {"file_dialog_path", ""},
        {"file_browser_home", ""},
        {"php_manual_path", ""},
        {"app_font_family", ""},
        {"app_font_size", "12"},
        {"editor_font_family", ""},
        {"editor_font_size", "12"},
        {"editor_popup_font_size", "11"},
        {"editor_tooltip_font_size", "10"},
        {"editor_breadcrumbs_font_size", "10"},
        {"editor_tab_width", "4"},
        {"editor_tab_type", "tabs"},
        {"editor_tab_type_detect", "yes"},
        {"editor_new_line_mode", "lf"},
        {"editor_encoding", "UTF-8"},
        {"editor_fallback_encoding", "CP-1251"},
        {"editor_clean_before_save", "no"},
        {"editor_breadcrumbs_enabled", "yes"},
        {"editor_show_annotations", "yes"},
        {"editor_parse_interval", "5000"},
        {"editor_long_line_marker_enabled", "yes"},
        {"editor_wrap_long_lines", "no"},
        {"highlight_spaces", "no"},
        {"highlight_tabs", "no"},
        {"highlight_php_extensions", "php, phtml, tpl, html"},
        {"highlight_js_extensions", "js"},
        {"highlight_css_extensions", "css, less, scss, sass"},
        {"highlight_html_extensions", "xml"},
        {"parser_enable_php_lint", "yes"},
        {"parser_enable_php_cs", "yes"},
        {"parser_enable_parse_php", "yes"},
        {"parser_enable_parse_js", "yes"},
        {"parser_enable_parse_css", "yes"},
        {"parser_enable_git", "yes"},
        {"parser_enable_servers", "yes"},
        {"parser_php_path", ""},
        {"parser_git_path", ""},
        {"parser_bash_path", ""},
        {"parser_sassc_path", ""},
        {"parser_phpcs_path", ""},
        {"parser_phpcs_standard", "PSR2"},
        {"parser_phpcs_error_severity", "5"},
        {"parser_phpcs_warning_severity", "5"},
        {"shortcut_backtab", "Shift+Tab"},
        {"shortcut_save", "Ctrl+S"},
        {"shortcut_save_all", "Ctrl+Shift+S"},
        {"shortcut_comment", "Ctrl+/"},
        {"shortcut_overwrite_mode", "Insert"},
        {"shortcut_tooltip", "Ctrl+Space"},
        {"shortcut_search", "Ctrl+F"},
        {"shortcut_search_in_files", "Ctrl+Shift+F"},
        {"shortcut_help", "F1"},
        {"shortcut_sidebar", "Ctrl+Return"},
        {"shortcut_toolbar", "Ctrl+T"},
        {"shortcut_output", "Ctrl+Shift+Return"},
        {"shortcut_quick_access", "F3"},
        {"shortcut_quick_access_alt", "Ctrl+P"},
        {"shortcut_duplicate_line", "Ctrl+D"},
        {"shortcut_delete_line", "Ctrl+Shift+D"},
        {"shortcut_context_menu", "F2"},
        {"shortcut_focus_tree", "Alt+Down"},
        {"shortcut_open_file", "Ctrl+O"},
        {"shortcut_open_project", "Ctrl+Shift+O"},
        {"shortcut_new_file", "Ctrl+N"},
        {"shortcut_new_folder", "Ctrl+Shift+N"},
        {"shortcut_previous_tab", "Alt+Left"},
        {"shortcut_next_tab", "Alt+Right"},
        {"shortcut_tabs_list", "Alt+Up"},
        {"shortcut_close_tab", "Ctrl+Q"},
        {"shortcut_close_project", "Ctrl+Shift+Q"},
        {"shortcut_close_app", "Ctrl+Alt+Q"},
        {"experimental_mode_enabled", "yes"},
        {"spellchecker_enabled", "yes"},
        {"show_dock_buttons", "yes"},
        {"color_scheme", COLOR_SCHEME_DARK.toStdString()},
        {"theme", THEME_DARK.toStdString()},
        {"custom_themes_path", ""},
        {"plugins_path", ""}
    };
}

void Settings::applyLightColors()
{
    data[COLOR_SCHEME_TYPE.toStdString()] = COLOR_SCHEME_LIGHT.toStdString();
    data["editor_line_number_bg_color"] = "#eeeeee";
    data["editor_line_number_color"] = "#999999";
    data["editor_line_number_modified_bg_color"] = "#bdf1ad";
    data["editor_line_number_modified_color"] = "#555555";
    data["editor_line_number_deleted_border_color"] = "#ff4614";
    data["editor_line_mark_bg_color"] = "#eeeeee";
    data["editor_line_map_bg_color"] = "#f5f5f5";
    data["editor_line_map_scroll_bg_color"] = "#e2e1f9";
    data["editor_line_map_scroll_area_bg_color"] = "#eaf5d9";
    data["editor_search_bg_color"] = "#e7e6f1";
    data["editor_breadcrumbs_bg_color"] = "#daecf5";
    data["editor_breadcrumbs_warning_bg_color"] = "#fff083";
    data["editor_breadcrumbs_error_bg_color"] = "#ff83ab";
    data["editor_breadcrumbs_color"] = "#335667";
    data["editor_widget_border_color"] = "#98c6ff";
    data["editor_selected_line_bg_color"] = "#fef8ff";
    data["editor_selected_word_bg_color"] = "#fffac7";
    data["editor_selected_char_bg_color"] = "#c1ffba";
    data["editor_selected_char_color"] = "#3e0009";
    data["editor_selected_tag_bg_color"] = "#ecffbd";
    data["editor_selected_expression_bg_color"] = "#ecffbd";
    data["editor_search_word_bg_color"] = "#a800ff";
    data["editor_search_word_color"] = "#ffffff";
    data["editor_text_color"] = "#333333";
    data["editor_bg_color"] = "#ffffff";
    data["editor_tooltip_border_color"] = "#d0cec1";
    data["editor_tooltip_bg_color"] = "#fffded";
    data["editor_tooltip_color"] = "#4c4c4c";
    data["editor_tooltip_bold_color"] = "#000000";
    data["editor_search_input_bg_color"] = "#ffffff";
    data["editor_search_input_error_bg_color"] = "#ff8181";
    data["editor_line_mark_color"] = "#00b727";
    data["editor_line_error_color"] = "#ec1212";
    data["editor_line_warning_color"] = "#ec9f12";
    data["editor_line_mark_rect_color"] = "#00b78e";
    data["editor_line_error_rect_color"] = "#e03333";
    data["editor_line_warning_rect_color"] = "#fbd99a";
    data["highlight_keyword_color"] = "#376092";
    data["highlight_class_color"] = "#790070";
    data["highlight_function_color"] = "#00756f";
    data["highlight_known_function_color"] = "#380075";
    data["highlight_variable_color"] = "#005cab";
    data["highlight_known_variable_color"] = "#8a051e";
    data["highlight_unused_variable_color"] = "#6f735b";
    data["highlight_single_line_comment_color"] = "#9c9c9c";
    data["highlight_multi_line_comment_color"] = "#8c986e";
    data["highlight_string_color"] = "#008e1f";
    data["highlight_tag_color"] = "#004973";
    data["highlight_tag_name_color"] = "#795400";
    data["highlight_php_tag_color"] = "#c11b49";
    data["highlight_selector_color"] = "#35016d";
    data["highlight_selector_tag_color"] = "#003380";
    data["highlight_property_color"] = "#3e6500";
    data["highlight_pseudo_class_color"] = "#003eaf";
    data["highlight_css_special_color"] = "#c10000";
    data["highlight_known_color"] = "#800064";
    data["highlight_expression_color"] = "#6100ab";
    data["highlight_space_color"] = "#000000";
    data["highlight_tab_color"] = "#cecece";
    data["highlight_punctuation_color"] = "#005cab";
    data["messages_error_color"] = "#bd0606";
    data["messages_warning_color"] = "#006b37";
    data["search_results_color"] = "#314d5d";
    data["output_color"] = "#333333";
    data["output_bg_color"] = "#ffffff";
    data["git_output_error_color"] = "#b10814";
    data["git_output_message_color"] = "#00842f";
    data["git_output_info_color"] = "#005384";
    data["popup_bg_color"] = "#7aedc8";
    data["popup_error_bg_color"] = "#ffb5af";
    data["popup_color"] = "#092c21";
    data["annotation_color"] = "#8f8576";
    data["progress_color"] = "#25b9ff";
}

void Settings::applyDarkColors()
{
    data[COLOR_SCHEME_TYPE.toStdString()] = COLOR_SCHEME_DARK.toStdString();
    data["editor_line_number_bg_color"] = "#232627";
    data["editor_line_number_color"] = "#555555";
    data["editor_line_number_modified_bg_color"] = "#093833";
    data["editor_line_number_modified_color"] = "#999999";
    data["editor_line_number_deleted_border_color"] = "#ba1205";
    data["editor_line_mark_bg_color"] = "#232627";
    data["editor_line_map_bg_color"] = "#232627";
    data["editor_line_map_scroll_bg_color"] = "#441b33";
    data["editor_line_map_scroll_area_bg_color"] = "#262635";
    data["editor_search_bg_color"] = "#232627";
    data["editor_breadcrumbs_bg_color"] = "#314661";
    data["editor_breadcrumbs_warning_bg_color"] = "#3f3533";
    data["editor_breadcrumbs_error_bg_color"] = "#1d181a";
    data["editor_breadcrumbs_color"] = "#9fc4d6";
    data["editor_widget_border_color"] = "#15365f";
    data["editor_selected_line_bg_color"] = "#1f1d23";
    data["editor_selected_word_bg_color"] = "#422a58";
    data["editor_selected_char_bg_color"] = "#65b544";
    data["editor_selected_char_color"] = "#000000";
    data["editor_selected_tag_bg_color"] = "#335d5f";
    data["editor_selected_expression_bg_color"] = "#5f3353";
    data["editor_search_word_bg_color"] = "#ea0053";
    data["editor_search_word_color"] = "#ffffff";
    data["editor_text_color"] = "#a5a9ad";
    data["editor_bg_color"] = "#0f0f10";
    data["editor_tooltip_border_color"] = "#232627";
    data["editor_tooltip_bg_color"] = "#194067";
    data["editor_tooltip_color"] = "#c4c8cc";
    data["editor_tooltip_bold_color"] = "#ffffff";
    data["editor_search_input_bg_color"] = "#3a4a50";
    data["editor_search_input_error_bg_color"] = "#710044";
    data["editor_line_mark_color"] = "#30ffaa";
    data["editor_line_error_color"] = "#ff2b2b";
    data["editor_line_warning_color"] = "#ffbf4a";
    data["editor_line_mark_rect_color"] = "#30ffaa";
    data["editor_line_error_rect_color"] = "#ff2b2b";
    data["editor_line_warning_rect_color"] = "#ffbf4a";
    data["highlight_keyword_color"] = "#6b76ff";
    data["highlight_class_color"] = "#ae63ff";
    data["highlight_function_color"] = "#00b7ae";
    data["highlight_known_function_color"] = "#1071ff";
    data["highlight_variable_color"] = "#05aeff";
    data["highlight_known_variable_color"] = "#ffb341";
    data["highlight_unused_variable_color"] = "#858871";
    data["highlight_single_line_comment_color"] = "#5d5d5d";
    data["highlight_multi_line_comment_color"] = "#6c7556";
    data["highlight_string_color"] = "#5faf22";
    data["highlight_tag_color"] = "#009df7";
    data["highlight_tag_name_color"] = "#bf8500";
    data["highlight_php_tag_color"] = "#f36f21";
    data["highlight_selector_color"] = "#9f49fd";
    data["highlight_selector_tag_color"] = "#3585fd";
    data["highlight_property_color"] = "#03d269";
    data["highlight_pseudo_class_color"] = "#1366ff";
    data["highlight_css_special_color"] = "#ec3a3a";
    data["highlight_known_color"] = "#fb6984";
    data["highlight_expression_color"] = "#00a5cc";
    data["highlight_space_color"] = "#888888";
    data["highlight_tab_color"] = "#333333";
    data["highlight_punctuation_color"] = "#00a5cc";
    data["messages_error_color"] = "#f12d2d";
    data["messages_warning_color"] = "#0c9c5d";
    data["search_results_color"] = "#4495c3";
    data["output_color"] = "#c4c8cc";
    data["output_bg_color"] = "#0f0f10";
    data["git_output_error_color"] = "#fb1727";
    data["git_output_message_color"] = "#05d24e";
    data["git_output_info_color"] = "#0483ce";
    data["popup_bg_color"] = "#2d6099";
    data["popup_error_bg_color"] = "#992d93";
    data["popup_color"] = "#f1f1f1";
    data["annotation_color"] = "#5e839b";
    data["progress_color"] = "#0076af";
}

void Settings::applyCustomColors(QString path)
{
    QString s, k, v;
    QFile f(path);
    f.open(QIODevice::ReadOnly);
    QTextStream in(&f);
    while (!in.atEnd()) {
        s = in.readLine();
        if (s.size() == 0 || s.indexOf("=") < 0) continue;
        k = s.mid(0, s.indexOf("=")).trimmed();
        v = s.mid(s.indexOf("=")+1).trimmed();
        if (k.size() == 0 || v.size() == 0) continue;
        if (!QColor::isValidColor(v) && v != COLOR_SCHEME_LIGHT && v != COLOR_SCHEME_DARK) continue;
        data[k.toStdString()] = v.toStdString();
    }
    f.close();
}

void Settings::set(std::string k, std::string v)
{
    data[k] = v;
}

std::string Settings::get(std::string k)
{
    iterator = data.find(k);
    if (iterator == data.end()) return "";
    std::string v = iterator->second;
    return v;
}

void Settings::load()
{
    QSettings windowSettings;
    for (auto it : data) {
        if (!windowSettings.contains(QString::fromStdString(it.first))) continue;
        QVariant v = windowSettings.value(QString::fromStdString(it.first), QString::fromStdString(it.second));
        set(it.first, v.toString().toStdString());
    }
}

void Settings::change(std::unordered_map<std::string, std::string> map)
{
    for (auto it : map) {
        set(it.first, it.second);
        changesData[it.first] = it.second;
    }
}

void Settings::save()
{
    QSettings windowSettings;
    for (auto it : changesData) {
        set(it.first, it.second);
        windowSettings.setValue(QString::fromStdString(it.first), QString::fromStdString(it.second));
    }
}

void Settings::reset()
{
    QSettings windowSettings;
    for (auto it : data) {
        if (!windowSettings.contains(QString::fromStdString(it.first))) continue;
        windowSettings.remove(QString::fromStdString(it.first));
    }
}
