#ifndef GUARD_EXCEPTION_H
#define GUARD_EXCEPTION_H

#include <exception>
#include <string>

/** @brief The common exception type for all project-specific
  * exceptions.
  */
class CException : public std::exception
{
public:
	/** @brief Gets the error message. */
	const char* what() const  { return m_strMessage.c_str(); }

	CException(const std::string& strMessage="") : m_strMessage(strMessage)  { }
	virtual ~CException()  { }

	std::string m_strMessage; ///< the error message
};

#endif 