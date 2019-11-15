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

#ifndef __NEUROMORE_OSCFEEDBACKPACKET_H
#define __NEUROMORE_OSCFEEDBACKPACKET_H

// include required headers
#include "OscPacket.h"



class ENGINE_API OscFeedbackPacket : public OscPacket
{	
	public:
		enum { NUM_FLOATS = 32 };

		// constructor & destructor
		OscFeedbackPacket();
		virtual ~OscFeedbackPacket();
		
		virtual void Write() override;

	private:
		void FillDatagram();

		// data entries
		float		mElapsedTime;
		bool		mSessionRunning;
		double		mNumPoints;
		bool		mHavePoints;

};

#endif
