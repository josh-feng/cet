#!/usr/bin/env lua
-- design -- widget
-- {
--     -- required
--     ['.'] = gui.Window; w = 10; h = 10; -- minw = 0; minh = 0;
--     label = ''; -- font/size/color
--
--     -- optional
--     box = 'up'; -- decoration
--     bg = color or image (tile)
--     align = gui.North, gui.East, gui.West, gui.South -- gui.Grid
--        + enda, mid, endb (cw)
--     scale = 0; -- false/no, 0/scale, 1/center; 2/scroll-bar
--     shortcut = ''; -- activate
--     callback = { func, pdata, ...
--          [''] = { func, pdata, ... } -- event : true for default act
--          shift/control/alt
--          mouse-left/mouse-right/mouse-middle
--     };
--     sub = {}; -- sub/extended class
--
--     {...}; -- sub-widget
--     {...}; -- sub-widget
-- }
local class = require 'pool'
local strfind, strsub, strmatch = string.find, string.sub, string.match
local tpack, tunpack, tinsert = table.pack, table.unpack, table.insert

local fl = require 'moonfltk' -- local (network:html)

local common = { -- common/basic widget {{{
    -- widget (sub) moonFLTK
    -- ├─ box (sub)
    -- ├─ button (sub)
    -- │   ├─ light_button
    -- │   │   ├─ check_button
    -- │   │   ├─ radio_light_button
    -- │   │   └─ round_button
    -- │   │       └─ radio_round_button
    -- │   ├─ radio_button
    -- │   ├─ repeat_button
    -- │   ├─ return_button
    -- │   └─ toggle_button
    -- ├─ chart
    -- ├─ clock_output
    -- │   └─ clock
    -- │       └─ round_clock
    -- ├─ group (sub)
    -- │   ├─ browser_
    -- │   │   ├─ browser (sub)
    -- │   │   │   ├─ file_browser
    -- │   │   │   ├─ hold_browser
    -- │   │   │   ├─ multi_browser
    -- │   │   │   └─ select_browser
    -- │   │   └─ check_browser
    -- │   ├─ color_chooser
    -- │   ├─ help_view
    -- │   ├─ input_choice
    -- │   ├─ pack
    -- │   ├─ scroll
    -- │   ├─ spinner
    -- │   ├─ table (sub)
    -- │   │   └─ table_row (sub)
    -- │   ├─ tabs (sub)
    -- │   ├─ text_display
    -- │   │   └─ text_editor
    -- │   ├─ tile
    -- │   ├─ tree
    -- │   ├─ window (sub)
    -- │   │   ├─ double_window (sub)
    -- │   │   │   └─ overlay_window (sub)
    -- │   │   ├─ gl_window (sub)
    -- │   │   └─ single_window (sub)
    -- │   │       └─ menu_window (sub)
    -- │   └─ wizard
    -- ├─ input_
    -- │   └─ input
    -- │       ├─ file_input
    -- │       ├─ float_input
    -- │       ├─ int_input
    -- │       ├─ multiline_input
    -- │       ├─ output
    -- │       │   └─ multiline_output
    -- │       └─ secret_input
    -- ├─ menu_
    -- │   ├─ choice
    -- │   ├─ menu_bar
    -- │   └─ menu_button
    -- ├─ progress
    -- └─ valuator
    --     ├─ adjuster
    --     ├─ counter
    --     │   └─ simple_counter
    --     ├─ dial
    --     │   ├─ fill_dial
    --     │   └─ line_dial
    --     ├─ roller (sub)
    --     ├─ slider (sub)
    --     │   ├─ fill_slider
    --     │   ├─ hor_fill_slider
    --     │   ├─ hor_nice_slider
    --     │   ├─ hor_slider
    --     │   ├─ nice_slider
    --     │   ├─ scrollbar
    --     │   └─ value_slider
    --     │       └─ hor_value_slider
    --     ├─ value_input
    --     └─ value_output
} -- }}}

local gui = { -- {{{
    sub = ' widget box button group browser table_row tabs '..
          ' window double_window overlay_window gl_window '..
          ' single_window menu_window roller slider ';
    BOLD   = fl.BOLD;
    ITALIC = fl.ITALIC;
} -- }}}

gui.font = { -- {{{
    -- 'FL_HELVETICA_BOLD_ITALIC';
    -- gui.BOLD;
    -- gui.ITALIC;
} -- }}}

gui.color = { -- alias {{{
} -- }}}

gui.widget = { -- alias {{{
} -- }}}

