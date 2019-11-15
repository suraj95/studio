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

#ifndef __NEUROMORE_ACTICHAMPNODE_H
#define __NEUROMORE_ACTICHAMPNODE_H

// include the required headers
#include "../../Config.h"
#include "../../Graph/DeviceInputNode.h"
#include "actiCHampDevice.h"

#ifdef INCLUDE_DEVICE_ACTICHAMP

class ENGINE_API ActiChampNode : public DeviceInputNode
{
	public:
		enum { TYPE_ID = 0xD00000 | ActiChampDevice::TYPE_ID };
		static const char* Uuid ()												{ return "5876a271-e66b-4f29-b10d-a210b849d708"; }

		// constructor & destructor
		ActiChampNode(Graph* parentGraph) : DeviceInputNode(parentGraph, ActiChampDevice::TYPE_ID)		{}
		~ActiChampNode()				  										{}

		Core::Color GetColor() const override									{ return Core::RGBA(255,147,38); }
		uint32 GetType() const override											{ return TYPE_ID; }
		const char* GetTypeUuid() const override final							{ return Uuid(); }
		const char* GetReadableType() const override							{ return "ActiChamp"; }
		const char* GetRuleName() const override final							{ return ActiChampDevice::GetRuleName(); }
		GraphObject* Clone(Graph* parentObject) override						{ ActiChampNode* clone = new ActiChampNode(parentObject); return clone; }
};

#endif

#endif
