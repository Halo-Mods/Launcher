#pragma once

template<typename t_type, typename t_storage_type, size_t k_count>
struct c_flags
{
public:
	void set_raw_bits(t_storage_type raw_bits)
	{
		m_storage = raw_bits;
	}

	void set(t_type bit, bool enable)
	{
		if (bit < k_count)
		{
			if (enable)
				m_storage |= (1 << bit);
			else
				m_storage &= ~(1 << bit);
		}
	}

	bool valid_bit(t_type bit)
	{
		return VALID_INDEX(0, k_count);
	}

	bool test(t_type bit)
	{
		//assert(valid_bit(bit));
		return TEST_BIT(m_storage, bit);
	}

	bool operator==(t_type value)
	{
		return !!(m_storage & (1 << value));
	}

	template <class T>
	void operator= (T value)
	{
		m_storage = static_cast<t_storage_type>(value);
	}

	template <class T>
	operator T () const
	{
		return static_cast<T>(m_storage);
	}

protected:
	t_storage_type m_storage;
};

template<size_t k_bit_count>
struct c_static_flags
{
	uint32_t m_storage[(k_bit_count / 8) / sizeof(uint32_t)];
};
