#ifndef GSP_HOOKS_INCLUDE_H
#define GSP_HOOKS_INCLUDE_H

enum F4_RangeHighlightKind
{
    F4_RangeHighlightKind_Whole,
    F4_RangeHighlightKind_Underline,
    F4_RangeHighlightKind_MinorUnderline,
};


internal void F4_TickColors(Application_Links *app, Frame_Info frame_info);
function void gsp_render(Application_Links *app, Frame_Info frame_info, View_ID view_id);


#endif //GSP_HOOKS_INCLUDE_H
