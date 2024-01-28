/* date = January 29th 2021 9:37 pm */

#ifndef FCODER_FLEURY_LANG_LIST_H
#define FCODER_FLEURY_LANG_LIST_H

// NOTE(rjf): Include language files here.
#include "4coder_fleury_lang_cpp.cpp"
#include "4coder_fleury_lang_metadesk.cpp"

// NOTE(rjf): @f4_register_languages Register languages.
function void
F4_RegisterLanguages(void)
{
    // NOTE(rjf): C/C++
    {
        String_Const_u8 extensions[] =
        {
            S8Lit("cpp"), S8Lit("cc"), S8Lit("c"), S8Lit("cxx"),
            S8Lit("C"), S8Lit("h"), S8Lit("hpp"),
        };
        for(int i = 0; i < ArrayCount(extensions); i += 1)
        {
            F4_RegisterLanguage(extensions[i],
                                F4_CPP_IndexFile,
                                lex_full_input_cpp_init,
                                lex_full_input_cpp_breaks,
                                F4_CPP_PosContext,
                                F4_CPP_Highlight,
                                Lex_State_Cpp);
        }
    }
    
    // NOTE(rjf): Metadesk
    {
        String_Const_u8 extensions[] =
        {
            // TODO(rjf): Maybe find a config-driven way to specify these? "mc" was sort of
            // introduced ad-hoc...
            S8Lit("md"), S8Lit("mc"), S8Lit("metacode"), S8Lit("meta"), S8Lit("metadesk"),
        };
        for(int i = 0; i < ArrayCount(extensions); i += 1)
        {
            F4_RegisterLanguage(extensions[i],
                                F4_MD_IndexFile,
                                lex_full_input_cpp_init,
                                lex_full_input_cpp_breaks,
                                F4_MD_PosContext,
                                F4_MD_Highlight,
                                Lex_State_Cpp);
        }
    }
}

#endif //FCODER_FLEURY_LANG_LIST_H
