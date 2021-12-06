#pragma once

#include "Game.h"

class Ref
{
public:
	Ref();
	virtual ~Ref();

protected:
	int		m_iRef;
	string	m_strTag;

public:
	void AddRef()
	{
		++m_iRef;
	}

	int Release()
	{
		--m_iRef;

		if (m_iRef == 0)
		{
			delete this;
			return 0;
		}

		return m_iRef;
	}

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	string GetTag()	const
	{
		return m_strTag;
	}
};

