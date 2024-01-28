// NOTE(gsp): a lot of this stuff is based off of or just copied from 4coder_fleury
// NOTE(gsp): some files were just copy pasted from @rfj 's layer, wherever those
//            files were mofied I tagged them with '// NOTE(gsp): @rjf_mod'

//~ NOTE(gsp): 4coder includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "4coder_default_include.cpp"

//~ NOTE(gsp): [h] gsp layer includes
#include "4coder_gsp_common.h"
#include "4coder_gsp_bindings.h"
#include "4coder_gsp_hooks.h"

#include "4coder_gsp_common.cpp"

//~ NOTE(gsp): [h] @rjf layer includes
#include "4coder_fleury_index.h"
#include "4coder_fleury_colors.h"
#include "4coder_fleury_lang.h"
#include "4coder_fleury_brace.h"
#include "4coder_fleury_divider_comments.h"

//~ NOTE(gsp): [c] @rjf layer includes
#include "4coder_fleury_brace.cpp"
#include "4coder_fleury_lang.cpp"
#include "4coder_fleury_index.cpp"
#include "4coder_fleury_colors.cpp"
#include "4coder_fleury_divider_comments.cpp"

//~ NOTE(gsp): [c] gsp layer includes
#include "4coder_gsp_bindings.cpp"
#include "4coder_gsp_hooks.cpp"

//~ NOTE(gsp): 4coder generated includes
#include "generated/managed_id_metadata.cpp"


//~ NOTE(gsp): @gsp_custom_layer_init
void custom_layer_init(Application_Links *app)
{
    default_framework_init(app);
    global_frame_arena = make_arena(get_base_allocator_system());
    
    // NOTE(gsp): Hooks
    {
        set_all_default_hooks(app);
        set_custom_hook(app, HookID_Tick,         gsp_tick);
        set_custom_hook(app, HookID_RenderCaller, gsp_render);
    }
    
    // NOTE(gsp): mappings/bindings
    {
        Thread_Context *tctx = get_thread_context(app);
        mapping_init(tctx, &framework_mapping);
        gsp_setup_essential_mapping(&framework_mapping);
    }
    
    
    // NOTE(rjf): Set up custom code index.
    {
        F4_Index_Initialize();
    }
    
    // NOTE(rjf): Register languages.
    {
        F4_RegisterLanguages();
    }
}

CUSTOM_COMMAND_SIG(gsp_startup)
CUSTOM_DOC("GSP startup event")
{
    ProfileScope(app, "gsp startup");
    
    User_Input input = get_current_input(app);
    if(!match_core_code(&input, CoreCode_Startup))
    {
        return;
    }
    
    //~ NOTE(rjf): Default 4coder initialization.
    String_Const_u8_Array file_names = input.event.core.file_names;
    load_themes_default_folder(app);
    default_4coder_initialize(app, file_names);
    
    //~ NOTE(gsp): Open special buffers
    {
        
        // NOTE(gsp): compilation buffer
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*compilation*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
            buffer_set_setting(app, buffer, BufferSetting_ReadOnly, true);
        }
        
        // NOTE(gsp): home buffer
        {
            Buffer_ID buffer = create_buffer(app, string_u8_litexpr("*HOME*"),
                                             BufferCreate_NeverAttachToFile |
                                             BufferCreate_AlwaysNew);
            buffer_set_setting(app, buffer, BufferSetting_Unimportant, true);
            buffer_set_setting(app, buffer, BufferSetting_ReadOnly, true);
        }
    }
    
    //~ NOTE(gsp): init panels
    {
        Buffer_Identifier left  = buffer_identifier(string_u8_litexpr("*HOME*"));
        Buffer_Identifier right = buffer_identifier(string_u8_litexpr("*messages*"));
        Buffer_ID left_id = buffer_identifier_to_id(app, left);
        Buffer_ID right_id = buffer_identifier_to_id(app, right);
        
        // NOTE(gsp): left
        View_ID view = get_active_view(app, Access_Always);
        new_view_settings(app, view);
        view_set_buffer(app, view, left_id, 0);
        
        // NOTE(gsp): right
        open_panel_vsplit(app);
        View_ID right_view = get_active_view(app, Access_Always);
        view_set_buffer(app, right_view, right_id, 0);
        
        // NOTE(rjf): Restore Active to Left
        view_set_active(app, view);
    }
    
    //~ NOTE(rjf): Prep virtual whitespace.
    {
        def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
        clear_all_layouts(app);
    }
}