gui.new = class { -- {{{
    ['.'] = 'widget'; -- basic widget
    ['*'] = false; -- proxy

    -- align = false;
    -- when = false;
    -- shortcut = false;
    -- derived class method fltk
    -- position = function (o, x, y) o['*']:position(x, y) end;
    -- size = function (o, w, h) o['*']:size(w, h) end;
    -- resize = function (o, x, y, w, h) o['*']:resize(x, y, w, h) end;

    add = function (o, ...)
    end;

    insert = function (o, ...)
    end;

    redraw = function (o) o['*']:redraw() end;

    --
    sub_draw   = function (o, f) o['*']:override_draw(f)   end;
    sub_handle = function (o, f) o['*']:override_handle(f) end;
    sub_hide   = function (o, f) o['*']:override_hide(f)   end;
    sub_resize = function (o, f) o['*']:override_resize(f) end;

    show = function (o, ...) o['*']:show(...) end;

    callback = function (o, t) -- setting callback/events {{{
        local arg = {} -- replacing w/ proxy
        for i = 1, #t do arg[i] = type(t[i]) == 'table' and t[i]['*'] or t[i] end
        if type(arg[1]) == 'function' then o['*']:callback(tunpack(arg)) end
    end; -- }}}

    do_callback = function (o, ...) -- {{{
        local arg = {} -- replacing w/ proxy
        for _, v in ipairs(tpack(...)) do tinsert(arg, type(v) == 'table' and v['*'] or v) end
        o['*']:do_callback(tunpack(arg))
    end; -- }}}

    add = function (o, s) o['*']:add(s['*']) end;

    ['<'] = function (o, wgt) -- {{{
        if type(wgt) ~= 'table' then error('Widget spec: '..tostring(wgt), 2) end
        local basic = (gui.widget[wgt['.']] or wgt['.'])

        -- sub/derived/extend class
        if wgt.sub and strfind(gui.sub, ' '..basic..' ') then basic = basic..'_sub' end

        local proxy = fl[basic](wgt.x or 0, wgt.y or 0, wgt.w or 100, wgt.h or 100, wgt.label or basic)
        o['.'], o['*'] = basic, proxy

        if wgt.labelfont  then proxy:labelfont(wgt.labelfont) end
        if wgt.labelsize  then proxy:labelsize(wgt.labelsize) end
        if wgt.labeltype  then proxy:labeltype(wgt.labeltype) end
        if wgt.labelcolor then proxy:labelcolor(fl[gui.color[wgt.labelcolor] or wgt.labelcolor]) end
        --
        if wgt.bg  then proxy:color(fl[gui.color[wgt.bg] or wgt.bg]) end -- string:color, obj:image
        if wgt.box then proxy:box(wgt.box..' box') end
        -- if o.align then proxy.align(o.align) end

        -- sub
        if type(wgt.sub) == 'table' then
            if wgt.sub.draw   then o:sub_draw(wgt.sub.draw)     end
            if wgt.sub.handle then o:sub_handle(wgt.sub.handle) end
            if wgt.sub.hide   then o:sub_hide(wgt.sub.hide)     end
            if wgt.sub.resize then o:sub_resize(wgt.sub.resize) end
        end

        -- children widgets
        for i, g in ipairs(wgt) do o[i] = class:new(o, g) end

        -- if o.when then proxy.when(o.when) end
        -- if o.shortcut then proxy.shortcut(o.shortcut) end
        if type(wgt.act) == 'table' then o:callback(wgt.callback) end

        if #wgt > 0 then proxy:done() end
        -- if wgt.scale then proxy:resizable(proxy) end
    end; -- }}}

    { -- operator {{{
        __add = function (o1, o2) -- dock o2 to o1
            tinsert(o1.node, o2.node)
            return o1
        end;
        __tostring = function (o) return '('..o['.']..':'..o.label..')' end;
    } -- }}}
} -- }}}

