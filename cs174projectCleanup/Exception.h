#ifndef GUARD_EXCEPTION_H
#define GUARD_EXCEPTION_H

#include <exception>
#include <string>

class CException : public std::exception
{
public:
	const char* what() const  { return m_strMessage.c_str(); }

	CException(const std::string& strMessage="") : m_strMessage(strMessage)  { }
	virtual ~CException()  { }

	std::string m_strMessage;
};

#endif 