#include "json_creator.h"


namespace fixed
{

json_creator_base::save_restore_end::save_restore_end(json_creator_base& to_save) noexcept
: m_creator_to_save(to_save)
{
    std::string_view end_to_save = m_creator_to_save.save_end();
    std::memcpy(m_save_buf,
                end_to_save.data(),
                end_to_save.size());
    to_save.m_json_fstring_ref.resize(to_save.m_json_fstring_ref.size()-end_to_save.size());
    m_saved_end_chars = std::string_view(m_save_buf, end_to_save.size());
}


json_creator_base::save_restore_end::~save_restore_end()
{
    m_creator_to_save.m_json_fstring_ref += m_saved_end_chars;
}


std::string_view json_creator_base::save_end()
{
    return std::string_view(m_json_fstring_ref.data()+m_json_fstring_ref.size()-m_level-1, m_level+1);
}


void json_creator_base::restore_end(std::string_view in_end)
{
    m_json_fstring_ref += in_end;
}


void sub_object_creator::prepare_for_additional_value(const std::string_view in_key)
{
    if (0 < m_num_subs) {  // not first, need to add ','
        m_json_fstring_ref += internal::_COMMA;
        m_json_fstring_ref += m_object_whitespace_after_comma;
    }
    ++m_num_subs;

    m_json_fstring_ref += '"';
    m_json_fstring_ref += in_key;
    m_json_fstring_ref += internal::_KEY_VAL_SEP;
}


sub_object_creator sub_object_creator::append_object(std::string_view in_key)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value(in_key);
    sub_object_creator retVal(m_json_fstring_ref, m_level+1);
    retVal.set_array_whitespace_after_comma(m_array_whitespace_after_comma);
    retVal.set_object_whitespace_after_comma(m_object_whitespace_after_comma);

    return retVal;
}

sub_array_creator sub_object_creator::append_array(std::string_view in_key)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value(in_key);
    sub_array_creator retVal(m_json_fstring_ref, m_level+1);
    retVal.set_array_whitespace_after_comma(m_array_whitespace_after_comma);
    retVal.set_object_whitespace_after_comma(m_object_whitespace_after_comma);

    return retVal;
}

// add a value that is already formated as json

void sub_object_creator::push_json_str(const std::string_view in_key, const std::string_view in_value)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value(in_key);
    m_json_fstring_ref += in_value;
}


void sub_array_creator::prepare_for_additional_value()
{
    if (0 < m_num_subs) {  // not first, need to add ','
        m_json_fstring_ref += internal::_COMMA;
        m_json_fstring_ref += m_array_whitespace_after_comma;
    }
    ++m_num_subs;
}

sub_array_creator sub_array_creator::append_array()
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    sub_array_creator retVal(m_json_fstring_ref, m_level+1);
    retVal.set_array_whitespace_after_comma(m_array_whitespace_after_comma);
    retVal.set_object_whitespace_after_comma(m_object_whitespace_after_comma);

    return retVal;
}

sub_object_creator sub_array_creator::append_object()
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    sub_object_creator retVal(m_json_fstring_ref, m_level+1);
    retVal.set_array_whitespace_after_comma(m_array_whitespace_after_comma);
    retVal.set_object_whitespace_after_comma(m_object_whitespace_after_comma);

    return retVal;
}


// add a value that is already formated as json
void sub_array_creator::push_json_str(const std::string_view in_value)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    m_json_fstring_ref += in_value;
}

void sub_array_creator::append_value(const char* in_value)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    internal::write_value(in_value, m_json_fstring_ref);
}

}
