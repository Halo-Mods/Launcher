#pragma once

template<long k_maximum_count>
struct c_static_string
{
public:
	c_static_string() :
		m_string{}
	{
	}

	void set(char const* s)
	{
		csstrnzcpy(m_string, s, k_maximum_count);
	}

	void append(char const* s)
	{
		csstrnzcat(m_string, s, k_maximum_count);
	}

	char const* print(char const* format, ...)
	{
		va_list list;
		va_start(list, format);

		cvsnzprintf(m_string, k_maximum_count, format, list);

		va_end(list);

		return m_string;
	}

	char const* vprint(char const* format, va_list list)
	{
		cvsnzprintf(m_string, k_maximum_count, format, list);

		return m_string;
	}

	char const* append_print(char const* format, ...)
	{
		va_list list;
		va_start(list, format);

		char const* result = append_vprint(format, list);

		va_end(list);
		return result;
	}

	char const* append_vprint(char const* format, va_list list)
	{
		size_t current_length = length();

		//assert(format);
		//assert(current_length >= 0 && current_length < k_maximum_count);

		cvsnzprintf(m_string + current_length, k_maximum_count - current_length, format, list);

		return m_string;
	}

	void clear()
	{
		csmemset(m_string, 0, sizeof(m_string));
	}

	char const* get_string() const
	{
		return m_string;
	}

	size_t length() const
	{
		return csstrnlen(m_string, k_maximum_count);
	}

	bool starts_with(char const* _string) const
	{
		//assert(_string);

		return csmemcmp(_string, get_string(), length()) == 0;
	}

	size_t next_index_of(char const* _string, size_t index) const
	{
		//assert(_string);

		size_t result = -1;

		if (index < length())
		{
			char const* s = csstrstr(m_string + index, _string);
			if (s)
				result = s - get_string();
		}

		return result;
	}

	size_t index_of(char const* _string) const
	{
		//assert(_string);

		return next_index_of(_string, 0);
	}

	void set_bounded(char const* _string, size_t _length)
	{
		if (_length + 1 < k_maximum_count)
			_length++;
		else
			_length = k_maximum_count;

		csstrnzcpy(m_string, _string, _length);
	}

	bool substring(size_t index, size_t _length, c_static_string<k_maximum_count>& s) const
	{
		if (index < 0 || _length <= 0 || index + _length > length())
			return false;

		s.set_bounded(get_string() + index, _length);

		return true;
	}

protected:
	char m_string[k_maximum_count];
};