--[[


local wb = gui.new -- workbench
{ ['.'] = 'double_window'; w = 300; h = 500; label = arg[0];
  { ['.'] = 'widget'; x = 10; y = 10; w = 280; h = 280; sub = true; }
  {}
}

name = { "X", "Y", "R", "start", "end", "rotate" }
args = { 140, 140, 50, 0, 360, 0 } -- initial value

wb[1]:sub_draw(function (wid) -- proxy
    local x, y, w, h = wid:xywh()
    fl.push_clip(x, y, w, h) -- double buffer? TODO

    fl.color(fl.DARK3)
    fl.rectf(x, y, w, h)

    fl.push_matrix()
    if args[6] ~= 0 then
       fl.translate(x+w/2, y+h/2)
       fl.rotate(args[6])
       fl.translate(-(x+w/2), -(y+h/2))
    end
    fl.color(fl.WHITE)
    fl.translate(x, y)
    fl.begin_complex_polygon()
    fl.arc(args[1], args[2], args[3], args[4], args[5])
    fl.gap()
    fl.arc(140, 140, 20, 0, -360)
    fl.end_complex_polygon()
    fl.color(fl.RED)

    fl.begin_line()
    fl.arc(args[1], args[2], args[3], args[4], args[5])
    fl.end_line()

    fl.pop_matrix()

    fl.pop_clip()
end)

y = 300

function slider_cb(slider, n)
   args[n] = slider:value()
   wb[1]:redraw()
end

{ ['.'] = 'hor_value_slider'; w = 50, y = y,       w = 240; h = 25, label = 'X';      v = {   0, 300}; }
{ ['.'] = 'hor_value_slider'; w = 50, y = y +  25, w = 240; h = 25, label = 'Y';      v = {   0, 300}; }
{ ['.'] = 'hor_value_slider'; w = 50, y = y +  50, w = 240; h = 25, label = 'R';      v = {   0, 300}; }
{ ['.'] = 'hor_value_slider'; w = 50, y = y + 100, w = 240; h = 25, label = 'start';  v = {-360, 360}; }
{ ['.'] = 'hor_value_slider'; w = 50, y = y + 125, w = 240; h = 25, label = 'end';    v = {-360, 360}; }
{ ['.'] = 'hor_value_slider'; w = 50, y = y + 150, w = 240; h = 25, label = 'rotate'; v = {   0, 360}; }

{ ['.'] = 'h_slider'; x = 50; y =  25; w = 240, h = 25; label = name[1]; what = {   0, 300}; act = {slider_cb, 1}; }
{ ['.'] = 'h_slider'; x = 50; y =  25; w = 240, h = 25; label = name[2]; what = {   0, 300}; act = {slider_cb, 2}; }
{ ['.'] = 'h_slider'; x = 50; y =  25; w = 240, h = 25; label = name[3]; what = {   0, 300}; act = {slider_cb, 3}; }
{ ['.'] = 'h_slider'; x = 50; y =  25; w = 240, h = 25; label = name[4]; what = {-360, 360}; act = {slider_cb, 4}; }
{ ['.'] = 'h_slider'; x = 50; y =  25; w = 240, h = 25; label = name[5]; what = {-360, 360}; act = {slider_cb, 5}; }
{ ['.'] = 'h_slider'; x = 50; y =  25; w = 240, h = 25; label = name[6]; what = {   0, 360}; act = {slider_cb, 6}; }

for n=1,6 do
   local s = fl.hor_value_slider(50, y, 240, 25, name[n])
   y = y + 25
   if n < 4 then
      s:minimum(0) s:maximum(300)
   elseif n == 6 then
      s:minimum(0) s:maximum(360)
   else
   end
  s:minimum(what[1])
  s:maximum(what[2])
  s:step(what[3] or 1)
  s:value(args[n])
  s:align('left')
  s:callback(slider_cb, n)
end

wb:show(arg[0], arg)
return fl.run()


-- menu widget
{ ['.'] = 'double_window';
  { ['.'] = 'Window'; };

  { ['.'] = 'Input'; };
  { ['.'] = 'Input'; };
  { ['.'] = 'Button'; };
  { ['.'] = 'Return_Button'; };
  { ['.'] = 'Button'; };


  { ['.'] = 'menu_bar'; }; -- ['.'] = 'Menu_Item';
    { "&File",              0, 0, 0, FL_SUBMENU },
      { "&New File",        0, (Fl_Callback *)new_cb },
      { "&Open File...",    FL_COMMAND + 'o', (Fl_Callback *)open_cb },
      { "&Insert File...",  FL_COMMAND + 'i', (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER },
      { "&Save File",       FL_COMMAND + 's', (Fl_Callback *)save_cb },
      { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
      { "New &View", FL_ALT + 'v', (Fl_Callback *)view_cb, 0 },
      { "&Close View", FL_COMMAND + 'w', (Fl_Callback *)close_cb, 0, FL_MENU_DIVIDER },
      { "E&xit", FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0 },
      { 0 },
    { "&Edit", 0, 0, 0, FL_SUBMENU },
      { "&Undo",       FL_COMMAND + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
      { "Cu&t",        FL_COMMAND + 'x', (Fl_Callback *)cut_cb },
      { "&Copy",       FL_COMMAND + 'c', (Fl_Callback *)copy_cb },
      { "&Paste",      FL_COMMAND + 'v', (Fl_Callback *)paste_cb },
      { "&Delete",     0, (Fl_Callback *)delete_cb },
      { 0 },
    { "&Search", 0, 0, 0, FL_SUBMENU },
      { "&Find...",       FL_COMMAND + 'f', (Fl_Callback *)find_cb },
      { "F&ind Again",    FL_COMMAND + 'g', find2_cb },
      { "&Replace...",    FL_COMMAND + 'r', replace_cb },
      { "Re&place Again", FL_COMMAND + 't', replace2_cb },
      { 0 },
    { 0 }
  };
--]]
-- return gui
-- vim: ts=4 sw=4 sts=4 et foldenable fdm=marker fmr={{{,}}} fdl=1
