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
        m_json_fstring_ref += ___object_whitespace_after_comma;
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

    return retVal;
}

sub_array_creator sub_object_creator::append_array(std::string_view in_key)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value(in_key);
    sub_array_creator retVal(m_json_fstring_ref, m_level+1);

    return retVal;
}

// add a value that is already formated as json
void sub_object_creator::append_json_str(const std::string_view in_key, const std::string_view in_value)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value(in_key);
    m_json_fstring_ref += in_value;
}

// add a value that is already formated as json to the begening of the object
// Warning: less efficient than append_json_str!
void sub_object_creator::prepend_json_str(const std::string_view in_key, const std::string_view in_value)
{
    size_t num_additional_chars{0};
    num_additional_chars += 1;  // '"'
    num_additional_chars += in_key.size();
    num_additional_chars += internal::_KEY_VAL_SEP.size();
    num_additional_chars += in_value.size();
    if (0 < m_num_subs) {  // not first, need to add ','
        num_additional_chars += internal::_COMMA.size();
        num_additional_chars += ___object_whitespace_after_comma.size();
    }
    m_json_fstring_ref.insert(1, num_additional_chars, '*');

    size_t replacement_location{1};
    m_json_fstring_ref[replacement_location] = '"';
    ++replacement_location;
    m_json_fstring_ref.replace(replacement_location, in_key);
    replacement_location += in_key.size();

    m_json_fstring_ref.replace(replacement_location, internal::_KEY_VAL_SEP);
    replacement_location += internal::_KEY_VAL_SEP.size();

    m_json_fstring_ref.replace(replacement_location, in_value);
    replacement_location += in_value.size();

    if (0 < m_num_subs) {  // not first, need to add ','
        m_json_fstring_ref.replace(replacement_location, internal::_COMMA);
        replacement_location += internal::_COMMA.size();
        m_json_fstring_ref.replace(replacement_location, ___object_whitespace_after_comma);
    }
    ++m_num_subs;
}

void sub_object_creator::append_values_from(const sub_object_creator& in_to_merge_from)
{
    std::string_view values_to_merge(in_to_merge_from.m_json_fstring_ref.data()+1,                                                  in_to_merge_from.m_json_fstring_ref.size()-2);
    if (! values_to_merge.empty())
    {
        json_creator_base::save_restore_end sv(*this);
        if (0 < m_num_subs) {  // not first, need to add ','
            m_json_fstring_ref += internal::_COMMA;
            m_json_fstring_ref += ___object_whitespace_after_comma;
        }
        m_json_fstring_ref.insert(m_json_fstring_ref.size(), values_to_merge);
        ++m_num_subs;
    }
}

void sub_object_creator::prepend_values_from(const sub_object_creator& in_to_merge_from)
{
    std::string_view values_to_merge(in_to_merge_from.m_json_fstring_ref.data()+1,                                                  in_to_merge_from.m_json_fstring_ref.size()-2);
    if (! values_to_merge.empty())
    {
        size_t num_additional_chars{values_to_merge.size()};
        if (0 < m_num_subs) {  // not first, need to add ','
            num_additional_chars += internal::_COMMA.size();
            num_additional_chars += ___object_whitespace_after_comma.size();
        }
        m_json_fstring_ref.insert(1, num_additional_chars, '*');

        size_t replacement_location{1};
        m_json_fstring_ref.replace(replacement_location, values_to_merge);
        replacement_location += values_to_merge.size();
        if (0 < m_num_subs) {
            m_json_fstring_ref.replace(replacement_location, internal::_COMMA);
            replacement_location += internal::_COMMA.size();
            m_json_fstring_ref.replace(replacement_location, ___object_whitespace_after_comma);
        }
        ++m_num_subs;
    }
}


void sub_array_creator::prepare_for_additional_value()
{
    if (0 < m_num_subs) {  // not first, need to add ','
        m_json_fstring_ref += internal::_COMMA;
        m_json_fstring_ref += ___array_whitespace_after_comma;
    }
    ++m_num_subs;
}

sub_array_creator sub_array_creator::append_array()
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    sub_array_creator retVal(m_json_fstring_ref, m_level+1);

    return retVal;
}

sub_object_creator sub_array_creator::append_object()
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    sub_object_creator retVal(m_json_fstring_ref, m_level+1);

    return retVal;
}


// add a value that is already formated as json to the end of the array
void sub_array_creator::append_json_str(const std::string_view in_value)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    m_json_fstring_ref += in_value;
}

// add a value that is already formated as json to the beginning of the array
void sub_array_creator::prepend_json_str(const std::string_view in_value)
{
    size_t num_additional_chars{in_value.size()};
    if (0 < m_num_subs) {  // not first, need to add ','
        num_additional_chars += internal::_COMMA.size();
        num_additional_chars += ___array_whitespace_after_comma.size();
    }
    m_json_fstring_ref.insert(1, num_additional_chars, '*');

    size_t replacement_location{1};

    m_json_fstring_ref.replace(replacement_location, in_value);
    replacement_location += in_value.size();

    if (0 < m_num_subs) {  // not first, need to add ','
        m_json_fstring_ref.replace(replacement_location, internal::_COMMA);
        replacement_location += internal::_COMMA.size();
        m_json_fstring_ref.replace(replacement_location, ___array_whitespace_after_comma);
    }
    ++m_num_subs;
}

void sub_array_creator::append_value(const char* in_value)
{
    typename sub_array_creator::save_restore_end sv(*this);
    prepare_for_additional_value();
    internal::write_value(in_value, m_json_fstring_ref);
}


void sub_array_creator::append_values_from(const sub_array_creator& in_to_merge_from)
{
    std::string_view values_to_merge(in_to_merge_from.m_json_fstring_ref.data()+1,                                                  in_to_merge_from.m_json_fstring_ref.size()-2);
    if (! values_to_merge.empty())
    {
        json_creator_base::save_restore_end sv(*this);
        if (0 < m_num_subs) {  // not first, need to add ','
            m_json_fstring_ref += internal::_COMMA;
            m_json_fstring_ref += ___array_whitespace_after_comma;
        }
        m_json_fstring_ref.insert(m_json_fstring_ref.size(), values_to_merge);
        ++m_num_subs;
    }
}

void sub_array_creator::prepend_values_from(const sub_array_creator& in_to_merge_from)
{
    std::string_view values_to_merge(in_to_merge_from.m_json_fstring_ref.data()+1,                                                  in_to_merge_from.m_json_fstring_ref.size()-2);
    if (! values_to_merge.empty())
    {
        size_t num_additional_chars{values_to_merge.size()};
        if (0 < m_num_subs) {  // not first, need to add ','
            num_additional_chars += internal::_COMMA.size();
            num_additional_chars += ___array_whitespace_after_comma.size();
        }
        m_json_fstring_ref.insert(1, num_additional_chars, '*');

        size_t replacement_location{1};
        m_json_fstring_ref.replace(replacement_location, values_to_merge);
        replacement_location += values_to_merge.size();
        if (0 < m_num_subs) {
            m_json_fstring_ref.replace(replacement_location, internal::_COMMA);
            replacement_location += internal::_COMMA.size();
            m_json_fstring_ref.replace(replacement_location, ___array_whitespace_after_comma);
        }
        ++m_num_subs;
    }
}

}
