
function show_menu(name, entries)

    local function draw(selected)
        -- Render title
        render_text(0, 0, name, style.headline)

        -- Render entries (maybe more abstract later)
        for i, entry in ipairs(entries) do
            if i == selected then
                render_text(0, 0.1 * i, entry[1], style.selected)
            else
                render_text(0, 0.1 * i, entry[1], style.normal)
            end
        end
    end

    local selected = 1
    
    while true do
        draw(selected)
        local key = key:pressed()

        if key == keys.enter then
            return entries[selected][2]()
        elseif key == keys.up then
            -- Lua starts indexing with 1
            selected = selected % #entries + 1
        elseif key == keys.down then
            if selected == 1 then
                selected = #entries
            else
                selected = selected - 1
            end
        end
    end
end


show_menu(
    "Star",
    {
         {"Sing", function() screen:start("singing") end},
         {"Quit", function() screen:return_() end}
    }
)

