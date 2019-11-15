/****************************************************************************
**
** Copyright 2019 neuromore co
** Contact: https://neuromore.com/contact
**
** Commercial License Usage
** Licensees holding valid commercial neuromore licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and neuromore. For licensing terms
** and conditions see https://neuromore.com/licensing. For further
** information use the contact form at https://neuromore.com/contact.
**
** neuromore Public License Usage
** Alternatively, this file may be used under the terms of the neuromore
** Public License version 1 as published by neuromore co with exceptions as 
** appearing in the file neuromore-class-exception.md included in the 
** packaging of this file. Please review the following information to 
** ensure the neuromore Public License requirements will be met: 
** https://neuromore.com/npl
**
****************************************************************************/

#ifndef __CORE_LOGCALLBACKS_H
#define __CORE_LOGCALLBACKS_H

// include required headers headers
#include "StandardHeaders.h"
#include "String.h"


namespace Core
{

enum ELogLevel
{
	LOGLEVEL_NONE			= 0,
	LOGLEVEL_CRITICAL		= 1 << 0,
	LOGLEVEL_ERROR			= 1 << 1,
	LOGLEVEL_WARNING		= 1 << 2,
	LOGLEVEL_INFO			= 1 << 3,
	LOGLEVEL_DETAILEDINFO	= 1 << 4,
	LOGLEVEL_DEBUG			= 1 << 5
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ENGINE_API LogLevelPreset
{
	public:
		LogLevelPreset(const char* name, ELogLevel logLevel)					{ mName = name; mLogLevel = logLevel; }
		virtual ~LogLevelPreset()												{}

		ELogLevel GetLogLevel() const											{ return mLogLevel; }
		const char* GetName() const												{ return mName.AsChar(); }
		const String& GetNameString() const										{ return mName; }

	private:
		String		mName;
		ELogLevel	mLogLevel;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ENGINE_API LogCallback
{
	public:
		LogCallback();
		virtual ~LogCallback()												{}

		bool IsEnabled() const												{ return mIsEnabled; }
		void SetIsEnabled(bool isEnabled)									{ mIsEnabled = isEnabled; }

		virtual void Log(const char* text, ELogLevel logLevel) = 0;
		virtual uint32 GetType() const = 0;

	protected:
		bool		mIsEnabled;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ENGINE_API LogFileCallback : public LogCallback
{
	public:
		enum { TYPE_ID = 0x0000001 };

		LogFileCallback(const char* filename);
		virtual ~LogFileCallback();

		uint32 GetType() const override final								{ return TYPE_ID; }
		void Log(const char* text, ELogLevel logLevel) override final;

	private:
		FILE* mLogFile;
};

} // namespace Core


#endif
