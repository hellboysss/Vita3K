// Vita3K emulator project
// Copyright (C) 2018 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <gui/functions.h>
#include <imgui.h>

#include <gui/gui_constants.h>
#include <host/state.h>
#include <kernel/thread/thread_functions.h>
#include <kernel/thread/thread_state.h>

#include <util/fs.h>
#include <util/resource.h>

#include <pugixml.hpp>

#include <string>

bool ShouldRenderLivearea(HostState &host) {
    if (host.gui.game_selector.selected_title_id.empty()) {
        return false;
    }

    if ((!host.gui.livearea.cached) || (host.gui.game_selector.selected_title_id != host.gui.livearea.last_cached_id)) {
        host.gui.livearea.last_cached_id = host.gui.game_selector.selected_title_id;

        const std::string livearea_content_dir = host.pref_path + "ux0\\app\\" + host.gui.livearea.last_cached_id + "\\sce_sys\\livearea\contents\\";

        // We should see if we can get the template file
        const std::string livearea_template_xml = livearea_content_dir + "template.xml";

        bool should_render_background = false;

        if (!fs::exists(livearea_template_xml)) {
            return false;
        }

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(livearea_template_xml.c_str());
        pugi::xml_node livearea_node = doc.child("livearea");

        if (!livearea_node) {
            return false;
        }

        host.gui.livearea.background_path = livearea_node.child("livearea-background").attribute("image").value();

        host.gui.livearea.cached = true;
        host.gui.livearea.should_render = true;
    }

    return host.gui.livearea.should_render;
}

void DrawLivearea(HostState &host) {
    host.gui.livearea.should_render = ShouldRenderLivearea(host);
}