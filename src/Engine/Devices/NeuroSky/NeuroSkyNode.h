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

#ifndef __NEUROMORE_NEUROSKYNODE_H
#define __NEUROMORE_NEUROSKYNODE_H

// include the required headers
#include "../../Config.h"
#include "../../Graph/DeviceInputNode.h"

#ifdef INCLUDE_DEVICE_NEUROSKY_MINDWAVE

class ENGINE_API NeuroSkyNode : public DeviceInputNode
{
	public:
		enum { TYPE_ID = 0xD00000 | NeuroSkyDevice::TYPE_ID };
		static const char* Uuid () { return "d676273c-bb6c-11e4-8dfc-aa07a5b093db"; }
		
		NeuroSkyNode(Graph* parentGraph) : DeviceInputNode(parentGraph, NeuroSkyDevice::TYPE_ID)		{}
		~NeuroSkyNode()																			{}

		Core::Color GetColor() const override									{ return Core::RGBA(0,164,228); } // color from NeuroSky logo
		uint32 GetType() const override											{ return TYPE_ID; }
		const char* GetTypeUuid() const override final							{ return Uuid(); }
		const char* GetReadableType() const override							{ return "NeuroSky"; }
		const char* GetRuleName() const override final							{ return NeuroSkyDevice::GetRuleName(); }
		GraphObject* Clone(Graph* parentGraph) override							{ NeuroSkyNode* clone = new NeuroSkyNode(parentGraph); return clone; }
};


#endif

#endif
